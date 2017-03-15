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
* $Id: func_least.cpp 3954 2013-07-08 16:30:15Z bpaul $
*
*
****************************************************************************/

#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;

#include "functor_all.h"
#include "functioncolumn.h"
using namespace execplan;

#include "rowgroup.h"
using namespace rowgroup;

#include "joblisttypes.h"
using namespace joblist;

#include "utils_utf8.h"
using namespace funcexp;

class to_lower
{
    public:
        char operator() (char c) const            // notice the return type
        {
            return tolower(c);
        }
};



namespace funcexp
{

erydbSystemCatalog::ColType Func_least::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	//return fp[0]->data()->resultType();
	return resultType;
}

int64_t Func_least::getIntVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct)
{
	double str = fp[0]->data()->getDoubleVal(row, isNull);

	double leastStr = str;
	for (uint32_t i = 1; i < fp.size(); i++)
	{
		double str1 = fp[i]->data()->getDoubleVal(row, isNull);

		if ( leastStr > str1 )
			leastStr = str1;
	}

	return (int64_t) leastStr;
}

double Func_least::getDoubleVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct)
{
	double str = fp[0]->data()->getDoubleVal(row, isNull);

	double leastStr = str;
	for (uint32_t i = 1; i < fp.size(); i++)
	{
		double str1 = fp[i]->data()->getDoubleVal(row, isNull);

		if ( leastStr > str1 )
			leastStr = str1;
	}

	return (double) leastStr;
}

std::string Func_least::getStrVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct)
{
	string leastStr = fp[0]->data()->getStrVal(row, isNull);
	for (uint32_t i = 1; i < fp.size(); i++)
	{
		const string& str1 = fp[i]->data()->getStrVal(row, isNull);

		int tmp = utf8::erydb_strcoll(leastStr.c_str(), str1.c_str());
		if ( tmp > 0 )

//		if ( leastStr > str1 )
			leastStr = str1;
	}

	return leastStr;
}

ERYDB_Decimal Func_least::getDecimalVal(Row& row,
							FunctionParm& fp,
							bool& isNull,
							erydbSystemCatalog::ColType& ct)
{
	ERYDB_Decimal str = fp[0]->data()->getDecimalVal(row, isNull);

	ERYDB_Decimal leastStr = str;
	for (uint32_t i = 1; i < fp.size(); i++)
	{
		ERYDB_Decimal str1 = fp[i]->data()->getDecimalVal(row, isNull);

		if ( leastStr > str1 )
			leastStr = str1;
	}

	return leastStr;
}



} // namespace funcexp
// vim:ts=4 sw=4:

