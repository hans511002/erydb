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
* $Id: func_date.cpp 3923 2013-06-19 21:43:06Z bwilkinson $
*
*
****************************************************************************/

#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;

#include "functor_dtm.h"
#include "functioncolumn.h"
#include "rowgroup.h"
using namespace execplan;

#include "dataconvert.h"

#include "errorcodes.h"
#include "erydberrorinfo.h"
#include "errorids.h"
using namespace logging;


namespace funcexp
{

erydbSystemCatalog::ColType Func_date::operationType( FunctionParm& fp, erydbSystemCatalog::ColType& resultType )
{
	return resultType;
}

int64_t Func_date::getIntVal(rowgroup::Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	erydbSystemCatalog::ColDataType type = parm[0]->data()->resultType().colDataType;

	string value = "";

	switch (type)
	{
		case execplan::erydbSystemCatalog::DATE:
		{
			return parm[0]->data()->getDatetimeIntVal(row, isNull);
			break;
		}

		case execplan::erydbSystemCatalog::DATETIME:
		{
			int64_t val1  = parm[0]->data()->getDatetimeIntVal(row, isNull);
			value = dataconvert::DataConvert::datetimeToString(val1);
			value = value.substr(0,10);
			break;
		}

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
        case execplan::erydbSystemCatalog::DOUBLE:
		case execplan::erydbSystemCatalog::UDOUBLE:
		case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
		{
			isNull = true;
			return 0;
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "date: datatype of " << execplan::colDataTypeToString(type);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}

	return dataconvert::DataConvert::datetimeToInt(value);
}

string Func_date::getStrVal(rowgroup::Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	const string& val = parm[0]->data()->getStrVal(row, isNull);

	return val.substr(0,10);
}


} // namespace funcexp
// vim:ts=4 sw=4:
