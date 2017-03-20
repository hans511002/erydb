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
* $Id: func_if.cpp 3871 2013-06-07 16:25:01Z bpaul $
*
*
****************************************************************************/

#include <string>
using namespace std;

#include "functor_all.h"
#include "functioncolumn.h"
#include "predicateoperator.h"
using namespace execplan;

#include "rowgroup.h"
using namespace rowgroup;

namespace
{

bool boolVal(SPTP& parm, Row& row, bool& isNull)
{
	bool ret = true;
	try
	{
		ret = parm->getBoolVal(row, isNull);
	}
	catch (logging::NotImplementedExcept&)
	{
		switch (parm->data()->resultType().colDataType)
		{
			case erydbSystemCatalog::CHAR:
			case erydbSystemCatalog::VARCHAR:
				ret = (atoi((char*)(parm->data()->getStrVal().c_str())) != 0);
            case erydbSystemCatalog::FLOAT:
			case erydbSystemCatalog::UFLOAT:
				ret = (parm->data()->getFloatVal(row, isNull) != 0);
			case erydbSystemCatalog::DOUBLE:
            case erydbSystemCatalog::UDOUBLE:
				ret = (parm->data()->getDoubleVal(row, isNull) != 0);
            case erydbSystemCatalog::DECIMAL:
            case erydbSystemCatalog::UDECIMAL:
				ret = (parm->data()->getDecimalVal(row, isNull).value != 0);
			case erydbSystemCatalog::BIGINT:
			case erydbSystemCatalog::SMALLINT:
			case erydbSystemCatalog::MEDINT:
			case erydbSystemCatalog::INT:
            case erydbSystemCatalog::UBIGINT:
            case erydbSystemCatalog::USMALLINT:
            case erydbSystemCatalog::UMEDINT:
            case erydbSystemCatalog::UINT:
			case erydbSystemCatalog::DATE:
			case erydbSystemCatalog::DATETIME:
			default:
				ret = (parm->data()->getIntVal(row, isNull) != 0);
		}
	}

	return ret;
}

}


namespace funcexp
{

// IF(expression1, expression12, expression3)
//
// if parm order:
//   expression1 expression2 expression3
//
erydbSystemCatalog::ColType Func_if::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	// The result type given by the connector may not be right if there's derived table (MySQL bug?)
	// We want to double check on our own.
	// If any parm is of string type, the result type should be string.
	if (fp[1]->data()->resultType().colDataType == erydbSystemCatalog::CHAR ||
		  fp[1]->data()->resultType().colDataType == erydbSystemCatalog::VARCHAR ||
		  fp[2]->data()->resultType().colDataType == erydbSystemCatalog::CHAR ||
		  fp[2]->data()->resultType().colDataType == erydbSystemCatalog::VARCHAR)
	{
		erydbSystemCatalog::ColType ct;
		ct.colDataType = erydbSystemCatalog::VARCHAR;
		ct.colWidth = 255;
		resultType = ct;
		return ct;
	}

	erydbSystemCatalog::ColType ct = fp[1]->data()->resultType();
	PredicateOperator op;
	op.setOpType(ct, fp[2]->data()->resultType());
	ct = op.operationType();
	resultType = ct;
	return ct;
}


int64_t Func_if::getIntVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	if (boolVal(parm[0], row, isNull) && !isNull)
	{
		return parm[1]->data()->getIntVal(row, isNull);
	}
	else
	{
		isNull = false;
		return parm[2]->data()->getIntVal(row, isNull);
	}
}


string Func_if::getStrVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{

	if (boolVal(parm[0], row, isNull))
	{
		isNull = false;
		return parm[1]->data()->getStrVal(row, isNull);
	}
	else
	{
		isNull = false;
		return parm[2]->data()->getStrVal(row, isNull);
	}
}


ERYDB_Decimal Func_if::getDecimalVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	if (boolVal(parm[0], row, isNull))
	{
		isNull = false;
		return parm[1]->data()->getDecimalVal(row, isNull);
	}
	else
	{
		isNull = false;
		return parm[2]->data()->getDecimalVal(row, isNull);
	}
}


double Func_if::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	if (boolVal(parm[0], row, isNull))
	{
		isNull = false;
		return parm[1]->data()->getDoubleVal(row, isNull);
	}
	else
	{
		isNull = false;
		return parm[2]->data()->getDoubleVal(row, isNull);
	}
}


int32_t Func_if::getDateIntVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	if (boolVal(parm[0], row, isNull))
	{
		isNull = false;
		return parm[1]->data()->getDateIntVal(row, isNull);
	}
	else
	{
		isNull = false;
		return parm[2]->data()->getDateIntVal(row, isNull);
	}
}


int64_t Func_if::getDatetimeIntVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	if (boolVal(parm[0], row, isNull))
	{
		isNull = false;
		return parm[1]->data()->getDatetimeIntVal(row, isNull);
	}
	else
	{
		isNull = false;
		return parm[2]->data()->getDatetimeIntVal(row, isNull);
	}
}


} // namespace funcexp
// vim:ts=4 sw=4:
