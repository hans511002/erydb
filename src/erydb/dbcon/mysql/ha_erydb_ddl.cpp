/* Copyright (C) 2014 EryDB, Inc.
   Copyright (C) 2016 MariaDB Corporaton

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

/*
 * $Id: ha_erydb_ddl.cpp 9675 2013-07-11 15:38:12Z chao $
 */

#include "erydb_mysql.h"
#include <string>
#include <iostream>
#include <stack>
#ifdef _MSC_VER
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include <fstream>
#include <sstream>
#include <cerrno>
#include <cstring>
#ifdef _MSC_VER
#include <unordered_set>
#else
#include <tr1/unordered_set>
#endif
#include <utility>
//#define NDEBUG
#include <cassert>
using namespace std;

#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/regex.hpp>
#include <boost/tokenizer.hpp>
using namespace boost;



#include "ha_erydb_impl_if.h"
using namespace cal_impl_if;

#include "ddlpkg.h"
#include "sqlparser.h"
using namespace ddlpackage;

#include "ddlpackageprocessor.h"
using namespace ddlpackageprocessor;

#include "dataconvert.h"
using namespace dataconvert;

#include "bytestream.h"
using namespace messageqcpp;

#include "configcpp.h"
using namespace config;

#include "erydbcompress.h"
using namespace compress;

#include "erydberrorinfo.h"
#include "errorids.h"
using namespace logging;

#include "dbrm.h"
using namespace BRM;

#include "erydbsystemcatalog.h"
#include "expressionparser.h"
#include "erydbselectexecutionplan.h"
#include "simplefilter.h"
#include "simplecolumn.h"
#include "expressionparser.h"
#include "constantcolumn.h"
using namespace execplan;

#include "resourcemanager.h"
using namespace joblist;

namespace
{

typedef erydbSelectExecutionPlan::ColumnMap::value_type CMVT_;
ResourceManager rm;
bool useHdfs = rm.useHdfs();

#include "ha_autoi.cpp"

//convenience fcn
inline uint32_t tid2sid(const uint32_t tid)
{
	return erydbSystemCatalog::erydb_tid2sid(tid);
}


uint32_t convertDataType(int dataType)
{
	uint32_t erydbDataType;

	switch (dataType)
	{
		case ddlpackage::DDL_CHAR:
			erydbDataType = erydbSystemCatalog::CHAR;
			break;

		case ddlpackage::DDL_VARCHAR:
			erydbDataType = erydbSystemCatalog::VARCHAR;
			break;

		case ddlpackage::DDL_VARBINARY:
			erydbDataType = erydbSystemCatalog::VARBINARY;
			break;

		case ddlpackage::DDL_BIT:
			erydbDataType = erydbSystemCatalog::BIT;
			break;

		case ddlpackage::DDL_REAL:
		case ddlpackage::DDL_DECIMAL:
		case ddlpackage::DDL_NUMERIC:
		case ddlpackage::DDL_NUMBER:
			erydbDataType = erydbSystemCatalog::DECIMAL;
			break;

		case ddlpackage::DDL_FLOAT:
			erydbDataType = erydbSystemCatalog::FLOAT;
			break;

		case ddlpackage::DDL_DOUBLE:
			erydbDataType = erydbSystemCatalog::DOUBLE;
			break;

		case ddlpackage::DDL_INT:
		case ddlpackage::DDL_INTEGER:
			erydbDataType = erydbSystemCatalog::INT;
			break;

		case ddlpackage::DDL_BIGINT:
			erydbDataType = erydbSystemCatalog::BIGINT;
			break;

		case ddlpackage::DDL_MEDINT:
			erydbDataType = erydbSystemCatalog::MEDINT;
			break;

		case ddlpackage::DDL_SMALLINT:
			erydbDataType = erydbSystemCatalog::SMALLINT;
			break;

		case ddlpackage::DDL_TINYINT:
			erydbDataType = erydbSystemCatalog::TINYINT;
			break;

		case ddlpackage::DDL_DATE:
			erydbDataType = erydbSystemCatalog::DATE;
			break;

		case ddlpackage::DDL_DATETIME:
			erydbDataType = erydbSystemCatalog::DATETIME;
			break;

		case ddlpackage::DDL_CLOB:
			erydbDataType = erydbSystemCatalog::CLOB;
			break;

		case ddlpackage::DDL_BLOB:
			erydbDataType = erydbSystemCatalog::BLOB;
			break;

		case ddlpackage::DDL_UNSIGNED_TINYINT:
			erydbDataType = erydbSystemCatalog::UTINYINT;
			break;

		case ddlpackage::DDL_UNSIGNED_SMALLINT:
			erydbDataType = erydbSystemCatalog::USMALLINT;
			break;

		case ddlpackage::DDL_UNSIGNED_INT:
			erydbDataType = erydbSystemCatalog::UINT;
			break;

		case ddlpackage::DDL_UNSIGNED_BIGINT:
			erydbDataType = erydbSystemCatalog::UBIGINT;
			break;

		case ddlpackage::DDL_UNSIGNED_DECIMAL:
		case ddlpackage::DDL_UNSIGNED_NUMERIC:
			erydbDataType = erydbSystemCatalog::UDECIMAL;
			break;

		case ddlpackage::DDL_UNSIGNED_FLOAT:
			erydbDataType = erydbSystemCatalog::UFLOAT;
			break;

		case ddlpackage::DDL_UNSIGNED_DOUBLE:
			erydbDataType = erydbSystemCatalog::UDOUBLE;
			break;
		default:
			throw runtime_error("Unsupported datatype!");

	}

	return erydbDataType;
}


int parseCompressionComment ( std::string comment )
{
	algorithm::to_upper(comment);
	regex compat("[[:space:]]*COMPRESSION[[:space:]]*=[[:space:]]*", regex_constants::extended);
	int compressiontype = 0;
	boost::match_results<std::string::const_iterator> what;
	std::string::const_iterator start, end;
	start = comment.begin();
	end = comment.end();
	boost::match_flag_type flags = boost::match_default;
	if (boost::regex_search(start, end, what, compat, flags))
	{
		//Find the pattern, now get the compression type
		string compType (&(*(what[0].second)));
		//; is the seperator between compression and autoincrement comments.
		unsigned i = compType.find_first_of(";");
		if ( i <= compType.length() )
		{
			compType = compType.substr( 0,i);
		}
		i = compType.find_last_not_of(" ");
		if ( i <= compType.length() )
		{
			compType = compType.substr( 0,i+1);
		}

		errno = 0;
		char *ep = NULL;
		const char *str = compType.c_str();
		compressiontype = strtoll(str, &ep, 10);
		//  (no digits) || (more chars)  || (other errors & value = 0)
		if ((ep == str) || (*ep != '\0') || (errno != 0 && compressiontype == 0))
		{
			compressiontype = -1;
		}

	}
	else
		compressiontype = MAX_INT;
	return compressiontype;
}


bool validateAutoincrementDatatype ( int type )
{
	bool validAutoType = false;
	switch (type)
	{
		case ddlpackage::DDL_INT:
		case ddlpackage::DDL_INTEGER:
		case ddlpackage::DDL_BIGINT:
		case ddlpackage::DDL_MEDINT:
		case ddlpackage::DDL_SMALLINT:
		case ddlpackage::DDL_TINYINT:
		case ddlpackage::DDL_UNSIGNED_INT:
		case ddlpackage::DDL_UNSIGNED_BIGINT:
		case ddlpackage::DDL_UNSIGNED_MEDINT:
		case ddlpackage::DDL_UNSIGNED_SMALLINT:
		case ddlpackage::DDL_UNSIGNED_TINYINT:
			validAutoType = true;
			break;
	}
	return validAutoType;
}

bool validateNextValue( int type, int64_t value )
{
	bool validValue = true;
	switch (type)
	{
		case ddlpackage::DDL_BIGINT:
			{
				if (value > MAX_BIGINT)
					validValue = false;
			}
			break;
		case ddlpackage::DDL_UNSIGNED_BIGINT:
			{
				if (static_cast<uint64_t>(value) > MAX_UBIGINT)
					validValue = false;
			}
			break;
		case ddlpackage::DDL_INT:
		case ddlpackage::DDL_INTEGER:
		case ddlpackage::DDL_MEDINT:
			{
				if (value > MAX_INT)
					validValue = false;
			}
			break;
		case ddlpackage::DDL_UNSIGNED_INT:
		case ddlpackage::DDL_UNSIGNED_MEDINT:
			{
				if (static_cast<uint64_t>(value) > MAX_UINT)
					validValue = false;
			}
			break;
		case ddlpackage::DDL_SMALLINT:
			{
				if (value > MAX_SMALLINT)
					validValue = false;
			}
			break;
		case ddlpackage::DDL_UNSIGNED_SMALLINT:
			{
				if (static_cast<uint64_t>(value) > MAX_USMALLINT)
					validValue = false;
			}
			break;
		case ddlpackage::DDL_TINYINT:
			{
				if (value > MAX_TINYINT)
					validValue = false;
			}
			break;
		case ddlpackage::DDL_UNSIGNED_TINYINT:
			{
				if (static_cast<uint64_t>(value) > MAX_UTINYINT)
					validValue = false;
			}
			break;
	}
	return validValue;
}

bool anyRowInTable(string& schema, string& tableName, int sessionID)
{
	//find a column in the table
	boost::shared_ptr<erydbSystemCatalog> csc = erydbSystemCatalog::makeerydbSystemCatalog(sessionID);
	csc->identity(execplan::erydbSystemCatalog::FE);
	erydbSystemCatalog::TableName aTableName;
	algorithm::to_lower(schema);
	algorithm::to_lower(tableName);
	aTableName.schema = schema;
	aTableName.table = tableName;
	erydbSystemCatalog::RIDList ridList = csc->columnRIDs(aTableName, true);
	erydbSystemCatalog::TableColName tableColName =  csc->colName(ridList[0].objnum);

	erydbSelectExecutionPlan csep;
	erydbSelectExecutionPlan::ReturnedColumnList returnedColumnList;
	erydbSelectExecutionPlan::ColumnMap colMap;

	SessionManager sm;
	BRM::TxnID txnID;
	txnID = sm.getTxnID(sessionID);
	if (!txnID.valid)
	{
		txnID.id = 0;
		txnID.valid = true;
	}
	QueryContext verID;
	verID = sm.verID();
	csep.txnID(txnID.id);
	csep.verID(verID);
	csep.sessionID(sessionID);

	string firstCol = tableColName.schema+"."+tableColName.table+"."+tableColName.column;
	SimpleColumn* col[1];
	col[0] = new SimpleColumn(firstCol, sessionID);
	SRCP srcp;
	srcp.reset(col[0]);
	colMap.insert(CMVT_(firstCol, srcp));
	csep.columnMapNonStatic(colMap);
	returnedColumnList.push_back(srcp);
	csep.returnedCols(returnedColumnList);

	erydbSelectExecutionPlan::TableList tablelist;
	tablelist.push_back(make_aliastable(schema, tableName, ""));
	csep.tableList(tablelist);

	boost::shared_ptr<messageqcpp::MessageQueueClient> exemgrClient (new messageqcpp::MessageQueueClient("ExeMgr1"));
	ByteStream msg, emsgBs;
	rowgroup::RGData rgData;
	ByteStream::quadbyte qb = 4;
	msg << qb;
	rowgroup::RowGroup *rowGroup = 0;
	bool anyRow = false;

	exemgrClient->write(msg);
	ByteStream msgPlan;
	csep.serialize(msgPlan);
	exemgrClient->write(msgPlan);
	msg.restart();
	msg = exemgrClient->read(); //error handling
	emsgBs = exemgrClient->read();
	ByteStream::quadbyte qb1;

	if (emsgBs.length() == 0)
	{
		//exemgrClient->shutdown();
		//delete exemgrClient;
		//exemgrClient = 0;
		throw runtime_error("Lost conection to ExeMgr.");
	}
	string emsgStr;
	emsgBs >> emsgStr;
	if (msg.length() == 4)
	{
		msg >> qb1;
		if (qb1 != 0)
		{
			//exemgrClient->shutdown();
			//delete exemgrClient;
			//exemgrClient = 0;
			throw runtime_error(emsgStr);
		}
	}

	while (true)
	{
		msg.restart();
		msg = exemgrClient->read();
		if ( msg.length() == 0 )
		{
			//exemgrClient->shutdown();
			//delete exemgrClient;
			//exemgrClient = 0;
			throw runtime_error("Lost conection to ExeMgr.");
		}
		else
		{
			if (!rowGroup)
			{
				//This is mete data
				rowGroup = new rowgroup::RowGroup();
				rowGroup->deserialize(msg);
				qb = 100;
				msg.restart();
				msg << qb;
				exemgrClient->write(msg);
				continue;
			}
			rgData.deserialize(msg);
			rowGroup->setData(&rgData);

			if (rowGroup->getStatus() != 0)
			{
				//msg.advance(rowGroup->getDataSize());
				msg >> emsgStr;
				//exemgrClient->shutdown();
				//delete exemgrClient;
				//exemgrClient = 0;
				throw runtime_error(emsgStr);
			}

			if (rowGroup->getRowCount() > 0)
				anyRow = true;
			//exemgrClient->shutdown();
			//delete exemgrClient;
			//exemgrClient = 0;
			return anyRow;
		}
	}
}

bool anyNullInTheColumn (string& schema, string& table, string& columnName, int sessionID)
{
	erydbSelectExecutionPlan csep;
	erydbSelectExecutionPlan::ReturnedColumnList returnedColumnList;
	erydbSelectExecutionPlan::FilterTokenList filterTokenList;
	erydbSelectExecutionPlan::ColumnMap colMap;
	algorithm::to_lower(schema);
	algorithm::to_lower(table);
	algorithm::to_lower(columnName);

	SessionManager sm;
	BRM::TxnID txnID;
	txnID = sm.getTxnID(sessionID);
	if (!txnID.valid)
	{
		txnID.id = 0;
		txnID.valid = true;
	}
	QueryContext verID;
	verID = sm.verID();
	csep.txnID(txnID.id);
	csep.verID(verID);
	csep.sessionID(sessionID);

	string firstCol = schema+"."+table+"."+columnName;
	SimpleColumn* col[1];
	col[0] = new SimpleColumn(firstCol, sessionID);
	SRCP srcp;
	srcp.reset(col[0]);
	colMap.insert(CMVT_(firstCol, srcp));
	csep.columnMapNonStatic(colMap);
	returnedColumnList.push_back(srcp);
	csep.returnedCols(returnedColumnList);

	SimpleFilter *sf = new SimpleFilter();
	boost::shared_ptr<Operator> sop(new PredicateOperator("isnull"));
	sf->op(sop);
	ConstantColumn *rhs = new ConstantColumn("", ConstantColumn::NULLDATA);
	sf->lhs(col[0]->clone());
	sf->rhs(rhs);

	filterTokenList.push_back(sf);
	csep.filterTokenList(filterTokenList);

	erydbSelectExecutionPlan::TableList tablelist;
	tablelist.push_back(make_aliastable(schema, table, ""));
	csep.tableList(tablelist);

	boost::shared_ptr<messageqcpp::MessageQueueClient> exemgrClient (new messageqcpp::MessageQueueClient("ExeMgr1"));
	ByteStream msg, emsgBs;
	rowgroup::RGData rgData;
	ByteStream::quadbyte qb = 4;
	msg << qb;
	rowgroup::RowGroup *rowGroup = 0;
	bool anyRow = false;

	exemgrClient->write(msg);
	ByteStream msgPlan;
	csep.serialize(msgPlan);
	exemgrClient->write(msgPlan);
	msg.restart();
	msg = exemgrClient->read(); //error handling
	emsgBs = exemgrClient->read();
	ByteStream::quadbyte qb1;

	if (emsgBs.length() == 0)
	{
		//exemgrClient->shutdown();
		//delete exemgrClient;
		//exemgrClient = 0;
		throw runtime_error("Lost conection to ExeMgr.");
	}
	string emsgStr;
	emsgBs >> emsgStr;
	if (msg.length() == 4)
	{
		msg >> qb1;
		if (qb1 != 0)
		{
			//exemgrClient->shutdown();
			//delete exemgrClient;
			//exemgrClient = 0;
			throw runtime_error(emsgStr);
		}
	}

	while (true)
	{
		msg.restart();
		msg = exemgrClient->read();
		if ( msg.length() == 0 )
		{
			//exemgrClient->shutdown();
			//delete exemgrClient;
			//exemgrClient = 0;
			throw runtime_error("Lost conection to ExeMgr.");
		}
		else
		{
			if (!rowGroup)
			{
				//This is mete data
				rowGroup = new rowgroup::RowGroup();
				rowGroup->deserialize(msg);
				qb = 100;
				msg.restart();
				msg << qb;
				exemgrClient->write(msg);
				continue;
			}
			rgData.deserialize(msg);
			rowGroup->setData(&rgData);

			if (rowGroup->getStatus() != 0)
			{
				//msg.advance(amount);
				msg >> emsgStr;
				//exemgrClient->shutdown();
				//delete exemgrClient;
				//exemgrClient = 0;
				throw runtime_error(emsgStr);
			}

			if (rowGroup->getRowCount() > 0)
				anyRow = true;
			//exemgrClient->shutdown();
			//delete exemgrClient;
			//exemgrClient = 0;
			return anyRow;
		}
	}
}

int ProcessDDLStatement(string& ddlStatement, string& schema, const string& table, int sessionID,
	 string& emsg, int compressionTypeIn = 2, bool isAnyAutoincreCol = false, int64_t nextvalue = 1, std::string autoiColName = "")
{
  SqlParser parser;
  THD *thd = current_thd;
#ifdef ERYDB_DEBUG
	cout << "ProcessDDLStatement: " << schema << "." << table << ":" << ddlStatement << endl;
#endif

  parser.setDefaultSchema(schema);
  int rc = 0;
  ERYDBCompressInterface erydbCompress;
  parser.Parse(ddlStatement.c_str());
  cout << "ProcessDDLStatement: finished parse " << schema << "." << table << endl;
  if (!thd->erydb_vtable.cal_conn_info)
		thd->erydb_vtable.cal_conn_info = (void*)(new cal_connection_info());
  cal_connection_info* ci = reinterpret_cast<cal_connection_info*>(thd->erydb_vtable.cal_conn_info);
  if(parser.Good())
  {
#ifdef WITH_WSREP
	  wsrep_erydb_return_nodbug(thd);
#endif
	boost::shared_ptr<erydbSystemCatalog> csc = erydbSystemCatalog::makeerydbSystemCatalog(sessionID);
	csc->identity(execplan::erydbSystemCatalog::FE);
	const ddlpackage::ParseTree &ptree = parser.GetParseTree();
	if (UNLIKELY(ptree.fList.size() == 0))
	{
		// TODO: Once the crash bug is found, this should convert to "return 0"
		cout << "***** ProcessDDLStatement has no stmt *****" << endl;
		setError(thd, ER_CHECK_NOT_IMPLEMENTED, "DDL processed without statement");
		return 1;
	}
	SqlStatement &stmt = *ptree.fList[0];
	bool isVarbinaryAllowed = false;
	std::string valConfig = config::Config::makeConfig()->getConfig(
			"WriteEngine", "AllowVarbinary" );
	algorithm::to_upper(valConfig);
	if (valConfig.compare("YES") == 0)
		isVarbinaryAllowed = true;

	//@Bug 1771. error out for not supported feature.
	if ( typeid ( stmt ) == typeid ( CreateTableStatement ) )
	{
		CreateTableStatement * createTable = dynamic_cast <CreateTableStatement *> ( &stmt );
		//@Bug 5767. To handle key words inside `` for a tablename.
		if (!(boost::iequals(schema, createTable->fTableDef->fQualifiedName->fSchema)) || !(boost::iequals(table,createTable->fTableDef->fQualifiedName->fName)))
		{
			rc = 1;
			thd->get_stmt_da()->set_overwrite_status(true);

			thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, (ERYDBErrorInfo::instance()->errorMsg(ERR_CREATE_DATATYPE_NOT_SUPPORT)).c_str());
			ci->alterTableState = cal_connection_info::NOT_ALTER;
			ci->isAlter = false;
			return rc;
		}

		bool matchedCol = false;
		for ( unsigned i=0; i < createTable->fTableDef->fColumns.size(); i++ )
		{
			// if there are any constraints other than 'DEFAULT NULL' (which is the default in ERYDB), kill
			//  the statement
			bool autoIncre = false;
			uint64_t startValue = 1;
			if (createTable->fTableDef->fColumns[i]->fConstraints.size() > 0 )
			{
				//support default value and NOT NULL constraint
				for (uint32_t j=0; j < createTable->fTableDef->fColumns[i]->fConstraints.size(); j++)
				{
					if (createTable->fTableDef->fColumns[i]->fConstraints[j]->fConstraintType != DDL_NOT_NULL)
					{
						rc = 1;
						thd->get_stmt_da()->set_overwrite_status(true);

						thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, (ERYDBErrorInfo::instance()->errorMsg(ERR_CONSTRAINTS)).c_str());
						ci->alterTableState = cal_connection_info::NOT_ALTER;
						ci->isAlter = false;
						return rc;
					}
				}
			}

			//check varbinary data type
			if ((createTable->fTableDef->fColumns[i]->fType->fType == ddlpackage::DDL_VARBINARY) && !isVarbinaryAllowed)
			{
				rc = 1;
  	 			thd->get_stmt_da()->set_overwrite_status(true);

	 			thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, "Varbinary is currently not supported by EryDB.");
				ci->alterTableState = cal_connection_info::NOT_ALTER;
				ci->isAlter = false;
	 			return rc;
			}

			if ((createTable->fTableDef->fColumns[i]->fType->fType == ddlpackage::DDL_VARBINARY) &&
			((createTable->fTableDef->fColumns[i]->fType->fLength > 8000) || (createTable->fTableDef->fColumns[i]->fType->fLength < 8)))
			{
				rc = 1;
  	 			thd->get_stmt_da()->set_overwrite_status(true);

	 			thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, "Varbinary length has to be between 8 and 8000.");
				ci->alterTableState = cal_connection_info::NOT_ALTER;
				ci->isAlter = false;
	 			return rc;
			}

			if (createTable->fTableDef->fColumns[i]->fDefaultValue)
			{
				if ((!createTable->fTableDef->fColumns[i]->fDefaultValue->fNull) && (createTable->fTableDef->fColumns[i]->fType->fType == ddlpackage::DDL_VARBINARY))
				{
					rc = 1;
					thd->get_stmt_da()->set_overwrite_status(true);

					thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, "Varbinary column cannot have default value.");
					ci->alterTableState = cal_connection_info::NOT_ALTER;
					ci->isAlter = false;
					return rc;
				}

				if (!createTable->fTableDef->fColumns[i]->fDefaultValue->fNull)
				{
					//validate the default value, if out of range, just error out
					uint32_t dataType;
					dataType = convertDataType(createTable->fTableDef->fColumns[i]->fType->fType);
					erydbSystemCatalog::ColType colType;
					colType.colDataType = (erydbSystemCatalog::ColDataType) dataType;
					colType.colWidth = createTable->fTableDef->fColumns[i]->fType->fLength;
					colType.precision = createTable->fTableDef->fColumns[i]->fType->fPrecision;
					colType.scale = createTable->fTableDef->fColumns[i]->fType->fScale;
					boost::any convertedVal;
					bool pushWarning = false;
					try {
						convertedVal = DataConvert::convertColumnData(colType, createTable->fTableDef->fColumns[i]->fDefaultValue->fValue, pushWarning, false, false );
					}
					catch(std::exception&)
					{
						rc = 1;
						thd->get_stmt_da()->set_overwrite_status(true);
						thd->raise_error_printf(ER_INTERNAL_ERROR, "The default value is out of range for the specified data type.");
						ci->alterTableState = cal_connection_info::NOT_ALTER;
						ci->isAlter = false;
						return rc;
					}
					if (pushWarning)
					{
						rc = 1;
						thd->get_stmt_da()->set_overwrite_status(true);
						thd->raise_error_printf(ER_INTERNAL_ERROR, "The default value is out of range for the specified data type.");
						ci->alterTableState = cal_connection_info::NOT_ALTER;
						ci->isAlter = false;
						return rc;
					}
				}
			}

			//Parse the column comment
			string comment = createTable->fTableDef->fColumns[i]->fComment;
			int compressionType = compressionTypeIn;
			if ( comment.length() > 0 )
			{
				compressionType = parseCompressionComment( comment);
				if ( compressionType == MAX_INT )
				{
					compressionType = compressionTypeIn;
				}
				else if ( compressionType < 0 )
				{
					rc = 1;
					thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_COMPRESSION_TYPE)).c_str());
					ci->alterTableState = cal_connection_info::NOT_ALTER;
					ci->isAlter = false;
					return rc;
				}
				if (compressionType == 1) compressionType = 2;
				if (( compressionType > 0 ) && !(erydbCompress.isCompressionAvail( compressionType )))
				{
					rc = 1;
					ci->alterTableState = cal_connection_info::NOT_ALTER;
					ci->isAlter = false;
#ifdef SKIP_ERYDB_COMPRESSION
		Message::Args args;
		thd->get_stmt_da()->set_overwrite_status(true);
		args.add("The compression type");
		thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_ENTERPRISE_ONLY, args)).c_str());
#else
		thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_COMPRESSION_TYPE)).c_str());
#endif
					return rc;
				}

				try {
					autoIncre = parseAutoincrementColumnComment(comment, startValue);
					if (autoIncre)
					{
						//Check whether there is a column with autoincrement already
						if ((isAnyAutoincreCol) && !(boost::iequals(autoiColName, createTable->fTableDef->fColumns[i]->fName)))
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_NUMBER_AUTOINCREMENT)).c_str());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}
						else
						{
							isAnyAutoincreCol = true;
							autoiColName = createTable->fTableDef->fColumns[i]->fName;
							matchedCol = true;
						}

						//Check whether the column has default value. If there is, error out
						if (createTable->fTableDef->fColumns[i]->fDefaultValue)
						{
							if (!createTable->fTableDef->fColumns[i]->fDefaultValue->fNull)
							{
								rc = 1;
								thd->get_stmt_da()->set_overwrite_status(true);
								thd->raise_error_printf(ER_INTERNAL_ERROR, "Autoincrement column cannot have a default value.");
								ci->alterTableState = cal_connection_info::NOT_ALTER;
								ci->isAlter = false;
								return rc;
							}
						}
					}
				}
				catch (runtime_error& ex)
				{
					rc = 1;
					thd->get_stmt_da()->set_overwrite_status(true);
					thd->raise_error_printf(ER_INTERNAL_ERROR, ex.what());
					ci->alterTableState = cal_connection_info::NOT_ALTER;
					ci->isAlter = false;
					return rc;
				}

			}
			if (!autoIncre &&  isAnyAutoincreCol && (boost::iequals(autoiColName, createTable->fTableDef->fColumns[i]->fName)))
			{
				autoIncre = true;
				matchedCol = true;
				startValue = nextvalue;
			}

			if (startValue <= 0)
			{
				rc = 1;
				thd->get_stmt_da()->set_overwrite_status(true);
				thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_NEGATIVE_STARTVALUE)).c_str());
				ci->alterTableState = cal_connection_info::NOT_ALTER;
				ci->isAlter = false;
				return rc;
			}

			if(autoIncre)
			{
					if (!validateAutoincrementDatatype(createTable->fTableDef->fColumns[i]->fType->fType))
					{
						rc = 1;
						thd->get_stmt_da()->set_overwrite_status(true);
						thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_AUTOINCREMENT_TYPE)).c_str());
						ci->alterTableState = cal_connection_info::NOT_ALTER;
						ci->isAlter = false;
						return rc;
					}
			 }

			if (!validateNextValue(createTable->fTableDef->fColumns[i]->fType->fType, startValue))
			{
				rc = 1;
				thd->get_stmt_da()->set_overwrite_status(true);
				thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_STARTVALUE)).c_str());
				ci->alterTableState = cal_connection_info::NOT_ALTER;
				ci->isAlter = false;
				return rc;
			}

			//hdfs
			if ((compressionType ==0) && (useHdfs))
			{
				compressionType = 2;
				string errmsg ("The table is created with Erydb compression type 2 under HDFS." );
				push_warning(thd, Sql_condition::WARN_LEVEL_WARN, 9999, errmsg.c_str());
			}

			(createTable->fTableDef->fColumns[i]->fType)->fCompressiontype = compressionType;
			if (autoIncre)
				(createTable->fTableDef->fColumns[i]->fType)->fAutoincrement = "y";
			else
				(createTable->fTableDef->fColumns[i]->fType)->fAutoincrement = "n";

			(createTable->fTableDef->fColumns[i]->fType)->fNextvalue = startValue;
		}

		if (isAnyAutoincreCol && !matchedCol) //@Bug 3555 error out on invalid column
		{
			rc = 1;
			Message::Args args;
			thd->get_stmt_da()->set_overwrite_status(true);
			args.add(autoiColName);
			thd->raise_error_printf(ER_INTERNAL_ERROR,(ERYDBErrorInfo::instance()->errorMsg(ERR_UNKNOWN_COL, args)).c_str());
			ci->alterTableState = cal_connection_info::NOT_ALTER;
			ci->isAlter = false;
			return rc;
		}
	}
	else if ( typeid ( stmt ) == typeid ( AlterTableStatement ) )
	{
		AlterTableStatement * alterTable = dynamic_cast <AlterTableStatement *> ( &stmt );
		if ( schema.length() == 0 )
		{
			schema = alterTable->fTableName->fSchema;
			if ( schema.length() == 0 )
			{
				rc = 1;
  	 			thd->get_stmt_da()->set_overwrite_status(true);

	 			thd->raise_error_printf(ER_INTERNAL_ERROR, "No database selected.");
				ci->alterTableState = cal_connection_info::NOT_ALTER;
				ci->isAlter = false;
	 			return rc;
			}
		}

		ddlpackage::AlterTableActionList actionList = alterTable->fActions;
		if (actionList.size() > 1) //@bug 3753 we don't support multiple actions in alter table statement
		{
			rc = 1;
			thd->get_stmt_da()->set_overwrite_status(true);

			thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, "Multiple actions in alter table statement is currently not supported by Erydb.");

			ci->alterTableState = cal_connection_info::NOT_ALTER;
			ci->isAlter = false;
			return rc;
		}

		for ( unsigned i=0; i < actionList.size(); i++ )
		{
			if ( ddlpackage::AtaAddColumn *addColumnPtr = dynamic_cast<AtaAddColumn*> (actionList[i]) )
			{
				//check varbinary data type
				if ((addColumnPtr->fColumnDef->fType->fType == ddlpackage::DDL_VARBINARY) && !isVarbinaryAllowed)
				{
					rc = 1;
					thd->get_stmt_da()->set_overwrite_status(true);
					thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, "Varbinary is currently not supported by Erydb.");
					ci->alterTableState = cal_connection_info::NOT_ALTER;
					ci->isAlter = false;
					return rc;
				}

				if ((addColumnPtr->fColumnDef->fType->fType == ddlpackage::DDL_VARBINARY) &&
				((addColumnPtr->fColumnDef->fType->fLength > 8000) || (addColumnPtr->fColumnDef->fType->fLength < 8)))
				{
					rc = 1;
					thd->get_stmt_da()->set_overwrite_status(true);
					thd->raise_error_printf(ER_INTERNAL_ERROR, "Varbinary length has to be between 8 and 8000.");
					ci->alterTableState = cal_connection_info::NOT_ALTER;
					ci->isAlter = false;
					return rc;
				}
				uint64_t startValue = 1;
				bool autoIncre  = false;
				if ( (addColumnPtr->fColumnDef->fConstraints.size() > 0 ) || addColumnPtr->fColumnDef->fDefaultValue )
				{
					//support default value and NOT NULL constraint
					for (uint32_t j=0; j < addColumnPtr->fColumnDef->fConstraints.size(); j++)
					{
						if (addColumnPtr->fColumnDef->fConstraints[j]->fConstraintType != DDL_NOT_NULL)
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, (ERYDBErrorInfo::instance()->errorMsg(ERR_CONSTRAINTS)).c_str());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}
						//if not null constraint, user has to provide a default value
						if ((addColumnPtr->fColumnDef->fConstraints[j]->fConstraintType == DDL_NOT_NULL) && (!addColumnPtr->fColumnDef->fDefaultValue))
						{

							//do select count(*) from the table to check whether there are existing rows. if there is, error out.
							bool anyRow  = false;
							try {
								anyRow = anyRowInTable(alterTable->fTableName->fSchema, alterTable->fTableName->fName, sessionID);
							}
							catch (runtime_error& ex)
							{
								rc = 1;
								thd->get_stmt_da()->set_overwrite_status(true);
								thd->raise_error_printf(ER_INTERNAL_ERROR, ex.what());
								ci->alterTableState = cal_connection_info::NOT_ALTER;
								ci->isAlter = false;
								return rc;
							}
							catch (...)
							{
								rc = 1;
								thd->get_stmt_da()->set_overwrite_status(true);
								thd->raise_error_printf(ER_INTERNAL_ERROR, "Unknown exception caught when checking any rows in the table.");
								ci->alterTableState = cal_connection_info::NOT_ALTER;
								ci->isAlter = false;
								return rc;
							}
							if (anyRow)
							{
								rc = 1;
								thd->get_stmt_da()->set_overwrite_status(true);
								thd->raise_error_printf(ER_INTERNAL_ERROR, "Table is not empty. New column has to have a default value if NOT NULL required.");
								ci->alterTableState = cal_connection_info::NOT_ALTER;
								ci->isAlter = false;
								return rc;
							}
						}
						else if ((addColumnPtr->fColumnDef->fConstraints[j]->fConstraintType == DDL_NOT_NULL) &&(addColumnPtr->fColumnDef->fDefaultValue))
						{
							if (addColumnPtr->fColumnDef->fDefaultValue->fValue.length() == 0) //empty string is NULL in erydb
							{
								rc = 1;
								thd->get_stmt_da()->set_overwrite_status(true);
								thd->raise_error_printf(ER_INTERNAL_ERROR, "New column has to have a default value if NOT NULL required.");
								ci->alterTableState = cal_connection_info::NOT_ALTER;
								ci->isAlter = false;
								return rc;
							}
						}
					}

					if (addColumnPtr->fColumnDef->fDefaultValue)
					{
						if ((!addColumnPtr->fColumnDef->fDefaultValue->fNull) && (addColumnPtr->fColumnDef->fType->fType == ddlpackage::DDL_VARBINARY))
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, "Varbinary column cannot have default value.");
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}

						//validate the default value, if out of range, just error out
						uint32_t dataType;
						dataType = convertDataType(addColumnPtr->fColumnDef->fType->fType);
						erydbSystemCatalog::ColType colType;
						colType.colDataType = (erydbSystemCatalog::ColDataType) dataType;
						colType.colWidth = addColumnPtr->fColumnDef->fType->fLength;
						colType.precision = addColumnPtr->fColumnDef->fType->fPrecision;
						colType.scale = addColumnPtr->fColumnDef->fType->fScale;
						boost::any convertedVal;
						bool pushWarning = false;
						try {
							convertedVal = DataConvert::convertColumnData(colType, addColumnPtr->fColumnDef->fDefaultValue->fValue, pushWarning, false, false );
						}
						catch(std::exception&)
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, "The default value is out of range for the specified data type.");
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}
						if (pushWarning)
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, "The default value is out of range for the specified data type.");
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}
					}
				}
				//Handle compression type
				string comment = addColumnPtr->fColumnDef->fComment;
				int compressionType = compressionTypeIn;
				if ( comment.length() > 0 )
				{
					//@Bug 3782 This is for synchronization after calonlinealter to use
					algorithm::to_upper(comment);
					regex pat("[[:space:]]*SCHEMA[[:space:]]+SYNC[[:space:]]+ONLY", regex_constants::extended);
					if (regex_search(comment, pat))
					{
						return 0;
					}
					compressionType = parseCompressionComment( comment);
					if ( compressionType == MAX_INT )
					{
						compressionType = compressionTypeIn;
					}
					else if ( compressionType < 0 )
					{
						rc = 1;
						thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_COMPRESSION_TYPE)).c_str());
						ci->alterTableState = cal_connection_info::NOT_ALTER;
						ci->isAlter = false;
						return rc;
					}

					if (( compressionType > 0 ) && !(erydbCompress.isCompressionAvail( compressionType )))
					{
						rc = 1;
						thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_COMPRESSION_TYPE)).c_str());
						ci->alterTableState = cal_connection_info::NOT_ALTER;
						ci->isAlter = false;
						return rc;
					}

					if ((compressionType ==0) && (useHdfs))
					{
						compressionType = 2;
						string errmsg ("The column is created with Erydb compression type 2 under HDFS." );
						push_warning(thd, Sql_condition::WARN_LEVEL_WARN, 9999, errmsg.c_str());
					}

					try {
						autoIncre = parseAutoincrementColumnComment(comment, startValue);
					}
					catch (runtime_error& ex)
					{
						rc = 1;
						thd->get_stmt_da()->set_overwrite_status(true);
						thd->raise_error_printf(ER_INTERNAL_ERROR, ex.what());
						ci->alterTableState = cal_connection_info::NOT_ALTER;
						ci->isAlter = false;
						return rc;
					}
					if (autoIncre)
					{
						//Check if the table already has autoincrement column
						boost::shared_ptr<erydbSystemCatalog> csc = erydbSystemCatalog::makeerydbSystemCatalog(sessionID);
						csc->identity(execplan::erydbSystemCatalog::FE);
						erydbSystemCatalog::TableName tableName;
						tableName.schema = alterTable->fTableName->fSchema;
						tableName.table = alterTable->fTableName->fName;
						erydbSystemCatalog::TableInfo tblInfo;
						try {
							tblInfo = csc->tableInfo(tableName);
						}
						catch (runtime_error& ex)
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, ex.what());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}

						if (tblInfo.tablewithautoincr == 1)
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_NUMBER_AUTOINCREMENT)).c_str());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}

						if (!validateAutoincrementDatatype(addColumnPtr->fColumnDef->fType->fType))
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_AUTOINCREMENT_TYPE)).c_str());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}
						if (!validateNextValue(addColumnPtr->fColumnDef->fType->fType, startValue))
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_STARTVALUE)).c_str());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}

						if (startValue <= 0)
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, (ERYDBErrorInfo::instance()->errorMsg(ERR_NEGATIVE_STARTVALUE)).c_str());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}
					}
				}
				addColumnPtr->fColumnDef->fType->fCompressiontype = compressionType;
				if (autoIncre)
					addColumnPtr->fColumnDef->fType->fAutoincrement = "y";
				else
					addColumnPtr->fColumnDef->fType->fAutoincrement = "n";

				addColumnPtr->fColumnDef->fType->fNextvalue = startValue;

			}
			else if ( dynamic_cast<AtaAddTableConstraint*> (actionList[i]))
			{
				rc = 1;
  	 			thd->get_stmt_da()->set_overwrite_status(true);

	 			thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, (ERYDBErrorInfo::instance()->errorMsg(ERR_CONSTRAINTS)).c_str());
				ci->alterTableState = cal_connection_info::NOT_ALTER;
				ci->isAlter = false;
	 			return rc;
			}
/*			else if ( dynamic_cast<AtaSetColumnDefault*> (actionList[i]) )
			{
				rc = 1;
  	 			thd->get_stmt_da()->set_overwrite_status(true);
	 			thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, (ERYDBErrorInfo::instance()->errorMsg(ERR_CONSTRAINTS)).c_str());
				ci->alterTableState = cal_connection_info::NOT_ALTER;
				ci->isAlter = false;
	 			return rc;
			}
			else if ( dynamic_cast<AtaDropColumnDefault*> (actionList[i]) )
			{
				rc = 1;
  	 			thd->get_stmt_da()->set_overwrite_status(true);
	 			thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, (ERYDBErrorInfo::instance()->errorMsg(ERR_CONSTRAINTS)).c_str());
				ci->alterTableState = cal_connection_info::NOT_ALTER;
				ci->isAlter = false;
	 			return rc;
			}
*/
			else if ( ddlpackage::AtaAddColumns *addColumnsPtr = dynamic_cast<AtaAddColumns*>(actionList[i]))
			{
				if ((addColumnsPtr->fColumns).size() > 1)
				{
					rc = 1;
					thd->get_stmt_da()->set_overwrite_status(true);
					thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, "Multiple actions in alter table statement is currently not supported by Erydb.");
					ci->alterTableState = cal_connection_info::NOT_ALTER;
					ci->isAlter = false;
					return rc;
				}

				//check varbinary data type
				if ((addColumnsPtr->fColumns[0]->fType->fType == ddlpackage::DDL_VARBINARY) && !isVarbinaryAllowed)
				{
					rc = 1;
					thd->get_stmt_da()->set_overwrite_status(true);
					thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, "Varbinary is currently not supported by Erydb.");
					ci->alterTableState = cal_connection_info::NOT_ALTER;
					ci->isAlter = false;
					return rc;
				}


				if ((addColumnsPtr->fColumns[0]->fType->fType == ddlpackage::DDL_VARBINARY) &&
				((addColumnsPtr->fColumns[0]->fType->fLength > 8000) || (addColumnsPtr->fColumns[0]->fType->fLength < 8)))
				{
					rc = 1;
					thd->get_stmt_da()->set_overwrite_status(true);
					thd->raise_error_printf(ER_INTERNAL_ERROR, "Varbinary length has to be between 8 and 8000.");
					ci->alterTableState = cal_connection_info::NOT_ALTER;
					ci->isAlter = false;
					return rc;
				}
				uint64_t startValue = 1;
				bool autoIncre  = false;
				if ( (addColumnsPtr->fColumns[0]->fConstraints.size() > 0 ) || addColumnsPtr->fColumns[0]->fDefaultValue )
				{
					//@Bug 5274. support default value and NOT NULL constraint
					for (uint32_t j=0; j < addColumnsPtr->fColumns[0]->fConstraints.size(); j++)
					{
						if (addColumnsPtr->fColumns[0]->fConstraints[j]->fConstraintType != DDL_NOT_NULL)
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, (ERYDBErrorInfo::instance()->errorMsg(ERR_CONSTRAINTS)).c_str());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}
						//if not null constraint, user has to provide a default value
						if ((addColumnsPtr->fColumns[0]->fConstraints[j]->fConstraintType == DDL_NOT_NULL) && (!addColumnsPtr->fColumns[0]->fDefaultValue))
						{

							//do select count(*) from the table to check whether there are existing rows. if there is, error out.
							bool anyRow  = false;
							try {
								anyRow = anyRowInTable(alterTable->fTableName->fSchema, alterTable->fTableName->fName, sessionID);
							}
							catch (runtime_error& ex)
							{
								rc = 1;
								thd->get_stmt_da()->set_overwrite_status(true);
								thd->raise_error_printf(ER_INTERNAL_ERROR, ex.what());
								ci->alterTableState = cal_connection_info::NOT_ALTER;
								ci->isAlter = false;
								return rc;
							}
							catch (...)
							{
								rc = 1;
								thd->get_stmt_da()->set_overwrite_status(true);
								thd->raise_error_printf(ER_INTERNAL_ERROR, "Unknown exception caught when checking any rows in the table.");
								ci->alterTableState = cal_connection_info::NOT_ALTER;
								ci->isAlter = false;
								return rc;
							}
							if (anyRow)
							{
								rc = 1;
								thd->get_stmt_da()->set_overwrite_status(true);
								thd->raise_error_printf(ER_INTERNAL_ERROR, "Table is not empty. New column has to have a default value if NOT NULL required.");
								ci->alterTableState = cal_connection_info::NOT_ALTER;
								ci->isAlter = false;
								return rc;
							}
						}
						else if ((addColumnsPtr->fColumns[0]->fConstraints[j]->fConstraintType == DDL_NOT_NULL) &&(addColumnsPtr->fColumns[0]->fDefaultValue))
						{
							if (addColumnsPtr->fColumns[0]->fDefaultValue->fValue.length() == 0) //empty string is NULL in erydb
							{
								rc = 1;
								thd->get_stmt_da()->set_overwrite_status(true);
								thd->raise_error_printf(ER_INTERNAL_ERROR, "New column has to have a default value if NOT NULL required.");
								ci->alterTableState = cal_connection_info::NOT_ALTER;
								ci->isAlter = false;
								return rc;
							}
						}
					}

					if (addColumnsPtr->fColumns[0]->fDefaultValue)
					{
						if ((!addColumnsPtr->fColumns[0]->fDefaultValue->fNull) && (addColumnsPtr->fColumns[0]->fType->fType == ddlpackage::DDL_VARBINARY))
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, "Varbinary column cannot have default value.");
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}

						//validate the default value, if out of range, just error out
						uint32_t dataType;
						dataType = convertDataType(addColumnsPtr->fColumns[0]->fType->fType);
						erydbSystemCatalog::ColType colType;
						colType.colDataType = (erydbSystemCatalog::ColDataType) dataType;
						colType.colWidth = addColumnsPtr->fColumns[0]->fType->fLength;
						colType.precision = addColumnsPtr->fColumns[0]->fType->fPrecision;
						colType.scale = addColumnsPtr->fColumns[0]->fType->fScale;
						boost::any convertedVal;
						bool pushWarning = false;
						try {
							convertedVal = DataConvert::convertColumnData(colType, addColumnsPtr->fColumns[0]->fDefaultValue->fValue, pushWarning, false, false );
						}
						catch(std::exception&)
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, "The default value is out of range for the specified data type.");
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}
						if (pushWarning)
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, "The default value is out of range for the specified data type.");
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}
					}
				}
				//Handle compression type
				string comment = addColumnsPtr->fColumns[0]->fComment;
				int compressionType = compressionTypeIn;
				if ( comment.length() > 0 )
				{
					compressionType = parseCompressionComment( comment);
					if ( compressionType == MAX_INT )
					{
						compressionType = compressionTypeIn;
					}
					else if ( compressionType < 0 )
					{
						rc = 1;
						thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_COMPRESSION_TYPE)).c_str());
						ci->alterTableState = cal_connection_info::NOT_ALTER;
						ci->isAlter = false;
						return rc;
					}

					if (( compressionType > 0 ) && !(erydbCompress.isCompressionAvail( compressionType )))
					{
						rc = 1;
						thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_COMPRESSION_TYPE)).c_str());
						ci->alterTableState = cal_connection_info::NOT_ALTER;
						ci->isAlter = false;
						return rc;
					}

					if ((compressionType ==0) && (useHdfs))
					{
						compressionType = 2;
						string errmsg ("The column is created with Erydb compression type 2 under HDFS." );
						push_warning(thd, Sql_condition::WARN_LEVEL_WARN, 9999, errmsg.c_str());
					}


					try {
						autoIncre = parseAutoincrementColumnComment(comment, startValue);
					}
					catch (runtime_error& ex)
					{
						rc = 1;
						thd->get_stmt_da()->set_overwrite_status(true);
						thd->raise_error_printf(ER_INTERNAL_ERROR, ex.what());
						ci->alterTableState = cal_connection_info::NOT_ALTER;
						ci->isAlter = false;
						return rc;
					}
					if (autoIncre)
					{
						//Check if the table already has autoincrement column
						boost::shared_ptr<erydbSystemCatalog> csc = erydbSystemCatalog::makeerydbSystemCatalog(sessionID);
						csc->identity(execplan::erydbSystemCatalog::FE);
						erydbSystemCatalog::TableName tableName;
						tableName.schema = alterTable->fTableName->fSchema;
						tableName.table = alterTable->fTableName->fName;
						erydbSystemCatalog::TableInfo tblInfo;
						try {
							tblInfo = csc->tableInfo(tableName);
						}
						catch (runtime_error& ex)
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, ex.what());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}

						if (tblInfo.tablewithautoincr == 1)
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_NUMBER_AUTOINCREMENT)).c_str());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}

						if (!validateAutoincrementDatatype(addColumnsPtr->fColumns[0]->fType->fType))
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_AUTOINCREMENT_TYPE)).c_str());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}
						if (!validateNextValue(addColumnsPtr->fColumns[0]->fType->fType, startValue))
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_STARTVALUE)).c_str());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}
						if (startValue <= 0)
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_NEGATIVE_STARTVALUE)).c_str());
							return rc;
						}
					}
				}
				addColumnsPtr->fColumns[0]->fType->fCompressiontype = compressionType;
				if (autoIncre)
					addColumnsPtr->fColumns[0]->fType->fAutoincrement = "y";
				else
					addColumnsPtr->fColumns[0]->fType->fAutoincrement = "n";

				addColumnsPtr->fColumns[0]->fType->fNextvalue = startValue;
			}
			else if (ddlpackage::AtaRenameColumn* renameColumnsPtr = dynamic_cast<AtaRenameColumn*>(actionList[i]))
			{
				//cout << "Rename a column" << endl;
				uint64_t startValue = 1;
				bool autoIncre  = false;
				//@Bug 3746 Handle compression type
				string comment = renameColumnsPtr->fComment;
				int compressionType = compressionTypeIn;
				if ( comment.length() > 0 )
				{
					compressionType = parseCompressionComment( comment);
					if ( compressionType == MAX_INT )
					{
						compressionType = compressionTypeIn;
					}
					else if ( compressionType < 0 )
					{
						rc = 1;
						thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_COMPRESSION_TYPE)).c_str());
						ci->alterTableState = cal_connection_info::NOT_ALTER;
						ci->isAlter = false;
						return rc;
					}

					if (( compressionType > 0 ) && !(erydbCompress.isCompressionAvail( compressionType )))
					{
						rc = 1;
						thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_COMPRESSION_TYPE)).c_str());
						ci->alterTableState = cal_connection_info::NOT_ALTER;
						ci->isAlter = false;
						return rc;
					}

					if ((compressionType ==0) && (useHdfs))
					{
						compressionType = 2;
						string errmsg ("The column is created with Erydb compression type 2 under HDFS." );
						push_warning(thd, Sql_condition::WARN_LEVEL_WARN, 9999, errmsg.c_str());
					}

				}

				//Handle autoincrement
				if ( comment.length() > 0 )
				{
					try {
						autoIncre = parseAutoincrementColumnComment(comment, startValue);
					}
					catch (runtime_error& ex)
					{
						rc = 1;
						thd->get_stmt_da()->set_overwrite_status(true);
						thd->raise_error_printf(ER_INTERNAL_ERROR, ex.what());
						ci->alterTableState = cal_connection_info::NOT_ALTER;
						ci->isAlter = false;
						return rc;
					}
					if (autoIncre)
					{
						//Check if the table already has autoincrement column
						erydbSystemCatalog::TableName tableName;
						tableName.schema = alterTable->fTableName->fSchema;
						tableName.table = alterTable->fTableName->fName;
						//erydbSystemCatalog::TableInfo tblInfo = csc->tableInfo(tableName);

						//@Bug 5444. rename column doen't need to check this.
					/*	if (tblInfo.tablewithautoincr == 1)
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_NUMBER_AUTOINCREMENT)).c_str());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						} */

						if (!validateAutoincrementDatatype(renameColumnsPtr->fNewType->fType))
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_AUTOINCREMENT_TYPE)).c_str());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}
						if (!validateNextValue(renameColumnsPtr->fNewType->fType, startValue))
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_STARTVALUE)).c_str());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}

					}
				}

				if (autoIncre)
					renameColumnsPtr->fNewType->fAutoincrement = "y";
				else
					renameColumnsPtr->fNewType->fAutoincrement = "n";

				renameColumnsPtr->fNewType->fNextvalue = startValue;
				renameColumnsPtr->fNewType->fCompressiontype = compressionType;

				if (renameColumnsPtr->fConstraints.size() > 0)
				{
					for (uint32_t j=0; j < renameColumnsPtr->fConstraints.size(); j++)
					{
						if (renameColumnsPtr->fConstraints[j]->fConstraintType == DDL_NOT_NULL)
						{
							//If NOT NULL constraint is added, check whether the existing rows has null vlues. If there is, error out the query.
							bool anyNullVal = false;
							try {
								anyNullVal = anyNullInTheColumn (alterTable->fTableName->fSchema, alterTable->fTableName->fName, renameColumnsPtr->fName, sessionID);
							}
							catch (runtime_error& ex)
							{
								rc = 1;
								thd->get_stmt_da()->set_overwrite_status(true);
								thd->raise_error_printf(ER_INTERNAL_ERROR, ex.what());
								ci->alterTableState = cal_connection_info::NOT_ALTER;
								ci->isAlter = false;
								return rc;
							}
							catch (...)
							{
								rc = 1;
								thd->get_stmt_da()->set_overwrite_status(true);
								thd->raise_error_printf(ER_INTERNAL_ERROR, "Unknown exception caught when checking any existing null values in the column.");
								ci->alterTableState = cal_connection_info::NOT_ALTER;
								ci->isAlter = false;
								return rc;
							}
							if (anyNullVal)
							{
								rc = 1;
								thd->get_stmt_da()->set_overwrite_status(true);
								thd->raise_error_printf(ER_INTERNAL_ERROR, "The existing rows in this column has null value already.");
								ci->alterTableState = cal_connection_info::NOT_ALTER;
								ci->isAlter = false;
								return rc;
							}
						}
						else
						{
							rc = 1;
							thd->get_stmt_da()->set_overwrite_status(true);
							thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, (ERYDBErrorInfo::instance()->errorMsg(ERR_CONSTRAINTS)).c_str());
							ci->alterTableState = cal_connection_info::NOT_ALTER;
							ci->isAlter = false;
							return rc;
						}
					}
				}
			}
			else
			{
			}
		}
	}
	//@Bug 5923 error out on unsupported statements.
	else if (( typeid ( stmt ) != typeid ( DropTableStatement )) && ( typeid ( stmt ) != typeid ( TruncTableStatement ))
		&& ( typeid ( stmt ) != typeid ( MarkPartitionStatement )) && ( typeid ( stmt ) != typeid ( RestorePartitionStatement )) 
		&& ( typeid ( stmt ) != typeid ( DropPartitionStatement )))
	{
		rc = 1;
		thd->get_stmt_da()->set_overwrite_status(true);
		thd->raise_error_printf(ER_INTERNAL_ERROR, (ERYDBErrorInfo::instance()->errorMsg(ERR_NON_SUPPORT_SYNTAX)).c_str());
		ci->alterTableState = cal_connection_info::NOT_ALTER;
		ci->isAlter = false;
		return rc;	
	}
	
	//@Bug 4387
	scoped_ptr<DBRM> dbrmp(new DBRM());
	int rc = dbrmp->isReadWrite();
	if (rc != 0 )
	{
		rc = 1;
		thd->get_stmt_da()->set_overwrite_status(true);
		thd->raise_error_printf(ER_INTERNAL_ERROR, "Cannot execute the statement. DBRM is read only!");
		ci->alterTableState = cal_connection_info::NOT_ALTER;
		ci->isAlter = false;
		return rc;
	}

	stmt.fSessionID = sessionID;
	stmt.fSql = ddlStatement;
	stmt.fOwner = schema;
	stmt.fTableWithAutoi = isAnyAutoincreCol;
	//cout << "Sending to DDLProc" << endl;
	ByteStream bytestream;
	bytestream << stmt.fSessionID;
	stmt.serialize(bytestream);
	MessageQueueClient mq("DDLProc");
	ByteStream::byte b=0;
	try
	{
	  mq.write(bytestream);
	  bytestream = mq.read();
	  if ( bytestream.length() == 0 )
	  {
		rc = 1;
	  	thd->get_stmt_da()->set_overwrite_status(true);

	  	thd->raise_error_printf(ER_INTERNAL_ERROR, "Lost connection to DDLProc");
		ci->alterTableState = cal_connection_info::NOT_ALTER;
		ci->isAlter = false;
	  }
	  else
	  {
	  	bytestream >> b;
	  	bytestream >> emsg;
	  	rc = b;
	  }
	}
	catch (runtime_error& e)
	{
	  rc =1;
	  thd->get_stmt_da()->set_overwrite_status(true);

	  thd->raise_error_printf(ER_INTERNAL_ERROR, "Lost connection to DDLProc");
	  ci->alterTableState = cal_connection_info::NOT_ALTER;
	  ci->isAlter = false;
	}
	catch (...)
	{
	  rc = 1;
	  thd->get_stmt_da()->set_overwrite_status(true);

	  thd->raise_error_printf(ER_INTERNAL_ERROR, "Unknown error caught");
	  ci->alterTableState = cal_connection_info::NOT_ALTER;
	  ci->isAlter = false;
	}

	if ((b != 0) && (b!=ddlpackageprocessor::DDLPackageProcessor::WARNING))
	{
	  thd->get_stmt_da()->set_overwrite_status(true);

	  thd->raise_error_printf(ER_INTERNAL_ERROR, emsg.c_str());
	}

	if (b ==ddlpackageprocessor::DDLPackageProcessor::WARNING)
	{
		rc = 0;
		string errmsg ("Error occured during file deletion. Restart DMLProc or use command tool ddlcleanup to clean up. " );
		push_warning(thd, Sql_condition::WARN_LEVEL_WARN, 9999, errmsg.c_str());
	}
	return rc;

  }
  else
  {
  	 rc = 1;
  	 thd->get_stmt_da()->set_overwrite_status(true);
	 //@Bug 3602. Error message for MySql syntax for autoincrement
	 algorithm::to_upper(ddlStatement);
	 if (ddlStatement.find("AUTO_INCREMENT") != string::npos)
	 {
		thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, "Use of the MySQL auto_increment syntax is not supported in Erydb. If you wish to create an auto increment column in Erydb, please consult the Erydb SQL Syntax Guide for the correct usage.");
		ci->alterTableState = cal_connection_info::NOT_ALTER;
		ci->isAlter = false;
	 }
	 else
	 {
		//@Bug 1888,1885. update error message
		thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, "The syntax or the data type(s) is not supported by Erydb. Please check the Erydb syntax guide for supported syntax or data types.");
		ci->alterTableState = cal_connection_info::NOT_ALTER;
		ci->isAlter = false;
	 }
  }
  return rc;
}

pair<string, string> parseTableName(const string& tn)
{
	string db;
	string tb;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
#ifdef _MSC_VER
	boost::char_separator<char> sep("\\");
#else
	boost::char_separator<char> sep("/");
#endif
	tokenizer tokens(tn, sep);
	tokenizer::iterator tok_iter = tokens.begin();
	++tok_iter;
	erydbassert(tok_iter != tokens.end());
	db = *tok_iter;
	++tok_iter;
	erydbassert(tok_iter != tokens.end());
	tb = *tok_iter;
	++tok_iter;
	erydbassert(tok_iter == tokens.end());
	return make_pair(db, tb);
}

}

int ha_erydb_impl_create_(const char *name, TABLE *table_arg, HA_CREATE_INFO *create_info, cal_connection_info& ci)
{
#ifdef ERYDB_DEBUG
	cout << "ha_erydb_impl_create_: " << name << endl;
#endif
	THD *thd = current_thd;

	char* query = thd->query();
	if (!query)
	{
		setError(thd, ER_INTERNAL_ERROR, "Attempt to create table, but query is NULL");
		return 1;
	}
	string stmt(query);
	stmt += ";";
	algorithm::to_upper(stmt);

	string db = table_arg->s->db.str;
	string tbl = table_arg->s->table_name.str;
	string tablecomment;
	bool isAnyAutoincreCol = false;
	std::string columnName("");
	uint64_t startValue = 1;
	if (table_arg->s->comment.length > 0 )
	{
		tablecomment = table_arg->s->comment.str;
		try {
			isAnyAutoincreCol = parseAutoincrementTableComment(tablecomment, startValue, columnName);
		}
		catch (runtime_error& ex)
		{
			setError(thd, ER_INTERNAL_ERROR, ex.what());
			return 1;
		}
		algorithm::to_upper(tablecomment);
	}
	//@Bug 2553 Add a parenthesis around option to group them together
	string alterpatstr("ALTER[[:space:]]+TABLE[[:space:]]+.*[[:space:]]+(((ADD)|(DROP)|(CHANGE)|(ALTER)|(COMMENT))[[:space:]]+|(COMMENT=))");
	string createpatstr("CREATE[[:space:]]+TABLE[[:space:]]");
	bool schemaSyncOnly = false;
	bool isCreate = true;

	// relate to bug 1793. Make sure this is not for a select statement because
	if (db == "erydbsys" && thd->erydb_vtable.vtable_state == THD::ERYDB_INIT
	    && tbl != "systable"
	    && tbl != "syscolumn" && tbl != "sysindex"
	    && tbl != "sysconstraint" && tbl != "sysindexcol"
	    && tbl != "sysconstraintcol" )
	{
		setError(thd, ER_INTERNAL_ERROR, "Cannot create non-system erydb tables in erydbsys database");
		return 1;
	}

	regex pat("[[:space:]]*SCHEMA[[:space:]]+SYNC[[:space:]]+ONLY", regex_constants::extended);
	if (regex_search(tablecomment, pat))
	{
		schemaSyncOnly = true;
		pat = createpatstr;
		if (!regex_search(stmt, pat)) 
		{
			isCreate = false;
		}
		if (isCreate)
		{
#ifdef ERYDB_DEBUG
			cout << "ha_erydb_impl_create_: SCHEMA SYNC ONLY found, returning" << endl;
#endif
			return 0;
		}
		if (thd->erydb_vtable.vtable_state == THD::ERYDB_ALTER_VTABLE) //check if it is select
		{
			return 0;
		}
	}
	else
	{
		if (db == "erydbsys")
		{
			setError(thd, ER_INTERNAL_ERROR, "erydb system tables can only be created with 'SCHEMA SYNC ONLY'");
			return 1;
		}
		else if ( db == "erydb_vtable") //@bug 3540. table created in erydb_vtable schema could be dropped when select statement happen to have same tablename.
		{
			setError(thd, ER_INTERNAL_ERROR, "Table creation is not allowed in erydb_vtable schema.");
			return 1;
		}
	}

	pat = alterpatstr;
	if (regex_search(stmt, pat)) {
		ci.isAlter = true;
		ci.alterTableState = cal_connection_info::ALTER_FIRST_RENAME;
#ifdef ERYDB_DEBUG
		cout << "ha_erydb_impl_create_: now in state ALTER_FIRST_RENAME" << endl;
#endif
	}

	string emsg;
	stmt = thd->query();
	stmt += ";";
	int rc = 0;

	// Don't do the DDL (only for create table if this is SSO. Should only get here on ATAC w/SSO.
	if ( schemaSyncOnly && isCreate)
		return rc;

	//this is replcated DDL, treat it just like SSO
	if (thd->slave_thread)
		return rc;

	//@bug 5660. Error out REAL DDL/DML on slave node.
	// When the statement gets here, it's NOT SSO or RESTRICT
	if (ci.isSlaveNode)
	{
		string emsg = logging::ERYDBErrorInfo::instance()->errorMsg(ERR_DML_DDL_SLAVE);
		setError(thd, ER_CHECK_NOT_IMPLEMENTED, emsg);
		return 1;
	}

	// @bug 3908. error out primary key for now.
	if (table_arg->key_info && table_arg->key_info->name && string(table_arg->key_info->name) == "PRIMARY")
	{
		string emsg = logging::ERYDBErrorInfo::instance()->errorMsg(ERR_CONSTRAINTS);
		setError(thd, ER_CHECK_NOT_IMPLEMENTED, emsg);
		ci.alterTableState = cal_connection_info::NOT_ALTER;
		ci.isAlter = false;
		return 1;
	}

	int compressiontype = thd->variables.erydb_compression_type;

	if (compressiontype == 1) compressiontype = 2;
	//string tablecomment;
	if (table_arg->s->comment.length > 0 )
	{
		tablecomment = table_arg->s->comment.str;
		compressiontype = parseCompressionComment( tablecomment );
	}
	if ( compressiontype == MAX_INT )
		compressiontype = thd->variables.erydb_compression_type;
	else if ( compressiontype < 0 )
	{
		string emsg = ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_COMPRESSION_TYPE);
		setError(thd, ER_INTERNAL_ERROR, emsg);
		ci.alterTableState = cal_connection_info::NOT_ALTER;
		ci.isAlter = false;
		return 1;
	}

	//hdfs
	if ((compressiontype ==0) && (useHdfs))
	{
		compressiontype = 2;
		push_warning(thd, Sql_condition::WARN_LEVEL_WARN, 9999, "The table is created with Erydb compression type 2 under HDFS.");
	}

	if (compressiontype == 1) compressiontype = 2;

	ERYDBCompressInterface erydbCompress;
	if ( ( compressiontype > 0 ) && !(erydbCompress.isCompressionAvail( compressiontype )) )
	{
		string emsg = ERYDBErrorInfo::instance()->errorMsg(ERR_INVALID_COMPRESSION_TYPE);
		setError(thd, ER_INTERNAL_ERROR, emsg);
		ci.alterTableState = cal_connection_info::NOT_ALTER;
		ci.isAlter = false;
		return 1;
	}

	rc = ProcessDDLStatement(stmt, db, tbl, tid2sid(thd->thread_id), emsg, compressiontype, isAnyAutoincreCol, startValue, columnName);

	if (rc != 0) {
		push_warning(thd, Sql_condition::WARN_LEVEL_WARN, 9999, emsg.c_str());
		//Bug 1705 reset the flag if error occurs
		ci.alterTableState = cal_connection_info::NOT_ALTER;
		ci.isAlter = false;
#ifdef ERYDB_DEBUG
		cout << "ha_erydb_impl_create_: ProcessDDL error, now in state NOT_ALTER" << endl;
#endif
	}
	return rc;
}

int ha_erydb_impl_delete_table_(const char *db, const char *name, cal_connection_info& ci)
{
#ifdef ERYDB_DEBUG
	cout << "ha_erydb_impl_delete_table: " << db << name << endl;
#endif
	THD *thd = current_thd;
	std::string tbl(name);
	std::string schema(db);
	char* query = thd->query();
	if (!query)
	{
		setError(thd, ER_INTERNAL_ERROR, "Attempt to drop table, but query is NULL");
		return 1;
	}
	std::string stmt(query);
	algorithm::to_upper(stmt);
	cout << "ha_erydb_impl_delete_table: " << schema.c_str() << "." << tbl.c_str() << " " << stmt.c_str() << endl;
	// @bug 4158 allow table name with 'restrict' in it (but not by itself)
	std::string::size_type fpos;
	fpos = stmt.rfind(" RESTRICT");
	if ((fpos != std::string::npos) && ((stmt.size() - fpos) == 9)) //last 9 chars of stmt are " RESTRICT"
	{
		return 0;
	}

	//this is replcated DDL, treat it just like SSO
	if (thd->slave_thread)
		return 0;

	//@bug 5660. Error out REAL DDL/DML on slave node.
	// When the statement gets here, it's NOT SSO or RESTRICT
	if (ci.isSlaveNode)
	{
		string emsg = logging::ERYDBErrorInfo::instance()->errorMsg(ERR_DML_DDL_SLAVE);
		setError(thd, ER_CHECK_NOT_IMPLEMENTED, emsg);
		return 1;
	}

	string emsg;
	if (thd->lex->sql_command == SQLCOM_DROP_DB)
	{
		std::string tableName(name);
		tableName.erase(0,tableName.rfind("/")+1);
		stmt = std::string("DROP TABLE ") + tableName;
	}
	else
	{
		stmt = thd->query();
	}
	stmt += ";";
	int rc = ProcessDDLStatement(stmt, schema, tbl, tid2sid(thd->thread_id), emsg);
	cout << "ProcessDDLStatement rc=" << rc << endl;
	if (rc != 0)
	{
		push_warning(thd, Sql_condition::WARN_LEVEL_WARN, 9999, emsg.c_str());
	}
	return rc;
}

int ha_erydb_impl_rename_table_(const char* from, const char* to, cal_connection_info& ci)
{
	THD *thd = current_thd;
	string emsg;

	ostringstream stmt1;
	pair<string, string> fromPair;
	pair<string, string> toPair;
	string stmt;

	//this is replcated DDL, treat it just like SSO
	if (thd->slave_thread)
		return 0;

	//@bug 5660. Error out REAL DDL/DML on slave node.
	// When the statement gets here, it's NOT SSO or RESTRICT
	if (ci.isSlaveNode)
	{
		string emsg = logging::ERYDBErrorInfo::instance()->errorMsg(ERR_DML_DDL_SLAVE);
		setError(current_thd, ER_CHECK_NOT_IMPLEMENTED, emsg);
		return 1;
	}

	fromPair = parseTableName(from);
	toPair = parseTableName(to);

	if (fromPair.first != toPair.first)
	{
		thd->get_stmt_da()->set_overwrite_status(true);
		thd->raise_error_printf(ER_CHECK_NOT_IMPLEMENTED, "Both tables must be in the same database to use RENAME TABLE");
		return -1;
	}

	stmt1 << "alter table " << fromPair.second << " rename to " << toPair.second << ";";

	stmt = stmt1.str();
	string db;
	if ( thd->db )
		db = thd->db;
	else if ( fromPair.first.length() !=0 )
		db = fromPair.first;
	else
		db = toPair.first;

	int rc = ProcessDDLStatement(stmt, db, "", tid2sid(thd->thread_id), emsg);
	if (rc != 0)
		push_warning(thd, Sql_condition::WARN_LEVEL_ERROR, 9999, emsg.c_str());

	return rc;
}


extern "C"
{

#ifdef _MSC_VER
__declspec(dllexport)
#endif
long long calonlinealter(UDF_INIT* initid, UDF_ARGS* args,
					char* is_null, char* error)
{
	string stmt(args->args[0], args->lengths[0]);

	string emsg;
	THD *thd = current_thd;
	string db("");
	if ( thd->db )
		db = thd->db;

	int compressiontype = thd->variables.erydb_compression_type;

	if (compressiontype == 1) compressiontype = 2;
	
	if ( compressiontype == MAX_INT )
		compressiontype = thd->variables.erydb_compression_type;

	//hdfs
	if ((compressiontype ==0) && (useHdfs))
	{
		compressiontype = 2;
	}

	if (compressiontype == 1) compressiontype = 2;
	
	int rc = ProcessDDLStatement(stmt, db, "", tid2sid(thd->thread_id), emsg, compressiontype);
	if (rc != 0)
		push_warning(thd, Sql_condition::WARN_LEVEL_ERROR, 9999, emsg.c_str());

	return rc;
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
my_bool calonlinealter_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
	if (args->arg_count != 1 || args->arg_type[0] != STRING_RESULT)
	{
		strcpy(message,"CALONLINEALTER() requires one string argument");
		return 1;
	}
	return 0;
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
void calonlinealter_deinit(UDF_INIT* initid)
{
}

}

// vim:ts=4 sw=4:
