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
* $Id: func_mod.cpp 3616 2013-03-04 14:56:29Z rdempsey $
*
*
****************************************************************************/

#include <string>
using namespace std;

#include "functor_real.h"
#include "funchelpers.h"
#include "functioncolumn.h"
#include "predicateoperator.h"
using namespace execplan;

#include "rowgroup.h"
using namespace rowgroup;

#include "errorcodes.h"
#include "erydberrorinfo.h"
#include "errorids.h"
using namespace logging;


namespace funcexp
{

erydbSystemCatalog::ColType Func_mod::operationType( FunctionParm& fp, erydbSystemCatalog::ColType& resultType )
{
	return resultType;
}


ERYDB_Decimal Func_mod::getDecimalVal(Row& row,
									FunctionParm& parm,
									bool& isNull,
									erydbSystemCatalog::ColType& operationColType)
{

	ERYDB_Decimal retValue;
	retValue.value = 0;
	retValue.scale = 0;

	if ( parm.size() < 2 ) {
		isNull = true;
		return retValue;
	}

	int64_t div = parm[1]->data()->getIntVal(row, isNull);

	if ( div == 0 ) {
		isNull = true;
		return retValue;
	}

	ERYDB_Decimal d = parm[0]->data()->getDecimalVal(row, isNull);
	int64_t value = d.value / helpers::power(d.scale);
	int lefto = d.value % helpers::power(d.scale);

	int64_t mod = (value % div) * helpers::power(d.scale) + lefto;

	retValue.value = mod;
	retValue.scale = d.scale;

	return retValue;
}


double Func_mod::getDoubleVal(Row& row,
									FunctionParm& parm,
									bool& isNull,
									erydbSystemCatalog::ColType& operationColType)
{
	if ( parm.size() < 2 ) {
		isNull = true;
		return 0;
	}

	int64_t div = parm[1]->data()->getIntVal(row, isNull);

	if ( div == 0 ) {
		isNull = true;
		return 0;
	}

	double mod = 0;
	
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
		{
			int64_t value = parm[0]->data()->getIntVal(row, isNull);

			mod = value % div;
		}
		break;

        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
        {
            uint64_t udiv = parm[1]->data()->getIntVal(row, isNull);
            uint64_t uvalue = parm[0]->data()->getUintVal(row, isNull);

            mod = uvalue % udiv;
        }
        break;

        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
		{
			double value = parm[0]->data()->getDoubleVal(row, isNull);

			mod = fmod(value,div);
		}
		break;

		case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		{
			float value = parm[0]->data()->getFloatVal(row, isNull);

			mod = fmod(value,div);
		}
		break;

		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
		{
			ERYDB_Decimal d = parm[0]->data()->getDecimalVal(row, isNull);
			int64_t value = d.value / helpers::power(d.scale);

			mod = value % div;
		}
		break;
		
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::VARCHAR:
		{
			double value = parm[0]->data()->getDoubleVal(row, isNull);
			mod = fmod(value,div);
			break;
		}

		default:
		{
			std::ostringstream oss;
			oss << "mod: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}

	return mod;
}

int64_t Func_mod::getIntVal(Row& row,
									FunctionParm& parm,
									bool& isNull,
									erydbSystemCatalog::ColType& operationColType)
{
	if ( parm.size() < 2 ) {
		isNull = true;
		return 0;
	}

	int64_t div = parm[1]->data()->getIntVal(row, isNull);

	if ( div == 0 ) {
		isNull = true;
		return 0;
	}

	int64_t mod = 0;

	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::VARCHAR:
		{
			int64_t value = parm[0]->data()->getIntVal(row, isNull);

			mod = value % div;
		}
		break;

        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
        {
            uint64_t udiv = parm[1]->data()->getIntVal(row, isNull);
            uint64_t uvalue = parm[0]->data()->getUintVal(row, isNull);

            mod = uvalue % udiv;
        }
        break;

        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
		{
			double value = parm[0]->data()->getDoubleVal(row, isNull);

			mod = fmod(value,div);
		}
		break;

		case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		{
			float value = parm[0]->data()->getFloatVal(row, isNull);

			mod = fmod(value,div);
		}
		break;

		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
		{
			ERYDB_Decimal d = parm[0]->data()->getDecimalVal(row, isNull);
			int64_t value = d.value / helpers::power(d.scale);

			mod = value % div;
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "mod: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}

	return mod;
}

uint64_t Func_mod::getUIntVal(Row& row,
									FunctionParm& parm,
									bool& isNull,
									erydbSystemCatalog::ColType& operationColType)
{
	if ( parm.size() < 2 ) {
		isNull = true;
		return 0;
	}

	int64_t div = parm[1]->data()->getIntVal(row, isNull);

	if ( div == 0 ) {
		isNull = true;
		return 0;
	}

	uint64_t mod = 0;

	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::VARCHAR:
		{
			int64_t value = parm[0]->data()->getIntVal(row, isNull);

			mod = value % div;
		}
		break;

        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
        {
            uint64_t udiv = parm[1]->data()->getIntVal(row, isNull);
            uint64_t uvalue = parm[0]->data()->getUintVal(row, isNull);

            mod = uvalue % udiv;
        }
        break;

        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
		{
			double value = parm[0]->data()->getDoubleVal(row, isNull);

			mod = fmod(value,div);
		}
		break;

		case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		{
			float value = parm[0]->data()->getFloatVal(row, isNull);

			mod = fmod(value,div);
		}
		break;

		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
		{
			ERYDB_Decimal d = parm[0]->data()->getDecimalVal(row, isNull);
			int64_t value = d.value / helpers::power(d.scale);

			mod = value % div;
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "mod: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}

	return mod;
}

std::string Func_mod::getStrVal(Row& row,
						FunctionParm& fp,
						bool& isNull,
						erydbSystemCatalog::ColType& op_ct)
{
   	if ( fp.size() < 2 ) {
		isNull = true;
		return std::string();
	}

	switch (fp[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
    		return intToString(getIntVal(row, fp, isNull, op_ct));
    		break;

		default:
			return doubleToString(getDoubleVal(row, fp, isNull, op_ct));
			break;
	}
}

} // namespace funcexp
// vim:ts=4 sw=4:
