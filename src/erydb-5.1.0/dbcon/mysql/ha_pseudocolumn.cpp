#include "erydb_mysql.h"
//#include <cmath>
#include <iostream>
#include <sstream>
using namespace std;
 
#include "errorids.h"
#include "erydberrorinfo.h"
#include "exceptclasses.h"
using namespace logging;

#include "pseudocolumn.h"
#include "functioncolumn.h"
#include "constantcolumn.h"
using namespace execplan;

#include "functor.h"
#include "functor_str.h"

#include "ha_erydb_impl_if.h"
using namespace cal_impl_if;

namespace {

/*******************************************************************************
 * Pseudo column connector interface
 *
 * erydbdbroot
 * erydbpm
 * erydbextentrelativerid
 * erydbsegmentdir
 * erydbsegment
 * erydbpartition
 * erydbextentmin
 * erydbextentmax
 * erydbextentid
 * erydbblockid
 *
 * All the pseudo column functions are only executed in EryDB.
 */

void bailout(char* error, const string& funcName)
{
	string errMsg = ERYDBErrorInfo::instance()->errorMsg(ERR_PSEUDOCOL_ERYDB_ONLY, funcName);
	current_thd->get_stmt_da()->set_overwrite_status(true);
    current_thd->raise_error_printf(ER_INTERNAL_ERROR, errMsg.c_str());
	*error = 1;
}

int64_t erydblocalpm()
{
	THD* thd = current_thd;
	if (!thd->erydb_vtable.cal_conn_info)
		thd->erydb_vtable.cal_conn_info = (void*)(new cal_connection_info());
	cal_connection_info* ci = reinterpret_cast<cal_connection_info*>(thd->erydb_vtable.cal_conn_info);

	if (ci->localPm == -1)
	{
		string module = ClientRotator::getModule();
		if (module.size() >= 3 && (module[0] == 'p' || module[0] == 'P'))
			ci->localPm = atol(module.c_str()+2);
		else
			ci->localPm = 0;
	}
	return ci->localPm;
}

extern "C"
{
/**
 * ERYDBDBROOT
 */
#ifdef _MSC_VER
__declspec(dllexport)
#endif
my_bool erydbdbroot_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
	if (args->arg_count != 1)
	{
		strcpy(message,"erydbdbroot() requires one argument");
		return 1;
	}

	return 0;
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
void erydbdbroot_deinit(UDF_INIT* initid)
{
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
long long erydbdbroot(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
	bailout(error, "erydbdbroot");
	return 0;
}

/**
 * ERYDBPM
 */

#ifdef _MSC_VER
__declspec(dllexport)
#endif
my_bool erydbpm_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
	if (args->arg_count != 1)
	{
		strcpy(message,"erydbpm() requires one argument");
		return 1;
	}

	return 0;
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
void erydbpm_deinit(UDF_INIT* initid)
{
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
long long erydbpm(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
	bailout(error, "erydbpm");
	return 0;
}

/**
 * ERYDBEXTENTRELATIVERID
 */

#ifdef _MSC_VER
__declspec(dllexport)
#endif
my_bool erydbextentrelativerid_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
	if (args->arg_count != 1)
	{
		strcpy(message,"erydbextentrelativerid() requires one argument");
		return 1;
	}

	return 0;
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
void erydbextentrelativerid_deinit(UDF_INIT* initid)
{
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
long long erydbextentrelativerid(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
	bailout(error, "erydbextentrelativerid");
	return 0;
}

/**
 * ERYDBBLOCKID
 */

#ifdef _MSC_VER
__declspec(dllexport)
#endif
my_bool erydbblockid_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
	if (args->arg_count != 1)
	{
		strcpy(message,"erydbblockid() requires one argument");
		return 1;
	}

	return 0;
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
void erydbblockid_deinit(UDF_INIT* initid)
{
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
long long erydbblockid(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
	bailout(error, "erydbblockid");
	return 0;
}

/**
 * ERYDBEXTENTID
 */

#ifdef _MSC_VER
__declspec(dllexport)
#endif
my_bool erydbextentid_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
	if (args->arg_count != 1)
	{
		strcpy(message,"erydbextentid() requires one argument");
		return 1;
	}

	return 0;
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
void erydbextentid_deinit(UDF_INIT* initid)
{
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
long long erydbextentid(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
	bailout(error, "erydbextentid");
	return 0;
}

/**
 * ERYDBSEGMENT
 */

#ifdef _MSC_VER
__declspec(dllexport)
#endif
my_bool erydbsegment_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
	if (args->arg_count != 1)
	{
		strcpy(message,"erydbsegment() requires one argument");
		return 1;
	}

	return 0;
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
void erydbsegment_deinit(UDF_INIT* initid)
{
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
long long erydbsegment(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
	bailout(error, "erydbsegment");
	return 0;
}

/**
 * ERYDBSEGMENTDIR
 */

#ifdef _MSC_VER
__declspec(dllexport)
#endif
my_bool erydbsegmentdir_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
	if (args->arg_count != 1)
	{
		strcpy(message,"erydbsegmentdir() requires one argument");
		return 1;
	}

	return 0;
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
void erydbsegmentdir_deinit(UDF_INIT* initid)
{
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
long long erydbsegmentdir(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
	bailout(error, "erydbsegmentdir");
	return 0;
}

/**
 * ERYDBPARTITION
 */

#ifdef _MSC_VER
__declspec(dllexport)
#endif
my_bool erydbpartition_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
	if (args->arg_count != 1)
	{
		strcpy(message,"erydbpartition() requires one argument");
		return 1;
	}

	return 0;
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
void erydbpartition_deinit(UDF_INIT* initid)
{
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
const char* erydbpartition(UDF_INIT* initid, UDF_ARGS* args,
					char* result, unsigned long* length,
					char* is_null, char* error)
{
	bailout(error, "erydbpartition");
	return result;
}

/**
 * ERYDBEXTENTMIN
 */

#ifdef _MSC_VER
__declspec(dllexport)
#endif
my_bool erydbextentmin_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
	if (args->arg_count != 1)
	{
		strcpy(message,"erydbpm() requires one argument");
		return 1;
	}
	initid->maybe_null = 1;
	return 0;
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
void erydbextentmin_deinit(UDF_INIT* initid)
{
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
const char* erydbextentmin(UDF_INIT* initid, UDF_ARGS* args,
                         char* result, unsigned long* length,
                         char* is_null, char* error)
{
	bailout(error, "erydbextentmin");
	return result;
}

/**
 * ERYDBEXTENTMAX
 */

#ifdef _MSC_VER
__declspec(dllexport)
#endif
my_bool erydbextentmax_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
	if (args->arg_count != 1)
	{
		strcpy(message,"erydbextentmax() requires one argument");
		return 1;
	}
	initid->maybe_null = 1;
	return 0;
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
void erydbextentmax_deinit(UDF_INIT* initid)
{
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
const char* erydbextentmax(UDF_INIT* initid, UDF_ARGS* args,
                         char* result, unsigned long* length,
                         char* is_null, char* error)
{
	bailout(error, "erydbextentmax");
	return result;
}

/**
 * ERYDBLOCALPM
 */

#ifdef _MSC_VER
__declspec(dllexport)
#endif
my_bool erydblocalpm_init(UDF_INIT* initid, UDF_ARGS* args, char* message)
{
	if (args->arg_count != 0)
	{
		strcpy(message,"erydblocalpm() should take no argument");
		return 1;
	}
	initid->maybe_null = 1;
	return 0;
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
void erydblocalpm_deinit(UDF_INIT* initid)
{
}

#ifdef _MSC_VER
__declspec(dllexport)
#endif
long long erydblocalpm(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
	longlong localpm = erydblocalpm();
	if (localpm == 0)
		*is_null = 1;
	return localpm;
}

}

}

namespace cal_impl_if {

ReturnedColumn* nullOnError(gp_walk_info& gwi, string& funcName)
{
	gwi.fatalParseError = true;
	gwi.parseErrorText =
	   logging::ERYDBErrorInfo::instance()->errorMsg(logging::ERR_PSEUDOCOL_WRONG_ARG, funcName);
	return NULL;
}

uint32_t isPseudoColumn(string funcName)
{
	return execplan::PseudoColumn::pseudoNameToType(funcName);
}

execplan::ReturnedColumn* buildPseudoColumn(Item* item,
                                            gp_walk_info& gwi,
                                            bool& nonSupport,
                                            uint32_t pseudoType)
{
	if (!(gwi.thd->erydb_vtable.cal_conn_info))
		gwi.thd->erydb_vtable.cal_conn_info = (void*)(new cal_connection_info());
	cal_connection_info* ci = reinterpret_cast<cal_connection_info*>(gwi.thd->erydb_vtable.cal_conn_info);

	Item_func* ifp = (Item_func*)item;

	// erydblocalpm is replaced by constant
	if (pseudoType == PSEUDO_LOCALPM)
	{
		int64_t localPm = erydblocalpm();
		ConstantColumn* cc;
		if (localPm)
			cc = new ConstantColumn(localPm);
		else
			cc = new ConstantColumn("", ConstantColumn::NULLDATA);
		cc->alias(ifp->full_name() ? ifp->full_name() : "");
		return cc;
	}

	// convert udf item to pseudocolumn item.
	// adjust result type
	// put arg col to column map
	string funcName = ifp->func_name();
	if (ifp->argument_count() != 1 ||
	    !(ifp->arguments()) ||
	    !(ifp->arguments()[0]) ||
	    ifp->arguments()[0]->type() != Item::FIELD_ITEM)
		return nullOnError(gwi, funcName);

	Item_field* field = (Item_field*)(ifp->arguments()[0]);

	// @todo rule out derive table
	if (!field->field || !field->db_name || strlen(field->db_name) == 0)
		return nullOnError(gwi, funcName);

	SimpleColumn *sc = buildSimpleColumn(field, gwi);
	if (!sc)
		return nullOnError(gwi, funcName);

	if ((pseudoType == PSEUDO_EXTENTMIN || pseudoType == PSEUDO_EXTENTMAX) &&
	   (sc->colType().colDataType == erydbSystemCatalog::VARBINARY ||
	   (sc->colType().colDataType == erydbSystemCatalog::VARCHAR && sc->colType().colWidth > 7) ||
	   (sc->colType().colDataType == erydbSystemCatalog::CHAR && sc->colType().colWidth > 8)))
		return nullOnError(gwi, funcName);

	// put arg col to column map
	if (gwi.clauseType == SELECT || gwi.clauseType == GROUP_BY) // select clause
	{
		SRCP srcp(sc);
		gwi.columnMap.insert(erydbSelectExecutionPlan::ColumnMap::value_type(sc->columnName(), srcp));
		gwi.tableMap[make_aliastable(sc->schemaName(), sc->tableName(), sc->tableAlias(), sc->isEryDB())] =
		       make_pair(1, field->cached_table);
	}
	else if (!gwi.rcWorkStack.empty())
	{
		gwi.rcWorkStack.pop();
	}

	if (pseudoType == PSEUDO_PARTITION)
	{
		// parms: psueducolumn dbroot, segmentdir, segment
		SPTP sptp;
		FunctionColumn *fc = new FunctionColumn(funcName);
		funcexp::FunctionParm parms;
		PseudoColumn *dbroot = new PseudoColumn(*sc, PSEUDO_DBROOT);
		sptp.reset(new ParseTree(dbroot));
		parms.push_back(sptp);
		PseudoColumn *pp = new PseudoColumn(*sc, PSEUDO_SEGMENTDIR);
		sptp.reset(new ParseTree(pp));
		parms.push_back(sptp);
		PseudoColumn* seg = new PseudoColumn(*sc, PSEUDO_SEGMENT);
		sptp.reset(new ParseTree(seg));
		parms.push_back(sptp);
		fc->functionParms(parms);
		fc->expressionId(ci->expressionId++);

		// string result type
		erydbSystemCatalog::ColType ct;
		ct.colDataType = erydbSystemCatalog::VARCHAR;
		ct.colWidth = 256;
		fc->resultType(ct);

		// operation type integer
		funcexp::Func_erydbpartition* erydbpartition = new funcexp::Func_erydbpartition();
		fc->operationType(erydbpartition->operationType(parms, fc->resultType()));
		fc->alias(ifp->full_name() ? ifp->full_name() : "");
		return fc;
	}

	PseudoColumn *pc = new PseudoColumn(*sc, pseudoType);

	// @bug5892. set alias for derived table column matching.
	pc->alias(ifp->name? ifp->name : "");
	return pc;
}

}
// vim:ts=4 sw=4:

