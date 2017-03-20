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
* $Id: func_math.cpp 3923 2013-06-19 21:43:06Z bwilkinson $
*
*
****************************************************************************/

#include <cstdlib>
#include <string>
#include <cerrno>
#define _USE_MATH_DEFINES // MSC: enable math defines
#include <cmath>
#include <iomanip>
using namespace std;

#include "functor_real.h"
#include "functor_str.h"
#include "functioncolumn.h"
using namespace execplan;

#include "rowgroup.h"
using namespace rowgroup;

#include "errorcodes.h"
#include "erydberrorinfo.h"
#include "errorids.h"
using namespace logging;

#include "funchelpers.h"

// Just in case they're missing...
#ifndef M_LN2
#define M_LN2 0.69314718055994530942 /* log_e 2 */
#endif
#ifndef M_PI
#define M_PI 3.14159265358979323846 /* pi */
#endif

namespace
{
inline double degrees(double radian)
{
	return (radian * 180.0 / M_PI);
}

inline double radians(double degree)
{
	return (degree * M_PI / 180.0);
}

#if defined(_MSC_VER) && MSC_VER < 1800
inline double log2(double x)
{
	return (log(x) / M_LN2);
}
#endif
}

namespace funcexp
{

//
//	acos
//

erydbSystemCatalog::ColType Func_acos::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	return fp[0]->data()->resultType();
}


double Func_acos::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
		case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
		case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
		{
			// null value is indicated by isNull
			double value = parm[0]->data()->getDoubleVal(row, isNull);
			if (isNull || (value < -1.0 || value > 1.0))
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return acos(value);
		}
		break;

		case execplan::erydbSystemCatalog::DATE:
		{
			int32_t value = parm[0]->data()->getDateIntVal(row, isNull);
			if (isNull || (value < -1.0 || value > 1.0))
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return acos((double)value);
		}
		break;

		case execplan::erydbSystemCatalog::DATETIME:
		{
			int64_t value = parm[0]->data()->getDatetimeIntVal(row, isNull);
			if (isNull || (value < -1.0 || value > 1.0))
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return acos((double)value);
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "acos: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}

}


//
//	asin
//

erydbSystemCatalog::ColType Func_asin::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	return fp[0]->data()->resultType();
}


double Func_asin::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
        case execplan::erydbSystemCatalog::DOUBLE:
		case execplan::erydbSystemCatalog::UDOUBLE:
		case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
		{
			// null value is indicated by isNull
			double value = parm[0]->data()->getDoubleVal(row, isNull);
			if (isNull || (value < -1.0 || value > 1.0))
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return asin(value);
		}
		break;

		case execplan::erydbSystemCatalog::DATE:
		{
			int32_t value = parm[0]->data()->getDateIntVal(row, isNull);
			if (isNull || (value < -1.0 || value > 1.0))
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return asin((double)value);
		}
		break;

		case execplan::erydbSystemCatalog::DATETIME:
		{
			int64_t value = parm[0]->data()->getDatetimeIntVal(row, isNull);
			if (isNull || (value < -1.0 || value > 1.0))
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return asin((double)value);
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "asin: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}
}



//
//	atan
//

erydbSystemCatalog::ColType Func_atan::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	return fp[0]->data()->resultType();
}


double Func_atan::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
        case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
		{
			// null value is indicated by isNull
			double value = parm[0]->data()->getDoubleVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
		
			if (parm.size() > 1 ) 
			{
				double value2 = parm[1]->data()->getDoubleVal(row, isNull);
				if (isNull)
				{
					isNull = true;
					return doubleNullVal();
				}
		
					return atan2(value, value2);
			}
			
			return atan(value);
		}
		break;

		case execplan::erydbSystemCatalog::DATE:
		{
			int32_t value = parm[0]->data()->getDateIntVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
		
			if (parm.size() > 1 ) 
			{
				double value2 = parm[1]->data()->getDoubleVal(row, isNull);
				if (isNull)
				{
					isNull = true;
					return doubleNullVal();
				}
		
					return atan2(value, value2);
			}
			
			return atan((double)value);
		}
		break;

		case execplan::erydbSystemCatalog::DATETIME:
		{
			int64_t value = parm[0]->data()->getDatetimeIntVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
		
			if (parm.size() > 1 ) 
			{
				double value2 = parm[1]->data()->getDoubleVal(row, isNull);
				if (isNull)
				{
					isNull = true;
					return doubleNullVal();
				}
		
					return atan2(value, value2);
			}
			
			return atan((double)value);
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "atan: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}
}


//
//	cos
//

erydbSystemCatalog::ColType Func_cos::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	return fp[0]->data()->resultType();
}


double Func_cos::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
        case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
		{
			// null value is indicated by isNull
			double value = parm[0]->data()->getDoubleVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return cos(value);
		}
		break;

		case execplan::erydbSystemCatalog::DATE:
		{
			int32_t value = parm[0]->data()->getDateIntVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return cos((double)value);
		}
		break;

		case execplan::erydbSystemCatalog::DATETIME:
		{
			int64_t value = parm[0]->data()->getDatetimeIntVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return cos((double)value);
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "cos: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}
}


//
//	cot
//

erydbSystemCatalog::ColType Func_cot::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	return fp[0]->data()->resultType();
}


double Func_cot::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
   	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
        case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
		{
			// null value is indicated by isNull
			double value = parm[0]->data()->getDoubleVal(row, isNull);
            if (value == 0)
            {
                Message::Args args;
                args.add("cot");
                args.add(value);
                unsigned errcode = ERR_FUNC_OUT_OF_RANGE_RESULT;
                throw ERYDBExcept(ERYDBErrorInfo::instance()->errorMsg(errcode, args), errcode);
            }
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return 1.0 / tan(value); 
		}
		break;

		case execplan::erydbSystemCatalog::DATE:
		{
			int32_t value = parm[0]->data()->getDateIntVal(row, isNull);
            if (value == 0)
            {
                Message::Args args;
                args.add("cot");
                args.add(value);
                unsigned errcode = ERR_FUNC_OUT_OF_RANGE_RESULT;
                throw ERYDBExcept(ERYDBErrorInfo::instance()->errorMsg(errcode, args), errcode);
            }

			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return 1.0 / tan((double)value); 
		}
		break;

		case execplan::erydbSystemCatalog::DATETIME:
		{
			int64_t value = parm[0]->data()->getDatetimeIntVal(row, isNull);
            if (value == 0)
            {
                Message::Args args;
                args.add("cot");
                args.add((uint64_t)value);
                unsigned errcode = ERR_FUNC_OUT_OF_RANGE_RESULT;
                throw ERYDBExcept(ERYDBErrorInfo::instance()->errorMsg(errcode, args), errcode);
            }
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return 1.0 / tan((double)value); 
		}
		break;

		default:
		{
            std::ostringstream oss;
			oss << "cot: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}
}


//
//	log
//

erydbSystemCatalog::ColType Func_log::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	return fp[0]->data()->resultType();
}


double Func_log::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
        case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
		{
			// null value is indicated by isNull
			double value = parm[0]->data()->getDoubleVal(row, isNull);
			if (isNull || value <= 0.0)
			{
				isNull = true;
				return doubleNullVal();
			}
		
			if (parm.size() > 1 ) 
			{
				double value2 = parm[1]->data()->getDoubleVal(row, isNull);
				if (isNull || (value2 <= 0.0 || value == 1.0) )
				{
					isNull = true;
					return doubleNullVal();
				}
		
					return log(value2) / log(value);
			}
			
			return log(value);
		}
		break;

		case execplan::erydbSystemCatalog::DATE:
		{
			int32_t value = parm[0]->data()->getDateIntVal(row, isNull);
			if (isNull || value <= 0.0)
			{
				isNull = true;
				return doubleNullVal();
			}
		
			if (parm.size() > 1 ) 
			{
				double value2 = parm[1]->data()->getDoubleVal(row, isNull);
				if (isNull || (value2 <= 0.0 || value == 1.0) )
				{
					isNull = true;
					return doubleNullVal();
				}
		
					return log(value2) / log((double)value);
			}
			
			return log((double)value);
		}
		break;

		case execplan::erydbSystemCatalog::DATETIME:
		{
			int64_t value = parm[0]->data()->getDatetimeIntVal(row, isNull);
			if (isNull || value <= 0.0)
			{
				isNull = true;
				return doubleNullVal();
			}
		
			if (parm.size() > 1 ) 
			{
				double value2 = parm[1]->data()->getDoubleVal(row, isNull);
				if (isNull || (value2 <= 0.0 || value == 1.0) )
				{
					isNull = true;
					return doubleNullVal();
				}
		
					return log(value2) / log((double)value);
			}
			
			return log((double)value);
		}
		break;

		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		{
			isNull = true;
			return doubleNullVal();
		}
		default:
		{
			std::ostringstream oss;
			oss << "log: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}
}


//
//	log2
//

erydbSystemCatalog::ColType Func_log2::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	return fp[0]->data()->resultType();
}


double Func_log2::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
        case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
		{
			// null value is indicated by isNull
			double value = parm[0]->data()->getDoubleVal(row, isNull);
			if (isNull || value <= 0.0)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return log2(value);
		}
		break;

		case execplan::erydbSystemCatalog::DATE:
		{
			int32_t value = parm[0]->data()->getDateIntVal(row, isNull);
			if (isNull || value <= 0.0)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return log2(value);
		}
		break;

		case execplan::erydbSystemCatalog::DATETIME:
		{
			int64_t value = parm[0]->data()->getDatetimeIntVal(row, isNull);
			if (isNull || value <= 0.0)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return log2(value);
		}
		break;

		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		{
			isNull = true;
			return doubleNullVal();
		}
		default:
		{
			std::ostringstream oss;
			oss << "log2: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}
}


//
//	log10
//

erydbSystemCatalog::ColType Func_log10::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	return fp[0]->data()->resultType();
}


double Func_log10::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
        case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
		{
			// null value is indicated by isNull
			double value = parm[0]->data()->getDoubleVal(row, isNull);
			if (isNull || value <= 0.0)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return log10(value);
		}
		break;

		case execplan::erydbSystemCatalog::DATE:
		{
			int32_t value = parm[0]->data()->getDateIntVal(row, isNull);
			if (isNull || value <= 0.0)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return log10((double)value);
		}
		break;

		case execplan::erydbSystemCatalog::DATETIME:
		{
			int64_t value = parm[0]->data()->getDatetimeIntVal(row, isNull);
			if (isNull || value <= 0.0)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return log10((double)value);
		}
		break;

		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		{
			isNull = true;
			return doubleNullVal();
		}
		default:
		{
			std::ostringstream oss;
			oss << "log10: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}
}


//
//	sin
//

erydbSystemCatalog::ColType Func_sin::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	return fp[0]->data()->resultType();
}


double Func_sin::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
        case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
		{
			// null value is indicated by isNull
			double value = parm[0]->data()->getDoubleVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return sin(value);
		}
		break;

		case execplan::erydbSystemCatalog::DATE:
		{
			int32_t value = parm[0]->data()->getDateIntVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return sin((double)value);
		}
		break;

		case execplan::erydbSystemCatalog::DATETIME:
		{
			int64_t value = parm[0]->data()->getDatetimeIntVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return sin((double)value);
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "sin: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}
}


//
//	sqrt
//

erydbSystemCatalog::ColType Func_sqrt::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	return fp[0]->data()->resultType();
}


double Func_sqrt::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
        case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
		{
			// null value is indicated by isNull
			double value = parm[0]->data()->getDoubleVal(row, isNull);
			if (isNull || value < 0)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return sqrt(value);
		}
		break;

		case execplan::erydbSystemCatalog::DATE:
		{
			int32_t value = parm[0]->data()->getDateIntVal(row, isNull);
			if (isNull || value < 0)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return sqrt((double)value);
		}
		break;

		case execplan::erydbSystemCatalog::DATETIME:
		{
			int64_t value = parm[0]->data()->getDatetimeIntVal(row, isNull);
			if (isNull || value < 0)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return sqrt((double)value);
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "sqrt: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}
}


//
//	tan
//

erydbSystemCatalog::ColType Func_tan::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	return fp[0]->data()->resultType();
}


double Func_tan::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
        case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
		{
			// null value is indicated by isNull
			double value = parm[0]->data()->getDoubleVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return tan(value);
		}
		break;

		case execplan::erydbSystemCatalog::DATE:
		{
			int32_t value = parm[0]->data()->getDateIntVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return tan((double)value);
		}
		break;

		case execplan::erydbSystemCatalog::DATETIME:
		{
			int64_t value = parm[0]->data()->getDatetimeIntVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return tan((double)value);
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "tan: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}

}


//
//	format
//

erydbSystemCatalog::ColType Func_format::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	return fp[0]->data()->resultType();
}

string Func_format::getStrVal(Row& row,
								FunctionParm& parm,
								bool& isNull,
								erydbSystemCatalog::ColType& operationColType)
{
	string value;
	int scale = 0;

	if (parm.size() > 1 ) 
		scale = parm[1]->data()->getIntVal(row, isNull);

	switch (parm[0]->data()->resultType().colDataType)
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
		{
			value = parm[0]->data()->getStrVal(row, isNull);
		}
		break;

        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
        case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		{
			double rawValue = parm[0]->data()->getDoubleVal(row, isNull);

			// roundup
			if (scale < 0) scale = 0;

			if (rawValue >= 0)
				rawValue += 0.5 / pow(10.0, scale);
			else
				rawValue -= 0.5 / pow(10.0, scale);
			
		    // double's can be *really* long to print out.  Max mysql
		    // is e308 so allow for 308 + 36 decimal places minimum.
		    char buf[384];
		    snprintf(buf, 384, "%0.36f", rawValue);
		    value = buf;
		}
		break;

		case execplan::erydbSystemCatalog::DATE:
		{
			value = dataconvert::DataConvert::dateToString1(parm[0]->data()->getDateIntVal(row, isNull));
		}
		break;

		case execplan::erydbSystemCatalog::DATETIME:
		{
			value = dataconvert::DataConvert::datetimeToString1(parm[0]->data()->getDatetimeIntVal(row, isNull));
		}
		break;

		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
		{
			ERYDB_Decimal decimal = parm[0]->data()->getDecimalVal(row, isNull);

			//perform rouding if needed
			if ( scale < 0 )
				scale = 0;
			if ( scale < decimal.scale )
			{
				int64_t d = 0;
				int64_t p = 1;
				if (!isNull && parm.size() > 1)
				{
					d = scale;
					if (!isNull)
						helpers::decimalPlaceDec(d, p, decimal.scale);
				}
	
				if (isNull)
					break;

				int64_t x = decimal.value;
				if (d > 0)
				{
					x = x * p;
				}
				else if (d < 0)
				{
					int64_t h = p / 2;  // 0.5
					if ((x >= h) || (x <= -h))
					{
						if (x >= 0)
							x += h;
						else
							x -= h;
	
						if (p != 0)
							x = x / p;
						else
							x = 0;
					}
					else
					{
						x = 0;
					}
				}
	
				// negative scale is not supported by CNX yet, set d to 0.
				if (decimal.scale < 0)
				{
					do
						x *= 10;
					while (++decimal.scale < 0);
				}
				decimal.value = x;
			}

			char buf[80];

			dataconvert::DataConvert::decimalToString( decimal.value, decimal.scale, buf, 80, parm[0]->data()->resultType().colDataType);

			value = buf;
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "format: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}

	if ( scale <= 0 )
	{
		// strip off any scale value
		string::size_type pos = value.find ('.',0);
		if (pos != string::npos)
			value = value.substr(0,pos);
		scale = 0;
	}
	else
	{
		// add or adjust scale value
		int pad = scale;
		string::size_type pos = value.find ('.',0);
		if (pos == string::npos)
			value = value.append(".");
		else
		{
			//if value begins with '.', prefix with a '0'
			if (pos == 0)
			{
				value = "0" + value;
				pos++;
			}
			//remove part of scale value, if needed
			value = value.substr(0,pos+scale+1);

			pad = scale - ( value.size() - pos-1 );
		}

		// pad extra with '0'
		if (*(value.data()) != '#')
		{
			for ( int i = 0 ; i < pad ; i ++ )
			{
				value = value.append("0");
			}
		}

		scale++; 
	}

	int comma = value.size() - scale;
	int end = 0;
	string::size_type pos = value.find ('-',0);
	if (pos != string::npos)
		end = 1;;

	while ((comma -= 3) > end)
	{
		value.insert(comma, ",");
	}

	return value;
}


//
//	radians
//

erydbSystemCatalog::ColType Func_radians::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	return fp[0]->data()->resultType();
}


double Func_radians::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
        case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
		{
			// null value is indicated by isNull
			double value = parm[0]->data()->getDoubleVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return radians(value);
		}
		break;

		case execplan::erydbSystemCatalog::DATE:
		{
			int32_t value = parm[0]->data()->getDateIntVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return radians((double)value);
		}
		break;

		case execplan::erydbSystemCatalog::DATETIME:
		{
			int64_t value = parm[0]->data()->getDatetimeIntVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return radians((double)value);
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "radians: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}

}

//
//	degrees
//

erydbSystemCatalog::ColType Func_degrees::operationType(FunctionParm& fp, erydbSystemCatalog::ColType& resultType)
{
	// operation type is not used by this functor
	return fp[0]->data()->resultType();
}


double Func_degrees::getDoubleVal(Row& row,
							FunctionParm& parm,
							bool& isNull,
							erydbSystemCatalog::ColType&)
{
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::erydbSystemCatalog::BIGINT:
		case execplan::erydbSystemCatalog::INT:
		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::TINYINT:
		case execplan::erydbSystemCatalog::SMALLINT:
        case execplan::erydbSystemCatalog::DOUBLE:
        case execplan::erydbSystemCatalog::UDOUBLE:
        case execplan::erydbSystemCatalog::FLOAT:
        case execplan::erydbSystemCatalog::UFLOAT:
		case execplan::erydbSystemCatalog::VARCHAR:
		case execplan::erydbSystemCatalog::CHAR:
		case execplan::erydbSystemCatalog::DECIMAL:
        case execplan::erydbSystemCatalog::UDECIMAL:
        case execplan::erydbSystemCatalog::UBIGINT:
        case execplan::erydbSystemCatalog::UINT:
        case execplan::erydbSystemCatalog::UMEDINT:
        case execplan::erydbSystemCatalog::UTINYINT:
        case execplan::erydbSystemCatalog::USMALLINT:
		{
			// null value is indicated by isNull
			double value = parm[0]->data()->getDoubleVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return degrees(value);
		}
		break;

		case execplan::erydbSystemCatalog::DATE:
		{
			int32_t value = parm[0]->data()->getDateIntVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return degrees((double)value);
		}
		break;

		case execplan::erydbSystemCatalog::DATETIME:
		{
			int64_t value = parm[0]->data()->getDatetimeIntVal(row, isNull);
			if (isNull)
			{
				isNull = true;
				return doubleNullVal();
			}
	
			return degrees((double)value);
		}
		break;

		default:
		{
			std::ostringstream oss;
			oss << "radians: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::ERYDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}

}



} // namespace funcexp
// vim:ts=4 sw=4:
