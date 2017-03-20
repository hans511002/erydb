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
* $Id: func_char_length.cpp 3923 2013-06-19 21:43:06Z bwilkinson $
*
*
****************************************************************************/

#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;

#include "functor_int.h"
#include "functioncolumn.h"
#include "rowgroup.h"
#include "erydbsystemcatalog.h"
#include "utils_utf8.h"
using namespace execplan;

#include "dataconvert.h"

#include "errorcodes.h"
#include "erydberrorinfo.h"
#include "errorids.h"
using namespace logging;

namespace funcexp
{

erydbSystemCatalog::ColType Func_char_length::operationType( FunctionParm& fp, erydbSystemCatalog::ColType& resultType )
{
	return resultType;
}

int64_t Func_char_length::getIntVal(rowgroup::Row& row,
						FunctionParm& parm,
						bool& isNull,
						erydbSystemCatalog::ColType& op_ct)
{
	erydbSystemCatalog::ColDataType type = parm[0]->data()->resultType().colDataType;

	switch (type)
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
		case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
		case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::VARCHAR: // including CHAR
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
		{
			const string& tstr = parm[0]->data()->getStrVal(row, isNull);
			if (isNull)
				return 0;

			size_t strwclen = utf8::erydb_mbstowcs(0, tstr.c_str(), 0) + 1;
			wchar_t* wcbuf = (wchar_t*)alloca(strwclen * sizeof(wchar_t));
			strwclen = utf8::erydb_mbstowcs(wcbuf, tstr.c_str(), strwclen);

			return (int64_t)strwclen;
		}

		case execplan::erydbSystemCatalog::DATE:
		{
			string date = dataconvert::DataConvert::dateToString(parm[0]->data()->getDateIntVal(row, isNull));
			return (int64_t)date.size();
		}	

		case execplan::erydbSystemCatalog::DATETIME:
		{
			string date = dataconvert::DataConvert::datetimeToString(parm[0]->data()->getDatetimeIntVal(row, isNull));
			return (int64_t)date.size();
		}

		default:
		{
			std::ostringstream oss;
			oss << "char_length: datatype of " << execplan::colDataTypeToString(type);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}

	return 0;
}


} // namespace funcexp
// vim:ts=4 sw=4:
