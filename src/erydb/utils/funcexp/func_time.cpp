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
* $Id: func_time.cpp 3495 2013-01-21 14:09:51Z rdempsey $
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

namespace funcexp
{

erydbSystemCatalog::ColType Func_time::operationType( FunctionParm& fp, erydbSystemCatalog::ColType& resultType )
{
	erydbSystemCatalog::ColType ct;
	ct.colDataType = erydbSystemCatalog::VARCHAR;
	ct.colWidth = 255;
	return ct;
}

string Func_time::getStrVal(rowgroup::Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	int64_t val = 0;
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
		{
			val = dataconvert::DataConvert::intToDatetime(parm[0]->data()->getIntVal(row, isNull));
			if (val == -1)
				isNull = true;
			//else
		//		return *(reinterpret_cast<uint64_t*>(&val));
			break;
		}
		case execplan::erydbSystemCatalog::DECIMAL:
		{
			if (parm[0]->data()->resultType().scale)
			{
				val = dataconvert::DataConvert::intToDatetime(parm[0]->data()->getIntVal(row, isNull));
				if (val == -1)
					isNull = true;
				//else
				//	return *(reinterpret_cast<uint64_t*>(&val));
			}
			break;
		}
		case execplan::erydbSystemCatalog::DOUBLE:
		case execplan::erydbSystemCatalog::FLOAT:
		{
			isNull = true;
			break;
		}
		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		{
			val = dataconvert::DataConvert::stringToDatetime(parm[0]->data()->getStrVal(row, isNull));
			if (val == -1)
				isNull = true;
			//else
			//	return *(reinterpret_cast<uint64_t*>(&val));
			break;
		}
		case execplan::erydbSystemCatalog::DATE:
		{
			val = parm[0]->data()->getDatetimeIntVal(row, isNull);
			break;
		}
		case execplan::erydbSystemCatalog::DATETIME:
		{
			val = parm[0]->data()->getDatetimeIntVal(row, isNull);
			break;
		}
		default:
		{
			isNull = true;
		}
	}
	if (isNull)
		return "";
	
	char buf[30] = {'\0'};
	dataconvert::DataConvert::datetimeToString(val, buf, sizeof(buf));
	string time(buf);
	return time.substr(11,80);
}

int64_t Func_time::getIntVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct)
{
	return dataconvert::DataConvert::datetimeToInt(getStrVal(row, fp, isNull, op_ct));
}
							
double Func_time::getDoubleVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct)
{
	// convert time value to int followiing mysql. e.g. 23:34:34 => 233434
	int64_t datetimevalue = dataconvert::DataConvert::stringToDatetime(fp[0]->data()->getStrVal(row, isNull));
	return ((unsigned)((datetimevalue >> 32) & 0x3f)) * 10000 +
					((unsigned)((datetimevalue >> 26) & 0x3f)) * 100 +
					(unsigned)((datetimevalue >> 20) & 0x3f);
}


} // namespace funcexp
// vim:ts=4 sw=4:
