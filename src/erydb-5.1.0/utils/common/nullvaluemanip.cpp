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


#include "nullvaluemanip.h"
#include <sstream>

using namespace std;
using namespace execplan;

namespace utils {

uint64_t getNullValue(erydbSystemCatalog::ColDataType t, uint32_t colWidth)
{
    switch (t) {
		case erydbSystemCatalog::TINYINT:
			return joblist::TINYINTNULL;
		case erydbSystemCatalog::SMALLINT:
			return joblist::SMALLINTNULL;
		case erydbSystemCatalog::MEDINT:
		case erydbSystemCatalog::INT:
			return joblist::INTNULL;
		case erydbSystemCatalog::FLOAT:
        case erydbSystemCatalog::UFLOAT:
			return joblist::FLOATNULL;
		case erydbSystemCatalog::DATE:
			return joblist::DATENULL;
		case erydbSystemCatalog::BIGINT:
			return joblist::BIGINTNULL;
		case erydbSystemCatalog::DOUBLE:
        case erydbSystemCatalog::UDOUBLE:
			return joblist::DOUBLENULL;
		case erydbSystemCatalog::DATETIME:
			return joblist::DATETIMENULL;
		case erydbSystemCatalog::CHAR:
		case erydbSystemCatalog::VARCHAR:
		case erydbSystemCatalog::STRINT: {
			switch (colWidth) {
				case 1: return joblist::CHAR1NULL;
				case 2: return joblist::CHAR2NULL;
				case 3:
				case 4: return joblist::CHAR4NULL;
				case 5:
				case 6:
				case 7:
				case 8: return joblist::CHAR8NULL;
				default:
					throw logic_error("getNullValue() Can't return the NULL string");
			}
			break;
		}
		case erydbSystemCatalog::DECIMAL:
        case erydbSystemCatalog::UDECIMAL:
        {
			switch (colWidth) {
				case 1 : return joblist::TINYINTNULL;
				case 2 : return joblist::SMALLINTNULL;
				case 4 : return joblist::INTNULL;
				default: return joblist::BIGINTNULL;
			}
			break;
		}
        case erydbSystemCatalog::UTINYINT:
            return joblist::UTINYINTNULL;
        case erydbSystemCatalog::USMALLINT:
            return joblist::USMALLINTNULL;
        case erydbSystemCatalog::UMEDINT:
        case erydbSystemCatalog::UINT:
            return joblist::UINTNULL;
        case erydbSystemCatalog::UBIGINT:
            return joblist::UBIGINTNULL;
		case erydbSystemCatalog::LONGDOUBLE:
			return -1;  // no NULL value for long double yet, this is a nan.
		case erydbSystemCatalog::VARBINARY:
		default:
			ostringstream os;
			os << "getNullValue(): got bad column type (" << t <<
				").  Width=" << colWidth << endl;
			throw logic_error(os.str());
	}

}

int64_t getSignedNullValue(erydbSystemCatalog::ColDataType t, uint32_t colWidth)
{
	switch (t) {
		case erydbSystemCatalog::TINYINT:
			return (int64_t) ((int8_t) joblist::TINYINTNULL);
		case erydbSystemCatalog::SMALLINT:
			return (int64_t) ((int16_t) joblist::SMALLINTNULL);
		case erydbSystemCatalog::MEDINT:
		case erydbSystemCatalog::INT:
			return (int64_t) ((int32_t) joblist::INTNULL);
		case erydbSystemCatalog::FLOAT:
        case erydbSystemCatalog::UFLOAT:
			return (int64_t) ((int32_t) joblist::FLOATNULL);
		case erydbSystemCatalog::DATE:
			return (int64_t) ((int32_t) joblist::DATENULL);
		case erydbSystemCatalog::BIGINT:
			return joblist::BIGINTNULL;
		case erydbSystemCatalog::DOUBLE:
        case erydbSystemCatalog::UDOUBLE:
			return joblist::DOUBLENULL;
		case erydbSystemCatalog::DATETIME:
			return joblist::DATETIMENULL;
		case erydbSystemCatalog::CHAR:
		case erydbSystemCatalog::VARCHAR:
		case erydbSystemCatalog::STRINT: {
			switch (colWidth) {
				case 1: return (int64_t) ((int8_t) joblist::CHAR1NULL);
				case 2: return (int64_t) ((int16_t) joblist::CHAR2NULL);
				case 3:
				case 4: return (int64_t) ((int32_t) joblist::CHAR4NULL);
				case 5:
				case 6:
				case 7:
				case 8: return joblist::CHAR8NULL;
				default:
					throw logic_error("getSignedNullValue() Can't return the NULL string");
			}
			break;
		}
		case erydbSystemCatalog::DECIMAL:
        case erydbSystemCatalog::UDECIMAL: {
			switch (colWidth) {
				case 1 : return (int64_t) ((int8_t)  joblist::TINYINTNULL);
				case 2 : return (int64_t) ((int16_t) joblist::SMALLINTNULL);
				case 4 : return (int64_t) ((int32_t) joblist::INTNULL);
				default: return joblist::BIGINTNULL;
			}
			break;
		}
        case erydbSystemCatalog::UTINYINT:
            return (int64_t) ((int8_t) joblist::UTINYINTNULL);
        case erydbSystemCatalog::USMALLINT:
            return (int64_t) ((int16_t) joblist::USMALLINTNULL);
        case erydbSystemCatalog::UMEDINT:
        case erydbSystemCatalog::UINT:
            return (int64_t) ((int32_t) joblist::UINTNULL);
        case erydbSystemCatalog::UBIGINT:
            return (int64_t)joblist::UBIGINTNULL;
		case erydbSystemCatalog::LONGDOUBLE:
			return -1;  // no NULL value for long double yet, this is a nan.
		case erydbSystemCatalog::VARBINARY:
		default:
			ostringstream os;
			os << "getSignedNullValue(): got bad column type (" << t <<
				").  Width=" << colWidth << endl;
			throw logic_error(os.str());
	}

}


}
