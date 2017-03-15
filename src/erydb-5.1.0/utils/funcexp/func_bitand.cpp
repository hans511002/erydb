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
* $Id: func_bitand.cpp 3495 2013-01-21 14:09:51Z rdempsey $
*
*
****************************************************************************/

#include <string>
using namespace std;

#include "functor_int.h"
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

erydbSystemCatalog::ColType Func_bitand::operationType( FunctionParm& fp, erydbSystemCatalog::ColType& resultType )
{
	return resultType;
}

int64_t Func_bitand::getIntVal(Row& row,
									FunctionParm& parm,
									bool& isNull,
									erydbSystemCatalog::ColType& operationColType)
{

	vector<int64_t> values;

	if ( parm.size() < 2 ) {
		isNull = true;
		return 0;
	}

	for (uint32_t i = 0; i < parm.size(); i++)
	{
		switch (parm[i]->data()->resultType().colDataType)
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
			case execplan::erydbSystemCatalog::FLOAT:
            case execplan::erydbSystemCatalog::UDOUBLE:
            case execplan::erydbSystemCatalog::UFLOAT:
			{
				values.push_back(parm[i]->data()->getIntVal(row, isNull));
			}
			break;
	
			case execplan::erydbSystemCatalog::VARCHAR:
			case execplan::erydbSystemCatalog::CHAR:
			{
				int64_t value = parm[i]->data()->getIntVal(row, isNull);
				if (isNull)
				{
					isNull = true;
					return value;
				}
				values.push_back(0);
			}
			break;
	
			case execplan::erydbSystemCatalog::DECIMAL:
			{
				ERYDB_Decimal d = parm[i]->data()->getDecimalVal(row, isNull);
				int64_t value = d.value / power(d.scale);
				int lefto = (d.value - value * power(d.scale)) / power(d.scale-1);
				if ( value >= 0 && lefto > 4 )
					value++;
				if ( value < 0 && lefto < -4 )
					value--;
				values.push_back(value);
			}
			break;
	
			case execplan::erydbSystemCatalog::DATE:
			{
				int64_t time = parm[i]->data()->getDateIntVal(row, isNull);
	
				int32_t year = 0, 
						month = 0, 
						day = 0;
				
				year = (uint32_t)((time >> 16) & 0xffff);
				month = (uint32_t)((time >> 12) & 0xf);
				day = (uint32_t)((time >> 6) & 0x3f);
	
				values.push_back((year*10000)+(month*100)+day);
			}
			break;
	
			case execplan::erydbSystemCatalog::DATETIME:
			{
				int64_t time = parm[i]->data()->getDatetimeIntVal(row, isNull);
	
				int32_t year = 0, 
						month = 0, 
						day = 0, 
						hour = 0, 
						min = 0, 
						sec = 0;
			
						year = (uint32_t)((time >> 48) & 0xffff);
						month = (uint32_t)((time >> 44) & 0xf);
						day = (uint32_t)((time >> 38) & 0x3f);
						hour = (uint32_t)((time >> 32) & 0x3f);
						min = (uint32_t)((time >> 26) & 0x3f);
						sec = (uint32_t)((time >> 20) & 0x3f);
	
	//			return (int64_t) (year*1000000000000)+(month*100000000)+(day*1000000)+(hour*10000)+(min*100)+sec;
				values.push_back((month*100000000)+(day*1000000)+(hour*10000)+(min*100)+sec);		
			}
			break;
	
			default:
			{
				std::ostringstream oss;
				oss << "bitand: datatype of " << execplan::colDataTypeToString(operationColType.colDataType);
				throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
			}
		}
	}

	vector<int64_t>::iterator p = values.begin();
	int64_t retValue = *p;
	p++;
	while ( p != values.end() )
	{
		retValue = retValue & *p;
		p++;
	}

	return retValue;
}


} // namespace funcexp
// vim:ts=4 sw=4:
