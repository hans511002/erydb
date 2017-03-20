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
* $Id: func_str_to_date.cpp 2578 2011-05-12 16:26:55Z chao $
*
*
****************************************************************************/

#include <unistd.h>
#include <cstdlib>
#include <string>
using namespace std;

#include "functor_dtm.h"
#include "funchelpers.h"
#include "functioncolumn.h"
#include "rowgroup.h"
using namespace execplan;

#include "dataconvert.h"
#define MAX_DAY_NUMBER 3652424L

#include "timeextract.h"

namespace
{
using namespace funcexp;

dataconvert::DateTime getDateTime (rowgroup::Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	TimeExtractor extractor;
	dataconvert::DateTime dateTime;
	dateTime.year = 0;
	dateTime.month = 0;
	dateTime.day = 0;
	dateTime.hour = 0;
	dateTime.minute = 0;
	dateTime.second = 0;
	dateTime.msecond = 0;
	int64_t val = 0;
	string valStr;
	const string& formatStr = parm[1]->data()->getStrVal(row, isNull);
	int rc = 0;
	switch (parm[0]->data()->resultType().colDataType)
	{
		case erydbSystemCatalog::DATE:
		{
			val = parm[0]->data()->getIntVal(row, isNull);
			valStr = dataconvert::DataConvert::dateToString (val);
			rc = extractor.extractTime (valStr, formatStr, dateTime);
			if ( rc < 0)
			{
				isNull = true;
				return -1;
			}
			break;
		}
		case erydbSystemCatalog::DATETIME:
		{
			val = parm[0]->data()->getIntVal(row, isNull);
			valStr = dataconvert::DataConvert::datetimeToString (val);
			rc = extractor.extractTime (valStr, formatStr, dateTime);
			if ( rc < 0)
			{
				isNull = true;
				return -1;
			}
			break;
		}
		case erydbSystemCatalog::CHAR:
		case erydbSystemCatalog::VARCHAR:
		{
			const string& valref = parm[0]->data()->getStrVal(row, isNull);
			//decode with provided format
			rc = extractor.extractTime (valref, formatStr, dateTime);
			if ( rc < 0)
			{
				isNull = true;
				return -1;
			}
			break;
		}
		case erydbSystemCatalog::BIGINT:
		case erydbSystemCatalog::MEDINT:
		case erydbSystemCatalog::SMALLINT:
		case erydbSystemCatalog::TINYINT:
		case erydbSystemCatalog::INT:	
		{
			val = parm[0]->data()->getIntVal(row, isNull);
			//decode with provided format
			rc = extractor.extractTime (helpers::intToString(val), formatStr, dateTime);
			if ( rc < 0)
			{
				isNull = true;
				return -1;
			}
			break;	
		}
		case erydbSystemCatalog::DECIMAL:
		{
			if (parm[0]->data()->resultType().scale == 0)
			{
				val = parm[0]->data()->getIntVal(row, isNull);
				
				//decode with provided format
				rc = extractor.extractTime (helpers::intToString(val), formatStr, dateTime);
				if ( rc < 0)
				{
					isNull = true;
					return -1;
				}
			}
			break;
		}
		default:
			isNull = true;
			return -1;
	}
	return dateTime;
}

}

namespace funcexp
{

erydbSystemCatalog::ColType Func_str_to_date::operationType( FunctionParm& fp, erydbSystemCatalog::ColType& resultType )
{
	return resultType;
}

string Func_str_to_date::getStrVal(rowgroup::Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType& ct)
{
	dataconvert::DateTime dateTime;
	dateTime = getDateTime(row, parm, isNull, ct);
	string convertedDate = dataconvert::DataConvert::datetimeToString(*((long long*) &dateTime));
	return convertedDate;
}

int32_t Func_str_to_date::getDateIntVal(rowgroup::Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType& ct)
{
	dataconvert::DateTime dateTime;
	dateTime = getDateTime(row, parm, isNull, ct);
	int64_t time = *(reinterpret_cast<int64_t*>(&dateTime));
	return ((((int32_t)(time >> 32)) & 0xFFFFFFC0) | 0x3E);
}		

int64_t Func_str_to_date::getDatetimeIntVal(rowgroup::Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType& ct)
{
	dataconvert::DateTime dateTime;
	dateTime = getDateTime(row, parm, isNull, ct);
	int64_t time = *(reinterpret_cast<int64_t*>(&dateTime));
	return time;
}

int64_t Func_str_to_date::getIntVal(rowgroup::Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType& ct)
{
	dataconvert::DateTime dateTime;
	dateTime = getDateTime(row, parm, isNull, ct);
	int64_t time = *(reinterpret_cast<int64_t*>(&dateTime));
	return time;
}								


} // namespace funcexp
// vim:ts=4 sw=4:
