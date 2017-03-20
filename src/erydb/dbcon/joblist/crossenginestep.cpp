/* Copyright (C) 2014 EryDB, Inc.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; version 2 of
   the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA. */

//  $Id: crossenginestep.cpp 9709 2013-07-20 06:08:46Z xlou $

#include <unistd.h>
//#define NDEBUG
#include <cassert>
#include <sstream>
#include <iomanip>
using namespace std;

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/uuid/uuid_io.hpp>
using namespace boost;

#include "messagequeue.h"
using namespace messageqcpp;

#include "loggingid.h"
#include "errorcodes.h"
#include "erydberrorinfo.h"
#include "errorids.h"
using namespace logging;

#include "erydbsystemcatalog.h"
#include "constantcolumn.h"
using namespace execplan;

#include "rowgroup.h"
using namespace rowgroup;

#include "dataconvert.h"
using namespace dataconvert;

#include "querytele.h"
using namespace querytele;

#include "funcexp.h"

#include "jobstep.h"
#include "jlf_common.h"
#include "crossenginestep.h"

#include "libdrizzle-2.0/drizzle.h"
#include "libdrizzle-2.0/drizzle_client.h"

namespace joblist
{

DrizzleMySQL::DrizzleMySQL() : fDrzp(NULL), fDrzcp(NULL), fDrzrp(NULL)
{
}


DrizzleMySQL::~DrizzleMySQL()
{
	if (fDrzrp)
	{
		drizzle_result_free(fDrzrp);
	}
	fDrzrp = NULL;

	if (fDrzcp)
	{
		drizzle_con_close(fDrzcp);
		drizzle_con_free(fDrzcp);
	}
	fDrzcp = NULL;

	if (fDrzp)
	{
		drizzle_free(fDrzp);
	}
	fDrzp = NULL;
}


int DrizzleMySQL::init(const char* h, unsigned int p, const char* u, const char* w, const char* d)
{
	int ret = -1;

	fDrzp = drizzle_create();
	if (fDrzp != NULL)
	{
		fDrzcp = drizzle_con_add_tcp(fDrzp, h, p, u, w, d, DRIZZLE_CON_MYSQL);
		if (fDrzcp != NULL)
		{
			ret = drizzle_con_connect(fDrzcp);
			if (ret != 0)
				fErrStr = "fatal error in drizzle_con_connect()";
		}
		else
		{
			fErrStr = "fatal error in drizzle_con_add_tcp()";
		}
	}
	else
	{
		fErrStr = "fatal error in drizzle_create()";
	}

	return ret;
}


int DrizzleMySQL::run(const char* query)
{
	int ret = 0;
	drizzle_return_t drzret;
	fDrzrp = drizzle_query_str(fDrzcp, fDrzrp, query, &drzret);
	if (drzret == 0 && fDrzrp != NULL)
	{
		ret = drzret = drizzle_result_buffer(fDrzrp);
		if (drzret != 0)
			fErrStr = "fatal error reading result from crossengine client lib";
	}
	else
	{
		fErrStr = "fatal error executing query in crossengine client lib";
		if (drzret != 0)
			ret = drzret;
		else
			ret = -1;
	}

	return ret;
}


CrossEngineStep::CrossEngineStep(
	const string& schema,
	const string& table,
	const string& alias,
	const JobInfo& jobInfo) :
		BatchPrimitive(jobInfo),
		fRowsRetrieved(0),
		fRowsReturned(0),
		fRowsPerGroup(256),
		fOutputDL(NULL),
		fOutputIterator(0),
		fEndOfResult(false),
		fSchema(schema),
		fTable(table),
		fAlias(alias),
		fColumnCount(0),
		fFeInstance(funcexp::FuncExp::instance())
{
	fExtendedInfo = "CES: ";
	getMysqldInfo(jobInfo);
	fQtc.stepParms().stepType = StepTeleStats::T_CES;
    drizzle = new DrizzleMySQL();
}


CrossEngineStep::~CrossEngineStep()
{
    delete drizzle;
}


void CrossEngineStep::setOutputRowGroup(const rowgroup::RowGroup& rg)
{
	fRowGroupOut = fRowGroupDelivered = fRowGroupAdded = rg;
}


void CrossEngineStep::deliverStringTableRowGroup(bool b)
{
	// results are either using setField, or mapping to delivered row group
	fRowGroupDelivered.setUseStringTable(b);
}


bool CrossEngineStep::deliverStringTableRowGroup() const
{
	return fRowGroupDelivered.usesStringTable();
}


void CrossEngineStep::addFcnJoinExp(const vector<execplan::SRCP>& fe)
{
	fFeFcnJoin = fe;
}


void CrossEngineStep::addFcnExpGroup1(const boost::shared_ptr<ParseTree>& fe)
{
	fFeFilters = fe;
}


void CrossEngineStep::setFE1Input(const rowgroup::RowGroup& rg)
{
	fRowGroupFe1 = rg;
}


void CrossEngineStep::setFcnExpGroup3(const vector<execplan::SRCP>& fe)
{
	fFeSelects = fe;
}


void CrossEngineStep::setFE23Output(const rowgroup::RowGroup& rg)
{
	fRowGroupFe3 = fRowGroupDelivered = rg;
}


void CrossEngineStep::makeMappings()
{
	fFe1Column.reset(new int[fColumnCount]);
	for (uint64_t i = 0; i < fColumnCount; ++i)
		fFe1Column[i] = -1;

	if (fFeFilters != NULL || fFeFcnJoin.size() > 0)
	{
		const std::vector<uint32_t>& colInFe1 = fRowGroupFe1.getKeys();
		for (uint64_t i = 0; i < colInFe1.size(); i++)
		{
			map<uint32_t, uint32_t>::iterator it = fColumnMap.find(colInFe1[i]);
			if (it != fColumnMap.end())
				fFe1Column[it->second] = i;
		}

		fFeMapping1 = makeMapping(fRowGroupFe1, fRowGroupOut);
	}

	if (!fFeSelects.empty())
		fFeMapping3 = makeMapping(fRowGroupOut, fRowGroupFe3);
}


void CrossEngineStep::setField(int i, const char* value, Row& row)
{
	erydbSystemCatalog::ColDataType colType = row.getColType(i);

	if ((colType == erydbSystemCatalog::CHAR || colType == erydbSystemCatalog::VARCHAR) &&
		row.getColumnWidth(i) > 8)
	{
		if (value != NULL)
			row.setStringField(value, i);
		else
			row.setStringField("", i);
	}
	else
	{
		erydbSystemCatalog::ColType ct;
		ct.colDataType = colType;
		ct.colWidth = row.getColumnWidth(i);
		ct.scale = row.getScale(i);
		ct.precision = row.getPrecision(i);
		row.setIntField(convertValueNum(value, ct, row.getSignedNullValue(i)), i);
	}
}


inline void CrossEngineStep::addRow(RGData &data)
{
	fRowDelivered.setRid(fRowsReturned%fRowsPerGroup);
	fRowDelivered.nextRow();
	fRowGroupAdded.incRowCount();

	if (++fRowsReturned%fRowsPerGroup == 0)
	{
		fOutputDL->insert(data);
		data.reinit(fRowGroupAdded, fRowsPerGroup);
		fRowGroupAdded.setData(&data);
		fRowGroupAdded.resetRowGroup(fRowsReturned);
		fRowGroupAdded.getRow(0, &fRowDelivered);
	}
}


// simplified version of convertValueNum() in jlf_execplantojoblist.cpp.
int64_t CrossEngineStep::convertValueNum(
	const char* str, const erydbSystemCatalog::ColType& ct, int64_t nullValue)
{
	// return value
	int64_t rv = nullValue;

	// null value
	if (str == NULL)
		return rv;

	// convertColumnData(execplan::erydbSystemCatalog::ColType colType,
	//                   const std::string& dataOrig,
	//                   bool& pushWarning,
	//                   bool nulFlag,
	//                   bool noRoundup )
	bool pushWarning = false;
	boost::any anyVal = DataConvert::convertColumnData(ct, str, pushWarning, false, true);

	// Out of range values are treated as NULL as discussed during design review.
	if (pushWarning)
		return rv;

	// non-null value
	switch (ct.colDataType)
	{
		case erydbSystemCatalog::BIT:
		rv = boost::any_cast<bool>(anyVal);
			break;
		case erydbSystemCatalog::TINYINT:
		rv = boost::any_cast<char>(anyVal);
			break;
        case erydbSystemCatalog::UTINYINT:
        rv = boost::any_cast<uint8_t>(anyVal);
            break;
		case erydbSystemCatalog::SMALLINT:
		rv = boost::any_cast<int16_t>(anyVal);
			break;
        case erydbSystemCatalog::USMALLINT:
        rv = boost::any_cast<uint16_t>(anyVal);
            break;
		case erydbSystemCatalog::MEDINT:
		case erydbSystemCatalog::INT:
#ifdef _MSC_VER
		rv = boost::any_cast<int>(anyVal);
#else
		rv = boost::any_cast<int32_t>(anyVal);
#endif
			break;
        case erydbSystemCatalog::UMEDINT:
        case erydbSystemCatalog::UINT:
        rv = boost::any_cast<uint32_t>(anyVal);
            break;
		case erydbSystemCatalog::BIGINT:
		rv = boost::any_cast<long long>(anyVal);
			break;
        case erydbSystemCatalog::UBIGINT:
        rv = boost::any_cast<uint64_t>(anyVal);
            break;
		case erydbSystemCatalog::FLOAT:
        case erydbSystemCatalog::UFLOAT:
			{
				float f = boost::any_cast<float>(anyVal);
				//N.B. There is a bug in boost::any or in gcc where, if you store a nan,
				//     you will get back a nan, but not necessarily the same bits that you put in.
				//     This only seems to be for float (double seems to work).
				if (isnan(f))
				{
					uint32_t ti = joblist::FLOATNULL;
					float* tfp = (float*)&ti;
					f = *tfp;
				}
				float* fp = &f;
				int32_t* ip = reinterpret_cast<int32_t*>(fp);
			  rv = *ip;
			}
			break;
		case erydbSystemCatalog::DOUBLE:
        case erydbSystemCatalog::UDOUBLE:
			{
				double d = boost::any_cast<double>(anyVal);
				double* dp = &d;
				int64_t* ip = reinterpret_cast<int64_t*>(dp);
			  rv = *ip;
			}
			break;
		case erydbSystemCatalog::CHAR:
		case erydbSystemCatalog::VARCHAR:
		case erydbSystemCatalog::VARBINARY:
		case erydbSystemCatalog::BLOB:
		case erydbSystemCatalog::CLOB:
			{
				string i = boost::any_cast<string>(anyVal);
				// bug 1932, pad nulls up to the size of v
				i.resize(sizeof(rv), 0);
			  rv = *((uint64_t *) i.data());
			}
			break;
		case erydbSystemCatalog::DATE:
		rv = boost::any_cast<uint32_t>(anyVal);
			break;
		case erydbSystemCatalog::DATETIME:
		rv = boost::any_cast<uint64_t>(anyVal);
			break;
		case erydbSystemCatalog::DECIMAL:
        case erydbSystemCatalog::UDECIMAL:
			if (ct.colWidth == erydbSystemCatalog::ONE_BYTE)
			rv = boost::any_cast<char>(anyVal);
			else if (ct.colWidth == erydbSystemCatalog::TWO_BYTE)
			rv = boost::any_cast<int16_t>(anyVal);
			else if (ct.colWidth == erydbSystemCatalog::FOUR_BYTE)
#ifdef _MSC_VER
			rv = boost::any_cast<int>(anyVal);
#else
			rv = boost::any_cast<int32_t>(anyVal);
#endif
			else
			rv = boost::any_cast<long long>(anyVal);
			break;
		default:
			break;
	}

	return rv;
}


void CrossEngineStep::getMysqldInfo(const JobInfo& jobInfo)
{
	if (jobInfo.rm.getMysqldInfo(fHost, fUser, fPasswd, fPort) == false)
		throw ERYDBExcept(ERYDBErrorInfo::instance()->errorMsg(ERR_CROSS_ENGINE_CONFIG),
						ERR_CROSS_ENGINE_CONFIG);
}


void CrossEngineStep::run()
{
//	erydbassert(!fDelivery);

	if (fOutputJobStepAssociation.outSize() == 0)
		throw logic_error("No output data list for cross engine step.");

	fOutputDL = fOutputJobStepAssociation.outAt(0)->rowGroupDL();
	if (fOutputDL == NULL)
		throw logic_error("Output is not a RowGroup data list.");

    if (fDelivery == true)
    {
        fOutputIterator = fOutputDL->getIterator();
    }

	fRunner.reset(new boost::thread(Runner(this)));
}


void CrossEngineStep::join()
{
	if (fRunner)
		fRunner->join();
}


void CrossEngineStep::execute()
{
	int ret = 0;
	StepTeleStats sts;
	sts.query_uuid = fQueryUuid;
	sts.step_uuid = fStepUuid;

	try
	{
		sts.msg_type = StepTeleStats::ST_START;
		sts.total_units_of_work = 1;
		postStepStartTele(sts);

		ret = drizzle->init(fHost.c_str(), fPort, fUser.c_str(), fPasswd.c_str(), fSchema.c_str());
		if (ret != 0)
			handleMySqlError(drizzle->getError().c_str(), ret);

		string query(makeQuery());
		fLogger->logMessage(logging::LOG_TYPE_INFO, "QUERY to foreign engine: " + query);
		if (traceOn())
			cout << "QUERY: " << query << endl;

		ret = drizzle->run(query.c_str());
		if (ret != 0)
			handleMySqlError(drizzle->getError().c_str(), ret);

		int num_fields = drizzle->getFieldCount();

		char** rowIn;                            // input
		//shared_array<uint8_t> rgDataDelivered;      // output
		RGData rgDataDelivered;
		fRowGroupAdded.initRow(&fRowDelivered);
		// use getDataSize() i/o getMaxDataSize() to make sure there are 8192 rows.
		rgDataDelivered.reinit(fRowGroupAdded, fRowsPerGroup);
		fRowGroupAdded.setData(&rgDataDelivered);
		fRowGroupAdded.resetRowGroup(0);
		fRowGroupAdded.getRow(0, &fRowDelivered);

		if (traceOn())
			dlTimes.setFirstReadTime();

		// Any functions to evaluate
		makeMappings();
		bool doFE1 = ((fFeFcnJoin.size() > 0) || (fFeFilters != NULL));
		bool doFE3 =  (fFeSelects.size() > 0);
		if (!doFE1 && !doFE3)
		{
			while ((rowIn = drizzle->nextRow()) && !cancelled())
			{
				for(int i = 0; i < num_fields; i++)
					setField(i, rowIn[i], fRowDelivered);

				addRow(rgDataDelivered);
			}
		}

		else if (doFE1 && !doFE3)  // FE in WHERE clause only
		{
			shared_array<uint8_t> rgDataFe1;  // functions in where clause
			Row rowFe1;                       // row for fe evaluation
			fRowGroupFe1.initRow(&rowFe1, true);
			rgDataFe1.reset(new uint8_t[rowFe1.getSize()]);
			rowFe1.setData(rgDataFe1.get());

			while ((rowIn = drizzle->nextRow()) && !cancelled())
			{
				// Parse the columns used in FE1 first, the other column may not need be parsed.
				for(int i = 0; i < num_fields; i++)
				{
					if (fFe1Column[i] != -1)
						setField(fFe1Column[i], rowIn[i], rowFe1);
				}

				if (fFeFilters && fFeInstance->evaluate(rowFe1, fFeFilters.get()) == false)
					continue;

				// evaluate the FE join column
				fFeInstance->evaluate(rowFe1, fFeFcnJoin);

				// Pass throug the parsed columns, and parse the remaining columns.
				applyMapping(fFeMapping1, rowFe1, &fRowDelivered);
				for(int i = 0; i < num_fields; i++)
				{
					if (fFe1Column[i] == -1)
						setField(i, rowIn[i], fRowDelivered);
				}

				addRow(rgDataDelivered);
			}
		}

		else if (!doFE1 && doFE3)  // FE in SELECT clause only
		{
			shared_array<uint8_t> rgDataFe3;  // functions in select clause
			Row rowFe3;                       // row for fe evaluation
			fRowGroupOut.initRow(&rowFe3, true);
			rgDataFe3.reset(new uint8_t[rowFe3.getSize()]);
			rowFe3.setData(rgDataFe3.get());

			while ((rowIn = drizzle->nextRow()) && !cancelled())
			{
				for(int i = 0; i < num_fields; i++)
					setField(i, rowIn[i], rowFe3);

				fFeInstance->evaluate(rowFe3, fFeSelects);
				fFeInstance->evaluate(rowFe3, fFeSelects);

				applyMapping(fFeMapping3, rowFe3, &fRowDelivered);

				addRow(rgDataDelivered);
			}
		}

		else  // FE in SELECT clause, FE join and WHERE clause
		{
			shared_array<uint8_t> rgDataFe1;  // functions in where clause
			Row rowFe1;                       // row for fe1 evaluation
			fRowGroupFe1.initRow(&rowFe1, true);
			rgDataFe1.reset(new uint8_t[rowFe1.getSize()]);
			rowFe1.setData(rgDataFe1.get());

			shared_array<uint8_t> rgDataFe3;  // functions in select clause
			Row rowFe3;                       // row for fe3 evaluation
			fRowGroupOut.initRow(&rowFe3, true);
			rgDataFe3.reset(new uint8_t[rowFe3.getSize()]);
			rowFe3.setData(rgDataFe3.get());

			while ((rowIn = drizzle->nextRow()) && !cancelled())
			{
				// Parse the columns used in FE1 first, the other column may not need be parsed.
				for(int i = 0; i < num_fields; i++)
				{
					if (fFe1Column[i] != -1)
						setField(fFe1Column[i], rowIn[i], rowFe1);
				}

				if (fFeFilters && fFeInstance->evaluate(rowFe1, fFeFilters.get()) == false)
					continue;

				// evaluate the FE join column
				fFeInstance->evaluate(rowFe1, fFeFcnJoin);

				// Pass throug the parsed columns, and parse the remaining columns.
				applyMapping(fFeMapping1, rowFe1, &rowFe3);
				for(int i = 0; i < num_fields; i++)
				{
					if (fFe1Column[i] == -1)
						setField(i, rowIn[i], rowFe3);
				}

				fFeInstance->evaluate(rowFe3, fFeSelects);
				applyMapping(fFeMapping3, rowFe3, &fRowDelivered);

				addRow(rgDataDelivered);
			}
		}

		//INSERT_ADAPTER(fOutputDL, rgDataDelivered);
		fOutputDL->insert(rgDataDelivered);
		fRowsRetrieved = drizzle->getRowCount();
	}
	catch (ERYDBExcept& iex)
	{
		catchHandler(iex.what(), iex.errorCode(), fErrorInfo, fSessionId);
	}
	catch(const std::exception& ex)
	{
		catchHandler(ex.what(), ERR_CROSS_ENGINE_CONNECT, fErrorInfo, fSessionId);
	}
	catch(...)
	{
		catchHandler("CrossEngineStep execute caught an unknown exception",
						ERR_CROSS_ENGINE_CONNECT, fErrorInfo, fSessionId);
	}

	sts.msg_type = StepTeleStats::ST_SUMMARY;
	sts.total_units_of_work = sts.units_of_work_completed = 1;
	sts.rows = fRowsReturned;
	postStepSummaryTele(sts);

	fEndOfResult = true;
	fOutputDL->endOfInput();

	// Bug 3136, let mini stats to be formatted if traceOn.
	if (traceOn())
	{
		dlTimes.setLastReadTime();
		dlTimes.setEndOfInputTime();
		printCalTrace();
	}
}


void CrossEngineStep::setBPP(JobStep* jobStep)
{
	pColStep* pcs = dynamic_cast<pColStep*>(jobStep);
	pColScanStep* pcss = NULL;
	pDictionaryStep* pds = NULL;
	pDictionaryScan* pdss = NULL;
	FilterStep* fs = NULL;
	string bop = " AND ";
	if (pcs != 0)
	{
		if (dynamic_cast<PseudoColStep*>(pcs) != NULL)
			throw logic_error("No Psedo Column for foreign engine.");

		if (pcs->BOP() == BOP_OR)
			bop = " OR ";
		addFilterStr(pcs->getFilters(), bop);
	}
	else if ((pcss = dynamic_cast<pColScanStep*>(jobStep)) != NULL)
	{
		if (pcss->BOP() == BOP_OR)
			bop = " OR ";
		addFilterStr(pcss->getFilters(), bop);
	}
	else if ((pds = dynamic_cast<pDictionaryStep*>(jobStep)) != NULL)
	{
		if (pds->BOP() == BOP_OR)
			bop = " OR ";
		addFilterStr(pds->getFilters(), bop);
	}
	else if ((pdss = dynamic_cast<pDictionaryScan*>(jobStep)) != NULL)
	{
		if (pds->BOP() == BOP_OR)
			bop = " OR ";
		addFilterStr(pdss->getFilters(), bop);
	}
	else if ((fs = dynamic_cast<FilterStep*>(jobStep)) != NULL)
	{
		addFilterStr(fs->getFilters(), bop);
	}
}

void CrossEngineStep::addFilterStr(const vector<const Filter*>& f, const string& bop)
{
	if (f.size() == 0)
		return;

	string filterStr;
	for (uint64_t i = 0; i < f.size(); i++)
	{
		if (f[i]->data().empty())
			continue;

		if (!filterStr.empty())
			filterStr += bop;

		filterStr += f[i]->data();
	}

	if (!filterStr.empty())
	{
		if (!fWhereClause.empty())
			fWhereClause += " AND (" + filterStr + ")";
		else
			fWhereClause += " WHERE (" + filterStr + ")";
	}
}


void CrossEngineStep::setProjectBPP(JobStep* jobStep1, JobStep*)
{
	fColumnMap[jobStep1->tupleId()] = fColumnCount++;

	if (!fSelectClause.empty())
		fSelectClause += ", ";
	else
		fSelectClause += "SELECT ";

	fSelectClause += jobStep1->name();
}


string CrossEngineStep::makeQuery()
{
	ostringstream oss;
	oss << fSelectClause << " FROM " << fTable;
	if (fTable.compare(fAlias) != 0)
		oss << " " << fAlias;

	if (!fWhereClause.empty())
		oss << fWhereClause;

	// the string must consist of a single SQL statement without a terminating semicolon ; or \g.
	// oss << ";";

	return oss.str();
}

void CrossEngineStep::handleMySqlError(const char* errStr, unsigned int errCode)
{
	ostringstream oss;
	oss << errStr << "(" << errCode << ")";
	if (errCode == (unsigned int) -1)
		oss << "(null pointer)";
	else
		oss << "(" << errCode << ")";

	throw ERYDBExcept(oss.str(), ERR_CROSS_ENGINE_CONNECT);

	return;
}


const RowGroup& CrossEngineStep::getOutputRowGroup() const
{
	return fRowGroupOut;
}


const RowGroup& CrossEngineStep::getDeliveredRowGroup() const
{
	return fRowGroupDelivered;
}


uint32_t CrossEngineStep::nextBand(messageqcpp::ByteStream &bs)
{
	//shared_array<uint8_t> rgDataOut;
	RGData rgDataOut;
	bool more = false;
	uint32_t rowCount = 0;

	try
	{
		bs.restart();

		more = fOutputDL->next(fOutputIterator, &rgDataOut);
		if (traceOn() && dlTimes.FirstReadTime().tv_sec ==0)
			dlTimes.setFirstReadTime();

		if (more && !cancelled())
		{
			fRowGroupDelivered.setData(&rgDataOut);
			fRowGroupDelivered.serializeRGData(bs);
			rowCount = fRowGroupDelivered.getRowCount();
		}
		else
		{
			while (more)
				more = fOutputDL->next(fOutputIterator, &rgDataOut);
			fEndOfResult = true;
		}
	}
	catch(const std::exception& ex)
	{
		catchHandler(ex.what(), ERR_IN_DELIVERY, fErrorInfo, fSessionId);

		while (more)
			more = fOutputDL->next(fOutputIterator, &rgDataOut);
		fEndOfResult = true;
	}
	catch(...)
	{
		catchHandler("CrossEngineStep next band caught an unknown exception",
						ERR_IN_DELIVERY, fErrorInfo, fSessionId);

		while (more)
			more = fOutputDL->next(fOutputIterator, &rgDataOut);
		fEndOfResult = true;
	}

	if (fEndOfResult)
	{
		// send an empty / error band
		rgDataOut.reinit(fRowGroupDelivered, 0);
		fRowGroupDelivered.setData(&rgDataOut);
		fRowGroupDelivered.resetRowGroup(0);
		fRowGroupDelivered.setStatus(status());
		fRowGroupDelivered.serializeRGData(bs);

		if (traceOn())
		{
			dlTimes.setLastReadTime();
			dlTimes.setEndOfInputTime();
		}

		if (traceOn())
			printCalTrace();
	}

	return rowCount;
}


const string CrossEngineStep::toString() const
{
	ostringstream oss;
	oss << "CrossEngineStep ses:" << fSessionId << " txn:" << fTxnId << " st:" << fStepId;

	oss << " in:";
	for (unsigned i = 0; i < fInputJobStepAssociation.outSize(); i++)
		oss << fInputJobStepAssociation.outAt(i);

	oss << " out:";
	for (unsigned i = 0; i < fOutputJobStepAssociation.outSize(); i++)
		oss << fOutputJobStepAssociation.outAt(i);

	oss << endl;

	return oss.str();
}


void CrossEngineStep::printCalTrace()
{
	time_t t = time (0);
	char timeString[50];
	ctime_r (&t, timeString);
	timeString[strlen (timeString )-1] = '\0';
	ostringstream logStr;
	logStr  << "ses:" << fSessionId << " st: " << fStepId << " finished at "<< timeString
			<< "; rows retrieved-" << fRowsRetrieved
			<< "; total rows returned-" << fRowsReturned << endl
			<< "\t1st read " << dlTimes.FirstReadTimeString()
			<< "; EOI " << dlTimes.EndOfInputTimeString() << "; runtime-"
			<< JSTimeStamp::tsdiffstr(dlTimes.EndOfInputTime(), dlTimes.FirstReadTime())
			<< "s;\n\tUUID " << uuids::to_string(fStepUuid) << endl
			<< "\tJob completion status " << status() << endl;
	logEnd(logStr.str().c_str());
	fExtendedInfo += logStr.str();
	formatMiniStats();
}


void CrossEngineStep::formatMiniStats()
{
	ostringstream oss;
	oss << "CES "
		<< "UM "
		<< "- "
		<< "- "
		<< "- "
		<< "- "
		<< "- "
		<< "- "
		<< JSTimeStamp::tsdiffstr(dlTimes.EndOfInputTime(), dlTimes.FirstReadTime()) << " "
		<< fRowsReturned << " ";
	fMiniInfo += oss.str();
}

}
// vim:ts=4 sw=4:


