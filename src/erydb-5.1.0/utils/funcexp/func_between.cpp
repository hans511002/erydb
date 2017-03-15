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

/****************************************************************************
* $Id: func_between.cpp 3954 2013-07-08 16:30:15Z bpaul $
*
*
****************************************************************************/

#include <cstdlib>
#include <string>
using namespace std;

#include "functor_bool.h"
#include "functioncolumn.h"
#include "predicateoperator.h"
#include "constantcolumn.h"
using namespace execplan;

#include "rowgroup.h"

#include "errorcodes.h"
#include "erydberrorinfo.h"
#include "errorids.h"
using namespace logging;

#include "utils_utf8.h"
using namespace funcexp;


namespace
{
	template<typename result_t>
	inline bool numericGE(result_t op1, result_t op2)
	{
		return op1 >= op2;
	}

	template<typename result_t>
	inline bool numericLE(result_t op1, result_t op2)
	{
		return op1 <= op2;
	}

	inline bool strGE(const string& op1, const string& op2)
	{
		//return strcoll(op1.c_str(), op2.c_str()) >= 0;
		return utf8::erydb_strcoll(op1.c_str(), op2.c_str()) >= 0;
	}

	inline bool strLE(const string& op1, const string& op2)
	{
		//return strcoll(op1.c_str(), op2.c_str()) <= 0;
		return utf8::erydb_strcoll(op1.c_str(), op2.c_str()) <= 0;
	}

	inline bool getBool(rowgroup::Row& row,
							funcexp::FunctionParm& pm,
							bool& isNull,
							erydbSystemCatalog::ColType& ct,
							bool notBetween)
	{
		switch (ct.colDataType)
		{
			case execplan::erydbSystemCatalog::BIGINT:
			case execplan::erydbSystemCatalog::INT:
			case execplan::erydbSystemCatalog::MEDINT:
			case execplan::erydbSystemCatalog::TINYINT:
			case execplan::erydbSystemCatalog::SMALLINT:
			{
				int64_t val = pm[0]->data()->getIntVal(row, isNull);
				if (notBetween)
				{
					if (!numericGE(val, pm[1]->data()->getIntVal(row, isNull)) && !isNull)
						return true;
					isNull = false;
					return (!numericLE(val, pm[2]->data()->getIntVal(row, isNull)) && !isNull);
				}
				return !isNull &&
						numericGE(val, pm[1]->data()->getIntVal(row, isNull)) &&
						numericLE(val, pm[2]->data()->getIntVal(row, isNull)) && !isNull;
			}
            case execplan::erydbSystemCatalog::UBIGINT:
            case execplan::erydbSystemCatalog::UINT:
            case execplan::erydbSystemCatalog::UMEDINT:
            case execplan::erydbSystemCatalog::UTINYINT:
            case execplan::erydbSystemCatalog::USMALLINT:
            {
                uint64_t val = pm[0]->data()->getUintVal(row, isNull);
                if (notBetween)
                {
                    if (!numericGE(val, pm[1]->data()->getUintVal(row, isNull)) && !isNull)
                        return true;
                    isNull = false;
                    return (!numericLE(val, pm[2]->data()->getUintVal(row, isNull)) && !isNull);
                }
                return !isNull &&
                        numericGE(val, pm[1]->data()->getUintVal(row, isNull)) &&
                        numericLE(val, pm[2]->data()->getUintVal(row, isNull)) && !isNull;
            }
			case execplan::erydbSystemCatalog::DATE:
			{
				int32_t val = pm[0]->data()->getDateIntVal(row, isNull);
				if (notBetween)
				{
					if (!numericGE(val, pm[1]->data()->getDateIntVal(row, isNull)) && !isNull)
						return true;
					isNull = false;
					return (!numericLE(val, pm[2]->data()->getDateIntVal(row, isNull)) && !isNull);
				}
				return !isNull &&
						numericGE(val, pm[1]->data()->getDateIntVal(row, isNull)) &&
						numericLE(val, pm[2]->data()->getDateIntVal(row, isNull));
			}
			case execplan::erydbSystemCatalog::DATETIME:
			{
				int64_t val = pm[0]->data()->getDatetimeIntVal(row, isNull);
				if (notBetween)
				{
					if (!numericGE(val, pm[1]->data()->getDatetimeIntVal(row, isNull)) && !isNull)
						return true;
					isNull = false;
					return (!numericLE(val, pm[2]->data()->getDatetimeIntVal(row, isNull)) && !isNull);
				}
				return !isNull &&
						numericGE(val, pm[1]->data()->getDatetimeIntVal(row, isNull)) &&
						numericLE(val, pm[2]->data()->getDatetimeIntVal(row, isNull));
			}
			case execplan::erydbSystemCatalog::DOUBLE:
            case execplan::erydbSystemCatalog::UDOUBLE:
			case execplan::erydbSystemCatalog::FLOAT:
            case execplan::erydbSystemCatalog::UFLOAT:
			{
				double val = pm[0]->data()->getDoubleVal(row, isNull);
				if (notBetween)
				{
					if (!numericGE(val, pm[1]->data()->getDoubleVal(row, isNull)) && !isNull)
						return true;
					isNull = false;
					return (!numericLE(val, pm[2]->data()->getDoubleVal(row, isNull)) && !isNull);
				}
				return !isNull &&
						numericGE(val, pm[1]->data()->getDoubleVal(row, isNull)) &&
						numericLE(val, pm[2]->data()->getDoubleVal(row, isNull));
			}
            case execplan::erydbSystemCatalog::DECIMAL:
			case execplan::erydbSystemCatalog::UDECIMAL:
			{
				ERYDB_Decimal val = pm[0]->data()->getDecimalVal(row, isNull);
				if (notBetween)
				{
					if (!numericGE(val, pm[1]->data()->getDecimalVal(row, isNull)) && !isNull)
						return true;
					isNull = false;
					return (!numericLE(val, pm[2]->data()->getDecimalVal(row, isNull)) && !isNull);
				}
				return !isNull &&
						numericGE(val, pm[1]->data()->getDecimalVal(row, isNull)) &&
						numericLE(val, pm[2]->data()->getDecimalVal(row, isNull));
			}
			case execplan::erydbSystemCatalog::VARCHAR: // including CHAR'
			case execplan::erydbSystemCatalog::CHAR:
			{
				const string& val = pm[0]->data()->getStrVal(row, isNull);
				if (notBetween)
				{
					if (!strGE(val, pm[1]->data()->getStrVal(row, isNull)) && !isNull)
						return true;
					isNull = false;
					return (!strLE(val, pm[2]->data()->getStrVal(row, isNull)) && !isNull);
				}
				return !isNull &&
						strGE(val, pm[1]->data()->getStrVal(row, isNull)) &&
						strLE(val, pm[2]->data()->getStrVal(row, isNull));
			}
			default:
			{
				std::ostringstream oss;
				oss << "between: datatype of " << execplan::colDataTypeToString(ct.colDataType);
				throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
			}
		}
	}

}

namespace funcexp
{

erydbSystemCatalog::ColType Func_between::operationType( FunctionParm& fp, erydbSystemCatalog::ColType& resultType )
{
	PredicateOperator op;
	erydbSystemCatalog::ColType ct = fp[0]->data()->resultType();
	//op.operationType(fp[0]->data()->resultType());
	bool allString = true;

	for (uint32_t i = 1; i < fp.size(); i++)
	{
		//op.setOpType(op.operationType(), fp[i]->data()->resultType());
		op.setOpType(ct, fp[i]->data()->resultType());
		ct = op.operationType();

		if ((fp[i]->data()->resultType().colDataType != erydbSystemCatalog::CHAR &&
			fp[i]->data()->resultType().colDataType != erydbSystemCatalog::VARCHAR) || 
			ct.colDataType == erydbSystemCatalog::DATE ||
			ct.colDataType == erydbSystemCatalog::DATETIME)
		{
			allString = false;
		}
	}

	if (allString)
	{
		ct.colDataType = erydbSystemCatalog::VARCHAR;
		ct.colWidth = 255;
	}

	else if (op.operationType().colDataType == erydbSystemCatalog::DATETIME)
	{
		ConstantColumn *cc = NULL;
		for (uint32_t i = 1; i < fp.size(); i++)
		{
			cc = dynamic_cast<ConstantColumn*>(fp[i]->data());
			if (cc)
			{
				Result result = cc->result();
				result.intVal = dataconvert::DataConvert::datetimeToInt(result.strVal);
				cc->result(result);
			}
		}
	}
	return ct;
}

bool Func_between::getBoolVal(rowgroup::Row& row,
							FunctionParm& pm,
							bool& isNull,
							erydbSystemCatalog::ColType& ct)
{
	return getBool(row, pm, isNull, ct, false) && !isNull;
}





erydbSystemCatalog::ColType Func_notbetween::operationType( FunctionParm& fp, erydbSystemCatalog::ColType& resultType )
{
	PredicateOperator *op = new PredicateOperator();
	erydbSystemCatalog::ColType ct;
	op->setOpType(fp[0]->data()->resultType(), fp[1]->data()->resultType());
	op->setOpType(op->resultType(), fp[2]->data()->resultType());
	return op->operationType();
}

bool Func_notbetween::getBoolVal(rowgroup::Row& row,
							FunctionParm& pm,
							bool& isNull,
							erydbSystemCatalog::ColType& ct)
{
	return getBool(row, pm, isNull, ct, true) && !isNull;
}


} // namespace funcexp
// vim:ts=4 sw=4:
