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
* $Id: func_ceil.cpp 3923 2013-06-19 21:43:06Z bwilkinson $
*
*
****************************************************************************/

#include <cstdlib>
#include <iomanip>
#include <string>
using namespace std;

#include "functor_real.h"
#include "functioncolumn.h"
using namespace execplan;

#include "rowgroup.h"
using namespace rowgroup;

#include "errorcodes.h"
#include "erydberrorinfo.h"
#include "errorids.h"
using namespace logging;
using namespace dataconvert;

#include "funchelpers.h"

namespace funcexp
{

erydbSystemCatalog::ColType Func_ceil::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	return fp[0]->data()->resultType();
}


int64_t Func_ceil::getIntVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType& op_ct)
{
	int64_t ret = 0;

	switch (op_ct.colDataType)
	{
		case erydbSystemCatalog::BIGINT:
		case erydbSystemCatalog::INT:
		case erydbSystemCatalog::MEDINT:
		case erydbSystemCatalog::TINYINT:
		case erydbSystemCatalog::SMALLINT:
		case erydbSystemCatalog::DECIMAL:
        case erydbSystemCatalog::UDECIMAL:
		{
            if (op_ct.scale == 0)
            {
                ret = parm[0]->data()->getIntVal(row, isNull);
                break;
            }

			ERYDB_Decimal decimal = parm[0]->data()->getDecimalVal(row, isNull);

			if (isNull)
				break;

			ret = decimal.value;
			// negative scale is not supported by CNX yet
			if (decimal.scale > 0)
			{

				if (decimal.scale >= 19)
				{
					std::ostringstream oss;
					oss << "ceil: datatype of " << colDataTypeToString(op_ct.colDataType)
						<< " with scale " << (int) decimal.scale << " is beyond supported scale";
					throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
				}

				// Adjust to an int based on the scale.
				int64_t tmp = ret;
				ret /= helpers::powerOf10_c[decimal.scale];

				// Add 1 if this is a positive number and there were values to the right of the
				// decimal point so that we return the largest integer value not less than X.
				if ((tmp - (ret * helpers::powerOf10_c[decimal.scale]) > 0))
				ret += 1;
			}
		}
		break;
        case erydbSystemCatalog::UBIGINT:
        case erydbSystemCatalog::UINT:
        case erydbSystemCatalog::UMEDINT:
        case erydbSystemCatalog::UTINYINT:
        case erydbSystemCatalog::USMALLINT:
        {
            ret = (int64_t)(parm[0]->data()->getUintVal(row, isNull));
        }
        break;
		case erydbSystemCatalog::DOUBLE:
        case erydbSystemCatalog::UDOUBLE:
		case erydbSystemCatalog::FLOAT:
        case erydbSystemCatalog::UFLOAT:
		{
			ret = (int64_t) ceil(parm[0]->data()->getDoubleVal(row, isNull));
		}
		break;

		case erydbSystemCatalog::VARCHAR:
		case erydbSystemCatalog::CHAR:
		{
			const string& str = parm[0]->data()->getStrVal(row, isNull);
			if (!isNull)
				ret = (int64_t) ceil(strtod(str.c_str(), 0));
		}
		break;

		case erydbSystemCatalog::DATE:
		{
			Date d (parm[0]->data()->getDateIntVal(row, isNull));
			if (!isNull)
				ret = d.convertToMySQLint();
		}
		break;

		case erydbSystemCatalog::DATETIME:
		{
			DateTime dt(parm[0]->data()->getDatetimeIntVal(row, isNull));

			if (!isNull)
				ret = dt.convertToMySQLint();
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "ceil: datatype of " << colDataTypeToString(op_ct.colDataType)
				<< " is not supported";
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}
	return ret;
}

uint64_t Func_ceil::getUintVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType& op_ct)
{
	uint64_t ret = 0;

	switch (op_ct.colDataType)
	{
		case erydbSystemCatalog::BIGINT:
		case erydbSystemCatalog::INT:
		case erydbSystemCatalog::MEDINT:
		case erydbSystemCatalog::TINYINT:
		case erydbSystemCatalog::SMALLINT:
		case erydbSystemCatalog::DECIMAL:
        case erydbSystemCatalog::UDECIMAL:
		{
            ret = (uint64_t)parm[0]->data()->getIntVal(row, isNull);
        }
		break;
        case erydbSystemCatalog::UBIGINT:
        case erydbSystemCatalog::UINT:
        case erydbSystemCatalog::UMEDINT:
        case erydbSystemCatalog::UTINYINT:
        case erydbSystemCatalog::USMALLINT:
        {
            ret = (parm[0]->data()->getUintVal(row, isNull));
        }
        break;
		case erydbSystemCatalog::DOUBLE:
        case erydbSystemCatalog::UDOUBLE:
		case erydbSystemCatalog::FLOAT:
        case erydbSystemCatalog::UFLOAT:
		{
			ret = (uint64_t) ceil(parm[0]->data()->getDoubleVal(row, isNull));
		}
		break;

		case erydbSystemCatalog::VARCHAR:
		case erydbSystemCatalog::CHAR:
		{
			const string& str = parm[0]->data()->getStrVal(row, isNull);
			if (!isNull)
				ret = (uint64_t) ceil(strtod(str.c_str(), 0));
		}
		break;

		case erydbSystemCatalog::DATE:
		{
            Date d (parm[0]->data()->getDateIntVal(row, isNull));
            if (!isNull)
                ret = d.convertToMySQLint();
		}
		break;

		case erydbSystemCatalog::DATETIME:
		{
            DateTime dt(parm[0]->data()->getDatetimeIntVal(row, isNull));

            if (!isNull)
                ret = dt.convertToMySQLint();
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "ceil: datatype of " << colDataTypeToString(op_ct.colDataType)
				<< " is not supported";
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}
	return ret;
}


double Func_ceil::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType& op_ct)
{
	double ret = 0.0;
	if (op_ct.colDataType == erydbSystemCatalog::DOUBLE ||
        op_ct.colDataType == erydbSystemCatalog::UDOUBLE ||
        op_ct.colDataType == erydbSystemCatalog::FLOAT ||
		op_ct.colDataType == erydbSystemCatalog::UFLOAT)
	{
		ret = ceil(parm[0]->data()->getDoubleVal(row, isNull));
	}
	else if (op_ct.colDataType == erydbSystemCatalog::VARCHAR ||
			 op_ct.colDataType == erydbSystemCatalog::CHAR)
	{
		const string& str = parm[0]->data()->getStrVal(row, isNull);
		if (!isNull)
			ret = ceil(strtod(str.c_str(), 0));
	}
	else
	{
        if (isUnsigned(op_ct.colDataType))
        {
            ret = (double) getUintVal(row, parm, isNull, op_ct);
        }
        else
        {
            ret = (double) getIntVal(row, parm, isNull, op_ct);
        }
	}

	return ret;
}


string Func_ceil::getStrVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType& op_ct)
{
	char tmp[512] = {'\0'};
	if (op_ct.colDataType == erydbSystemCatalog::DOUBLE ||
        op_ct.colDataType == erydbSystemCatalog::UDOUBLE ||
		op_ct.colDataType == erydbSystemCatalog::FLOAT ||
        op_ct.colDataType == erydbSystemCatalog::UFLOAT ||
		op_ct.colDataType == erydbSystemCatalog::VARCHAR ||
		op_ct.colDataType == erydbSystemCatalog::CHAR)
	{
		snprintf(tmp, 511, "%f", getDoubleVal(row, parm, isNull, op_ct));

		// remove the decimals in the oss string.
		char *d = tmp;
		while ((*d != '.') && (*d != '\0'))
			d++;
		*d = '\0';
	}
    else if (isUnsigned(op_ct.colDataType))
    {
#ifndef __LP64__
        snprintf(tmp, 511, "%llu", getUintVal(row, parm, isNull, op_ct));
#else
        snprintf(tmp, 511, "%lu", getUintVal(row, parm, isNull, op_ct));
#endif
    }
	else
	{
#ifndef __LP64__
        snprintf(tmp, 511, "%lld", getIntVal(row, parm, isNull, op_ct));
#else
        snprintf(tmp, 511, "%ld", getIntVal(row, parm, isNull, op_ct));
#endif
	}

	return string(tmp);
}


} // namespace funcexp
// vim:ts=4 sw=4:
