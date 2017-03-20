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
* $Id: func_regexp.cpp 3495 2013-01-21 14:09:51Z rdempsey $
*
*
****************************************************************************/

#include <cstdlib>
#include <string>
using namespace std;

#ifdef __linux__
#include <regex.h> 
#else
#include <boost/regex.hpp>
using namespace boost;
#endif

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

namespace
{
	inline bool getBool(rowgroup::Row& row,
							funcexp::FunctionParm& pm,
							bool& isNull,
							erydbSystemCatalog::ColType& ct)
	{
		
		string expr;
		string pattern;

		switch (pm[0]->data()->resultType().colDataType)
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
			case execplan::erydbSystemCatalog::VARCHAR: // including CHAR'
			case execplan::erydbSystemCatalog::CHAR:
			case execplan::erydbSystemCatalog::DOUBLE:
            case execplan::erydbSystemCatalog::UDOUBLE:
			case execplan::erydbSystemCatalog::FLOAT:
            case execplan::erydbSystemCatalog::UFLOAT:
			{
				expr = pm[0]->data()->getStrVal(row, isNull);
				break;
			}
			case execplan::erydbSystemCatalog::DATE:
			{
				expr = dataconvert::DataConvert::dateToString(pm[0]->data()->getDateIntVal(row, isNull));
				break;
			}	
			case execplan::erydbSystemCatalog::DATETIME:
			{
				expr = dataconvert::DataConvert::datetimeToString(pm[0]->data()->getDatetimeIntVal(row, isNull));
				//strip off micro seconds
				expr = expr.substr(0,19);
				break;
			}		
			case execplan::erydbSystemCatalog::DECIMAL:
            case execplan::erydbSystemCatalog::UDECIMAL:
			{
				ERYDB_Decimal d = pm[0]->data()->getDecimalVal(row, isNull);
	
				char buf[80];
	
				dataconvert::DataConvert::decimalToString(d.value, d.scale, buf, 80, pm[0]->data()->resultType().colDataType);
	
				expr = buf;
				break;
			}

			default:
			{
				std::ostringstream oss;
				oss << "regexp: datatype of " << execplan::colDataTypeToString(ct.colDataType);
				throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
			}
		}

		switch (pm[1]->data()->resultType().colDataType)
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
			case execplan::erydbSystemCatalog::VARCHAR: // including CHAR'
			case execplan::erydbSystemCatalog::DOUBLE:
            case execplan::erydbSystemCatalog::UDOUBLE:
			case execplan::erydbSystemCatalog::FLOAT:
            case execplan::erydbSystemCatalog::UFLOAT:
			case execplan::erydbSystemCatalog::CHAR:
			{
				pattern = pm[1]->data()->getStrVal(row, isNull);
				break;
			}
			case execplan::erydbSystemCatalog::DATE:
			{
				pattern = dataconvert::DataConvert::dateToString(pm[1]->data()->getDateIntVal(row, isNull));
				break;
			}	
			case execplan::erydbSystemCatalog::DATETIME:
			{
				pattern = dataconvert::DataConvert::datetimeToString(pm[1]->data()->getDatetimeIntVal(row, isNull));
				//strip off micro seconds
				pattern = pattern.substr(0,19);
				break;
			}		
			case execplan::erydbSystemCatalog::DECIMAL:
            case execplan::erydbSystemCatalog::UDECIMAL:
			{
				ERYDB_Decimal d = pm[1]->data()->getDecimalVal(row, isNull);
	
				char buf[80];
	
				dataconvert::DataConvert::decimalToString( d.value, d.scale, buf, 80, pm[1]->data()->resultType().colDataType);
	
				pattern = buf;
				break;
			}
			default:
			{
				std::ostringstream oss;
				oss << "regexp: datatype of " << execplan::colDataTypeToString(ct.colDataType);
				throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
			}
		}


#ifdef __linux__
		regex_t    re;

    	regcomp(&re, pattern.c_str(), REG_EXTENDED | REG_NOSUB );

		int res = regexec(&re, expr.c_str(), 0, NULL, 0);
		regfree(&re);
		if (res == 0)
			return true;
		else
			return false;
#else
		regex pat(pattern.c_str());
		return regex_search(expr.c_str(), pat);
#endif


	}
	
}

namespace funcexp
{

erydbSystemCatalog::ColType Func_regexp::operationType( FunctionParm& fp, erydbSystemCatalog::ColType& resultType )
{
	return resultType;
}

bool Func_regexp::getBoolVal(rowgroup::Row& row,
							FunctionParm& pm,
							bool& isNull,
							erydbSystemCatalog::ColType& ct)
{
	return getBool(row, pm, isNull, ct) && !isNull;
}


} // namespace funcexp
// vim:ts=4 sw=4:
