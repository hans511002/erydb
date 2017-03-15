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
* $Id: func_add_time.cpp 3923 2013-06-19 21:43:06Z bwilkinson $
*
*
****************************************************************************/

#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;

#include "functioncolumn.h"
#include "rowgroup.h"
using namespace execplan;

#include "dataconvert.h"
using namespace dataconvert;

#include "functor_dtm.h"
#include "funchelpers.h"

namespace
{
using namespace funcexp;

int64_t addTime(DateTime& dt1, Time& dt2)
{
	DateTime dt;
	dt.year = 0;
	dt.month = 0;
	dt.day = 0;
	dt.hour = 0;
	dt.minute = 0;
	dt.second = 0;
	dt.msecond = 0;

	int64_t month, day, hour, min, sec, msec, tmp;
	msec = (signed)(dt1.msecond + dt2.msecond);
	dt.msecond = tmp = msec % 1000000;
	if (tmp < 0)
	{
		dt.msecond = tmp + 1000000;
		dt2.second--;
	}
	sec = (signed)(dt1.second + dt2.second + msec/1000000);
	dt.second = tmp = sec % 60;
	if (tmp < 0)
	{
		dt.second = tmp + 60;
		dt2.minute--;
	}
	min = (signed)(dt1.minute + dt2.minute + sec/60);
	dt.minute = tmp = min % 60;
	if (tmp < 0)
	{
		dt.minute = tmp + 60;
		dt2.hour--;
	}
	hour = (signed)(dt1.hour + dt2.hour + min/60);
	dt.hour = tmp = hour % 24;
//	if (tmp < -1)
	if (tmp < 0)			// fix for subtime dlh
	{
		dt.hour = tmp + 24;
		dt2.day--;
	}
	day = (signed)(dt1.day + dt2.day + hour/24);
	
	if (isLeapYear(dt1.year) && dt1.month == 2)
		day--;
	
	month = dt1.month;
	int addyear = 0;
	if (dt2.day < 0 || dt2.hour < 0)
	{
		int monthSave = month;
		while (day <= 0)
		{
			month = (month == 1? 12: month-1);
			for (; day <= 0 && month > 0; month--)
				day += getDaysInMonth(month);
			month++;
//			month=12;
		}
		if ( month > monthSave )
			addyear--;
	}
	else
	{
		int monthSave = month;
		while (day > getDaysInMonth(month))
		{
			for (; day > getDaysInMonth(month) && month <= 12; month++)
				day -= getDaysInMonth(month);
			if (month > 12)
				month = 1;
		}
		if ( month < monthSave )
			addyear++;
	}
	dt.day = day;
	dt.month = month;
	dt.year = dt1.year + addyear;
	
	return *(reinterpret_cast<int64_t*>(&dt));
}
}

namespace funcexp
{

erydbSystemCatalog::ColType Func_add_time::operationType( FunctionParm& fp, erydbSystemCatalog::ColType& resultType )
{
	return resultType;
}

int64_t Func_add_time::getIntVal(rowgroup::Row& row,
						FunctionParm& parm,
						bool& isNull,
						erydbSystemCatalog::ColType& op_ct)
{
	return getDatetimeIntVal(row, parm, isNull, op_ct);
}

string Func_add_time::getStrVal(rowgroup::Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType& ct)
{
	return intToString(getIntVal(row, parm, isNull, ct));
}

int32_t Func_add_time::getDateIntVal(rowgroup::Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType& ct)
{
	return (((getDatetimeIntVal(row, parm, isNull, ct) >> 32) & 0xFFFFFFC0) | 0x3E);
}

int64_t Func_add_time::getDatetimeIntVal(rowgroup::Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType& ct)
{
	int64_t val1 = parm[0]->data()->getDatetimeIntVal(row, isNull);
	if (isNull)
		return -1;

	const string& val2 = parm[1]->data()->getStrVal(row, isNull);
	int sign = parm[2]->data()->getIntVal(row, isNull);
	DateTime dt1;
	dt1.year = (val1 >> 48) & 0xffff;
	dt1.month = (val1 >> 44) & 0xf;
	dt1.day = (val1 >> 38) & 0x3f;
	dt1.hour = (val1 >> 32) & 0x3f;
	dt1.minute = (val1 >> 26) & 0x3f;
	dt1.second = (val1 >> 20) & 0x3f;
	dt1.msecond = val1 & 0xfffff;
	
	int64_t	time = DataConvert::stringToTime(val2);
	if (time == -1)
	{
		isNull = true;
		return -1;
	}
	Time t2 = *(reinterpret_cast<Time*>(&time));
	
	// MySQL TIME type range '-838:59:59' and '838:59:59'
	if (t2.minute > 59 || t2.second > 59 || t2.msecond > 999999)
	{
		isNull = true;
		return -1;
	}
	
	int val_sign = 1;
	
	if (t2.day != 0 && t2.hour < 0)
	{
		isNull = true;
		return -1;
	}
	else if (t2.day < 0 || t2.hour < 0)
	{
		val_sign = -1;
	}
	if ((abs(t2.day) * 24 + abs(t2.hour)) > 838)
	{
		t2.hour = 838;
		t2.minute = 59;
		t2.second = 59;
	}
	else
	{
		t2.hour = abs(t2.day) * 24 + t2.hour;
	}
	t2.day = 0;
	if (val_sign * sign < 0)
	{
		t2.hour = -abs(t2.hour);
		t2.minute = -abs(t2.minute);
		t2.second = -abs(t2.second);
		t2.msecond = -abs(t2.msecond);
	}
	else
	{
		t2.hour = abs(t2.hour);
		t2.minute = abs(t2.minute);
		t2.second = abs(t2.second);
		t2.msecond = abs(t2.msecond);
	}

	return addTime(dt1, t2);
}


} // namespace funcexp
// vim:ts=4 sw=4:
