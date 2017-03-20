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

//   $Id: treenode.h 9635 2013-06-19 21:42:30Z bwilkinson $


/** @file */

#ifndef ERYDB_TREENODE_H
#define ERYDB_TREENODE_H

#include <string>
#include <iostream>
#include <cmath>
#include <boost/shared_ptr.hpp>

#ifdef _MSC_VER
#include <boost/regex.hpp>
#else
#include <regex.h>
#endif
#include <stdlib.h>
#include <unistd.h>

#include "erydbsystemcatalog.h"
#include "exceptclasses.h"
#include "dataconvert.h"
namespace messageqcpp {
class ByteStream;
}

namespace rowgroup {
class Row;
}

/**
 * Namespace
 */
namespace execplan{

typedef execplan::erydbSystemCatalog::ColType Type;


/**
 * @brief ERYDB_Decimal type
 *
 */
struct ERYDB_Decimal
{
	ERYDB_Decimal(): value(0), scale(0), precision(0) {}
	ERYDB_Decimal(int64_t val, int8_t s, uint8_t p) :
				value (val),
				scale(s),
				precision(p) {}

	int decimalComp(const ERYDB_Decimal& d) const
	{
		lldiv_t d1 = lldiv(value, ERYDB_pow[scale]);
		lldiv_t d2 = lldiv(d.value, ERYDB_pow[d.scale]);

		int ret = 0;
		if (d1.quot > d2.quot)
		{
			ret = 1;
		}
		else if (d1.quot < d2.quot)
		{
			ret = -1;
		}
		else
		{
			// rem carries the value's sign, but needs to be normalized.
			int64_t s = scale - d.scale;
			if (s < 0)
			{
				if ((d1.rem * ERYDB_pow[-s]) > d2.rem)
					ret = 1;
				else if ((d1.rem * ERYDB_pow[-s]) < d2.rem)
					ret = -1;
			}
			else
			{
				if (d1.rem > (d2.rem * ERYDB_pow[s]))
					ret = 1;
				else if (d1.rem < (d2.rem * ERYDB_pow[s]))
					ret = -1;
			}
		}

		return ret;
	}

	bool operator==(const ERYDB_Decimal& rhs) const
	{
		if (scale == rhs.scale)
			return value == rhs.value;
		else
			return (decimalComp(rhs) == 0);
	}
	bool operator>(const ERYDB_Decimal& rhs) const
	{
		if (scale == rhs.scale)
			return value > rhs.value;
		else
			return (decimalComp(rhs) > 0);
	}
	bool operator<(const ERYDB_Decimal& rhs) const
	{
		if (scale == rhs.scale)
			return value < rhs.value;
		else
			return (decimalComp(rhs) < 0);
	}
	bool operator>=(const ERYDB_Decimal& rhs) const
	{
		if (scale == rhs.scale)
			return value >= rhs.value;
		else
			return (decimalComp(rhs) >= 0);
	}
	bool operator<=(const ERYDB_Decimal& rhs) const
	{
		if (scale == rhs.scale)
			return value <= rhs.value;
		else
			return (decimalComp(rhs) <= 0);
	}
	bool operator!=(const ERYDB_Decimal& rhs) const
	{
		if (scale == rhs.scale)
			return value != rhs.value;
		else
			return (decimalComp(rhs) != 0);
	}

	int64_t value;
	int8_t  scale;	  // 0~18
	uint8_t precision;  // 1~18
};
typedef ERYDB_Decimal CNX_Decimal;

/**
 * @brief ERYDB_Regex struct
 *
 */
#ifdef _MSC_VER
typedef boost::regex ERYDB_Regex;
#else
typedef regex_t ERYDB_Regex;
#endif

typedef ERYDB_Regex CNX_Regex;

typedef boost::shared_ptr<ERYDB_Regex> SP_ERYDB_Regex;
typedef SP_ERYDB_Regex SP_CNX_Regex;

/** Trim trailing 0 from val. All insignificant zeroes to the right of the
 *  decimal point are removed. Also, the decimal point is not included on
 *  whole numbers. It works like %g flag with printf, but always print
 *  double value in fixed-point notation.
 *
 *  @parm val valid double value in fixed-point notation from printf %f.
 *            No format validation is perfomed in this function.
 *  @parm length length of the buffer val
 */
inline std::string removeTrailing0(char* val, uint32_t length)
{
	char* ptr = val;
	uint32_t i = 0;
	bool decimal_point = false;
	for (; i < length; i++, ptr++)
	{
		if (*ptr == '+' || *ptr == '-' || (*ptr >= '0' && *ptr <= '9'))
		{
			continue;
		}
		if (*ptr == '.')
		{
			decimal_point = true;
			continue;
		}
		*ptr = 0;
		break;
	}

	if (decimal_point)
	{
		for (i = i-1; i >= 0; i--)
		{
			if (val[i] == '0')
			{
				val[i] = 0;
			}
			else if (val[i] == '.')
			{
				val[i] = 0;
				break;
			}
			else
			{
				break;
			}
		}
	}
	return std::string(val);
}

/**
 * @brief Result type added for F&E framework
 *
 */
struct Result
{
	Result():intVal(0), uintVal(0), origIntVal(0), dummy(0),
			doubleVal(0), floatVal(0), boolVal(false),
			strVal(""), decimalVal(ERYDB_Decimal(0,0,0)),
			valueConverted(false) {}
	int64_t intVal;
	uint64_t uintVal;
	uint64_t origIntVal;
	// clear up the memory following origIntVal to make sure null terminated string
	// when converting origIntVal
	uint64_t dummy;
	double doubleVal;
	float floatVal;
	bool boolVal;
	std::string strVal;
	ERYDB_Decimal decimalVal;
	bool valueConverted;
};

/**
 * @brief An abstract class to represent a node data on the expression tree
 *
 */
class TreeNode
{
public:
	TreeNode();
	TreeNode(const TreeNode& rhs);
	virtual ~TreeNode();
	virtual const std::string data() const = 0;
	virtual void data(const std::string data) = 0;
	virtual const std::string toString() const = 0;
	virtual TreeNode* clone() const = 0;

	/**
	 * Interface for serialization
	 */

	/** @brief Convert *this to a stream of bytes
	 *
	 * Convert *this to a stream of bytes.
	 * @param b The ByteStream to add *this to.
	 */
	virtual void serialize(messageqcpp::ByteStream& b) const = 0;

	/** @brief Construct a TreeNode from a stream of bytes
	 *
	 * Construct a TreeNode from a stream of bytes.
	 * @param b The ByteStream to parse
	 * @return The newly allocated TreeNode
	 */
	virtual void unserialize(messageqcpp::ByteStream &b) = 0;

	/** @brief Do a deep, strict (as opposed to semantic) equivalence test
	 *
	 * Do a deep, strict (as opposed to semantic) equivalence test.
	 * @return true iff every member of t is a duplicate copy of every member of this; false otherwise
	 */
	virtual bool operator==(const TreeNode* t) const = 0;

	/** @brief Do a deep, strict (as opposed to semantic) equivalence test
	 *
	 * Do a deep, strict (as opposed to semantic) equivalence test.
	 * @return false iff every member of t is a duplicate copy of every member of this; true otherwise
	 */
	virtual bool operator!=(const TreeNode* t) const = 0;

	// derivedTable mutator and accessor
	virtual const std::string& derivedTable() const
	{ return fDerivedTable; }

	virtual void derivedTable(const std::string& derivedTable)
	{ fDerivedTable = derivedTable; }

	// must to be implented by treenode that could potentially belong to
	// one single derived table
	virtual void setDerivedTable()
	{ fDerivedTable = ""; }

	virtual TreeNode* derivedRefCol() const
	{ return fDerivedRefCol; }

	virtual void derivedRefCol(TreeNode* derivedRefCol)
	{ fDerivedRefCol = derivedRefCol; }

	virtual uint64_t refCount() const
	{ return fRefCount; }

	virtual void refCount (const uint64_t refCount)
	{ fRefCount = refCount; }

	// the inc and dec functions are used by connector single thread.
	virtual void decRefCount()
	{ fRefCount--; }

	virtual void incRefCount()
	{ fRefCount++; }

	/***********************************************************************
	 *                     F&E framework                                   *
	 ***********************************************************************/
	virtual const std::string& getStrVal(rowgroup::Row& row, bool& isNull) {return fResult.strVal;}
	virtual int64_t getIntVal(rowgroup::Row& row, bool& isNull) {return fResult.intVal;}
	virtual uint64_t getUintVal(rowgroup::Row& row, bool& isNull) {return fResult.uintVal;}
	virtual float getFloatVal(rowgroup::Row& row, bool& isNull) {return fResult.floatVal;}
	virtual double getDoubleVal(rowgroup::Row& row, bool& isNull) {return fResult.doubleVal;}
	virtual ERYDB_Decimal getDecimalVal(rowgroup::Row& row, bool& isNull) {return fResult.decimalVal;}
	virtual bool getBoolVal(rowgroup::Row& row, bool& isNull) {return fResult.boolVal;}
	virtual int32_t getDateIntVal(rowgroup::Row& row, bool& isNull) {return fResult.intVal;}
	virtual int64_t getDatetimeIntVal(rowgroup::Row& row, bool& isNull) {return fResult.intVal;}
	virtual void evaluate(rowgroup::Row& row, bool& isNull) {}

	inline bool getBoolVal();
	inline const std::string& getStrVal();
	inline int64_t getIntVal();
	inline uint64_t getUintVal();
	inline float getFloatVal();
	inline double getDoubleVal();
	inline ERYDB_Decimal getDecimalVal();
	inline int32_t getDateIntVal();
	inline int64_t getDatetimeIntVal();

	virtual const execplan::erydbSystemCatalog::ColType& resultType() const { return fResultType; }
	virtual execplan::erydbSystemCatalog::ColType& resultType() { return fResultType; }
	virtual void resultType ( const execplan::erydbSystemCatalog::ColType& resultType ) ;
	virtual void operationType(const Type& type) {fOperationType = type;}
	virtual const execplan::erydbSystemCatalog::ColType& operationType() const {return fOperationType;}

	// result mutator and accessor. for speical functor to set for optimization.
	virtual void result(const Result& result) { fResult = result; }
	virtual const Result& result() const { return fResult; }

	// regex mutator and accessor
	virtual void regex(SP_ERYDB_Regex regex) { fRegex = regex; }
	virtual SP_ERYDB_Regex regex() const { return fRegex; }

protected:
	Result fResult;
	execplan::erydbSystemCatalog::ColType fResultType; // mapped from mysql data type
	execplan::erydbSystemCatalog::ColType fOperationType; // operator type, could be different from the result type
	SP_ERYDB_Regex fRegex;

	// double's range is +/-1.7E308 with at least 15 digits of precision
	char tmp[312]; // for conversion use

	// @bug5635 If any item involved in this filter belongs to a derived table,
	// the derived table alias is added to the reference vector.
	std::string fDerivedTable;
	uint64_t fRefCount;
	TreeNode* fDerivedRefCol;

private:
	//default okay
	//TreeNode& operator=(const TreeNode& rhs);
};

inline bool TreeNode::getBoolVal()
{
	switch (fResultType.colDataType)
	{
		case erydbSystemCatalog::CHAR:
			if (fResultType.colWidth <= 8)
				return (atoi((char*)(&fResult.origIntVal)) != 0);
			return (atoi(fResult.strVal.c_str()) != 0);
		case erydbSystemCatalog::VARCHAR:
			if (fResultType.colWidth <= 7)
				return (atoi((char*)(&fResult.origIntVal)) != 0);
			return (atoi(fResult.strVal.c_str()) != 0);
		//FIXME: Huh???
		case erydbSystemCatalog::VARBINARY:
			if (fResultType.colWidth <= 7)
				return (atoi((char*)(&fResult.origIntVal)) != 0);
			return (atoi(fResult.strVal.c_str()) != 0);
		case erydbSystemCatalog::BIGINT:
		case erydbSystemCatalog::SMALLINT:
		case erydbSystemCatalog::MEDINT:
		case erydbSystemCatalog::TINYINT:
		case erydbSystemCatalog::INT:
		case erydbSystemCatalog::DATE:
		case erydbSystemCatalog::DATETIME:
			return (fResult.intVal != 0);
		case erydbSystemCatalog::UBIGINT:
		case erydbSystemCatalog::USMALLINT:
		case erydbSystemCatalog::UMEDINT:
		case erydbSystemCatalog::UTINYINT:
		case erydbSystemCatalog::UINT:
			return (fResult.uintVal != 0);
		case erydbSystemCatalog::FLOAT:
		case erydbSystemCatalog::UFLOAT:
			return (fResult.floatVal != 0);
		case erydbSystemCatalog::DOUBLE:
		case erydbSystemCatalog::UDOUBLE:
			return (fResult.doubleVal != 0);
		case erydbSystemCatalog::DECIMAL:
		case erydbSystemCatalog::UDECIMAL:
			return (fResult.decimalVal.value != 0);
		default:
			throw logging::InvalidConversionExcept("TreeNode::getBoolVal: Invalid conversion.");
	}
	return fResult.boolVal;
}

inline const std::string& TreeNode::getStrVal()
{
	switch (fResultType.colDataType)
	{
		case erydbSystemCatalog::CHAR:
			if (fResultType.colWidth <= 8)
				fResult.strVal = (char*)(&fResult.origIntVal);
			break;
		case erydbSystemCatalog::VARCHAR:
			if (fResultType.colWidth <= 7)
				fResult.strVal = (char*)(&fResult.origIntVal);
			break;
		//FIXME: ???
		case erydbSystemCatalog::VARBINARY:
			if (fResultType.colWidth <= 7)
				fResult.strVal = (char*)(&fResult.origIntVal);
			break;
		case erydbSystemCatalog::BIGINT:
		case erydbSystemCatalog::SMALLINT:
		case erydbSystemCatalog::MEDINT:
		case erydbSystemCatalog::TINYINT:
		case erydbSystemCatalog::INT:
		{
#ifndef __LP64__
			snprintf(tmp, 20, "%lld", fResult.intVal);
#else
			snprintf(tmp, 20, "%ld", fResult.intVal);
#endif
			fResult.strVal = std::string(tmp);
			break;
		}
		case erydbSystemCatalog::UBIGINT:
		case erydbSystemCatalog::USMALLINT:
		case erydbSystemCatalog::UMEDINT:
		case erydbSystemCatalog::UTINYINT:
		case erydbSystemCatalog::UINT:
		{
#ifndef __LP64__
			snprintf(tmp, 20, "%llu", fResult.uintVal);
#else
			snprintf(tmp, 20, "%lu", fResult.uintVal);
#endif
			fResult.strVal = std::string(tmp);
			break;
		}
		case erydbSystemCatalog::FLOAT:
		case erydbSystemCatalog::UFLOAT:
		{
			if ((fabs(fResult.floatVal) > (1.0 / ERYDB_pow[4])) &&
				(fabs(fResult.floatVal) < (float) ERYDB_pow[6]))
			{
				snprintf(tmp, 312, "%f", fResult.floatVal);
				fResult.strVal = removeTrailing0(tmp, 312);
			}
			else
			{
				// MCOL-299 Print scientific with 5 mantissa and no + sign for exponent
				int exponent  = (int)floor(log10( fabs(fResult.floatVal)));  // This will round down the exponent
				double base   = fResult.floatVal * pow(10, -1.0*exponent);
				if (std::isnan(exponent) || std::isnan(base))
				{
					snprintf(tmp, 312, "%f", fResult.floatVal);
					fResult.strVal = removeTrailing0(tmp, 312);
				}
				else
				{
					snprintf(tmp, 312, "%.5f", base);
					fResult.strVal = removeTrailing0(tmp, 312);
					snprintf(tmp, 312, "e%02d", exponent);
					fResult.strVal += tmp;
				}
	
//				snprintf(tmp, 312, "%e.5", fResult.floatVal);
//				fResult.strVal = tmp;
			}
			break;
		}
		case erydbSystemCatalog::DOUBLE:
		case erydbSystemCatalog::UDOUBLE:
		{
			if ((fabs(fResult.doubleVal) > (1.0 / ERYDB_pow[13])) &&
				(fabs(fResult.doubleVal) < (float) ERYDB_pow[15]))
			{
				snprintf(tmp, 312, "%f", fResult.doubleVal);
				fResult.strVal = removeTrailing0(tmp, 312);
			}
			else
			{
				// MCOL-299 Print scientific with 9 mantissa and no + sign for exponent
				int exponent  = (int)floor(log10( fabs(fResult.doubleVal)));  // This will round down the exponent
				double base   = fResult.doubleVal * pow(10, -1.0*exponent);
				if (std::isnan(exponent) || std::isnan(base))
				{
					snprintf(tmp, 312, "%f", fResult.doubleVal);
					fResult.strVal = removeTrailing0(tmp, 312);
				}
				else
				{
					snprintf(tmp, 312, "%.9f", base);
					fResult.strVal = removeTrailing0(tmp, 312);
					snprintf(tmp, 312, "e%02d", exponent);
					fResult.strVal += tmp;
				}
//				snprintf(tmp, 312, "%e", fResult.doubleVal);
//				fResult.strVal = tmp;
			}
			break;
		}
		case erydbSystemCatalog::DECIMAL:
		case erydbSystemCatalog::UDECIMAL:
		{
			dataconvert::DataConvert::decimalToString(fResult.decimalVal.value, fResult.decimalVal.scale, tmp, 22, fResultType.colDataType);
			fResult.strVal = std::string(tmp);
			break;
		}
		case erydbSystemCatalog::DATE:
		{
			dataconvert::DataConvert::dateToString(fResult.intVal, tmp, 255);
			fResult.strVal = std::string(tmp);
			break;
		}
		case erydbSystemCatalog::DATETIME:
		{
			dataconvert::DataConvert::datetimeToString(fResult.intVal, tmp, 255);
			fResult.strVal = std::string(tmp);
			break;
		}
		default:
			throw logging::InvalidConversionExcept("TreeNode::getStrVal: Invalid conversion.");
	}
	return fResult.strVal;
}

inline int64_t TreeNode::getIntVal()
{
	switch (fResultType.colDataType)
	{
		case erydbSystemCatalog::CHAR:
			if (fResultType.colWidth <= 8)
				return fResult.intVal;
			return atoll(fResult.strVal.c_str());
		case erydbSystemCatalog::VARCHAR:
			if (fResultType.colWidth <= 7)
				return fResult.intVal;
			return atoll(fResult.strVal.c_str());
		//FIXME: ???
		case erydbSystemCatalog::VARBINARY:
			if (fResultType.colWidth <= 7)
				return fResult.intVal;
			return atoll(fResult.strVal.c_str());
		case erydbSystemCatalog::BIGINT:
		case erydbSystemCatalog::TINYINT:
		case erydbSystemCatalog::SMALLINT:
		case erydbSystemCatalog::MEDINT:
		case erydbSystemCatalog::INT:
			return fResult.intVal;
		case erydbSystemCatalog::UBIGINT:
		case erydbSystemCatalog::UTINYINT:
		case erydbSystemCatalog::USMALLINT:
		case erydbSystemCatalog::UMEDINT:
		case erydbSystemCatalog::UINT:
			return fResult.uintVal;
		case erydbSystemCatalog::FLOAT:
		case erydbSystemCatalog::UFLOAT:
			return (int64_t)fResult.floatVal;
		case erydbSystemCatalog::DOUBLE:
		case erydbSystemCatalog::UDOUBLE:
			return (int64_t)fResult.doubleVal;
		case erydbSystemCatalog::DECIMAL:
		case erydbSystemCatalog::UDECIMAL:
		{
			return (int64_t)(fResult.decimalVal.value / pow((double)10, fResult.decimalVal.scale));
		}
		case erydbSystemCatalog::DATE:
		case erydbSystemCatalog::DATETIME:
			return fResult.intVal;
		default:
			throw logging::InvalidConversionExcept("TreeNode::getIntVal: Invalid conversion.");
	}
	return fResult.intVal;
}
inline uint64_t TreeNode::getUintVal()
{
	switch (fResultType.colDataType)
	{
		case erydbSystemCatalog::BIGINT:
		case erydbSystemCatalog::TINYINT:
		case erydbSystemCatalog::SMALLINT:
		case erydbSystemCatalog::MEDINT:
		case erydbSystemCatalog::INT:
			return fResult.intVal;
		case erydbSystemCatalog::UBIGINT:
		case erydbSystemCatalog::UTINYINT:
		case erydbSystemCatalog::USMALLINT:
		case erydbSystemCatalog::UMEDINT:
		case erydbSystemCatalog::UINT:
			return fResult.uintVal;
		case erydbSystemCatalog::FLOAT:
		case erydbSystemCatalog::UFLOAT:
			return (uint64_t)fResult.floatVal;
		case erydbSystemCatalog::DOUBLE:
		case erydbSystemCatalog::UDOUBLE:
			return (uint64_t)fResult.doubleVal;
		case erydbSystemCatalog::DECIMAL:
		case erydbSystemCatalog::UDECIMAL:
		{
			return (uint64_t)(fResult.decimalVal.value / pow((double)10, fResult.decimalVal.scale));
		}
		case erydbSystemCatalog::DATE:
		case erydbSystemCatalog::DATETIME:
			return fResult.intVal;
		default:
			throw logging::InvalidConversionExcept("TreeNode::getIntVal: Invalid conversion.");
	}
	return fResult.intVal;
}
inline float TreeNode::getFloatVal()
{
	switch (fResultType.colDataType)
	{
		case erydbSystemCatalog::CHAR:
			if (fResultType.colWidth <= 8)
				return atof((char*)(&fResult.origIntVal));
			return atof(fResult.strVal.c_str());
		case erydbSystemCatalog::VARCHAR:
			if (fResultType.colWidth <= 7)
				return atof((char*)(&fResult.origIntVal));
			return atof(fResult.strVal.c_str());
		//FIXME: ???
		case erydbSystemCatalog::VARBINARY:
			if (fResultType.colWidth <= 7)
				return atof((char*)(&fResult.origIntVal));
			return atof(fResult.strVal.c_str());
		case erydbSystemCatalog::BIGINT:
		case erydbSystemCatalog::TINYINT:
		case erydbSystemCatalog::SMALLINT:
		case erydbSystemCatalog::MEDINT:
		case erydbSystemCatalog::INT:
			return (float)fResult.intVal;
		case erydbSystemCatalog::UBIGINT:
		case erydbSystemCatalog::UTINYINT:
		case erydbSystemCatalog::USMALLINT:
		case erydbSystemCatalog::UMEDINT:
		case erydbSystemCatalog::UINT:
			return (float)fResult.uintVal;
		case erydbSystemCatalog::FLOAT:
		case erydbSystemCatalog::UFLOAT:
			return fResult.floatVal;
		case erydbSystemCatalog::DOUBLE:
		case erydbSystemCatalog::UDOUBLE:
			return (float)fResult.doubleVal;
		case erydbSystemCatalog::DECIMAL:
		{
			return (fResult.decimalVal.value / pow((double)10, fResult.decimalVal.scale));
		}
		case erydbSystemCatalog::DATE:
		case erydbSystemCatalog::DATETIME:
			return (float)fResult.intVal;
		default:
			throw logging::InvalidConversionExcept("TreeNode::getFloatVal: Invalid conversion.");
	}
	return fResult.floatVal;
}
inline double TreeNode::getDoubleVal()
{
	switch (fResultType.colDataType)
	{
		case erydbSystemCatalog::CHAR:
			if (fResultType.colWidth <= 8)
				return strtod((char*)(&fResult.origIntVal), NULL);
			return strtod(fResult.strVal.c_str(), NULL);
		case erydbSystemCatalog::VARCHAR:
			if (fResultType.colWidth <= 7)
				return strtod((char*)(&fResult.origIntVal), NULL);
			return strtod(fResult.strVal.c_str(), NULL);
		//FIXME: ???
		case erydbSystemCatalog::VARBINARY:
			if (fResultType.colWidth <= 7)
				return strtod((char*)(&fResult.origIntVal), NULL);
			return strtod(fResult.strVal.c_str(), NULL);
		case erydbSystemCatalog::BIGINT:
		case erydbSystemCatalog::TINYINT:
		case erydbSystemCatalog::SMALLINT:
		case erydbSystemCatalog::MEDINT:
		case erydbSystemCatalog::INT:
			return (double)fResult.intVal;
		case erydbSystemCatalog::UBIGINT:
		case erydbSystemCatalog::UTINYINT:
		case erydbSystemCatalog::USMALLINT:
		case erydbSystemCatalog::UMEDINT:
		case erydbSystemCatalog::UINT:
			return (double)fResult.uintVal;
		case erydbSystemCatalog::FLOAT:
		case erydbSystemCatalog::UFLOAT:
			return (double)fResult.floatVal;
		case erydbSystemCatalog::DOUBLE:
		case erydbSystemCatalog::UDOUBLE:
			return fResult.doubleVal;
		case erydbSystemCatalog::DECIMAL:
		case erydbSystemCatalog::UDECIMAL:
		{
			// this may not be accurate. if this is problematic, change to pre-calculated power array.
			return (double)(fResult.decimalVal.value / pow((double)10, fResult.decimalVal.scale));
		}
		case erydbSystemCatalog::DATE:
		case erydbSystemCatalog::DATETIME:
			return (double)fResult.intVal;
		default:
			throw logging::InvalidConversionExcept("TreeNode::getDoubleVal: Invalid conversion.");
	}
	return fResult.doubleVal;
}
inline ERYDB_Decimal TreeNode::getDecimalVal()
{
	switch (fResultType.colDataType)
	{
		case erydbSystemCatalog::CHAR:
		case erydbSystemCatalog::VARCHAR:
			throw logging::InvalidConversionExcept("TreeNode::getDecimalVal: non-support conversion from string");
		case erydbSystemCatalog::VARBINARY:
			throw logging::InvalidConversionExcept("TreeNode::getDecimalVal: non-support conversion from binary string");
		case erydbSystemCatalog::BIGINT:
		case erydbSystemCatalog::MEDINT:
		case erydbSystemCatalog::INT:
		case erydbSystemCatalog::SMALLINT:
		case erydbSystemCatalog::TINYINT:
			fResult.decimalVal.value =(int64_t)(fResult.intVal * pow((double)10, fResultType.scale));
			fResult.decimalVal.scale = fResultType.scale;
			fResult.decimalVal.precision = fResultType.precision;
			break;
		case erydbSystemCatalog::UBIGINT:
		case erydbSystemCatalog::UMEDINT:
		case erydbSystemCatalog::UINT:
		case erydbSystemCatalog::USMALLINT:
		case erydbSystemCatalog::UTINYINT:
			fResult.decimalVal.value =(int64_t)(fResult.uintVal * pow((double)10, fResultType.scale));
			fResult.decimalVal.scale = fResultType.scale;
			fResult.decimalVal.precision = fResultType.precision;
			break;
		case erydbSystemCatalog::DATE:
		case erydbSystemCatalog::DATETIME:
			throw logging::InvalidConversionExcept("TreeNode::getDecimalVal: Invalid conversion from datetime.");
		case erydbSystemCatalog::FLOAT:
			throw logging::InvalidConversionExcept("TreeNode::getDecimalVal: non-support conversion from float");
		case erydbSystemCatalog::UFLOAT:
			throw logging::InvalidConversionExcept("TreeNode::getDecimalVal: non-support conversion from float unsigned");
		case erydbSystemCatalog::DOUBLE:
			throw logging::InvalidConversionExcept("TreeNode::getDecimalVal: non-support conversion from double");
		case erydbSystemCatalog::UDOUBLE:
			throw logging::InvalidConversionExcept("TreeNode::getDecimalVal: non-support conversion from double unsigned");
		case erydbSystemCatalog::DECIMAL:
		case erydbSystemCatalog::UDECIMAL:
			return fResult.decimalVal;
		default:
			throw logging::InvalidConversionExcept("TreeNode::getDecimalVal: Invalid conversion.");
	}
	return fResult.decimalVal;
}

inline int64_t TreeNode::getDatetimeIntVal()
{
	if (fResultType.colDataType == execplan::erydbSystemCatalog::DATE)
		return (fResult.intVal & 0x00000000FFFFFFC0LL) << 32;
	else if (fResultType.colDataType == execplan::erydbSystemCatalog::DATETIME)
		//return (fResult.intVal & 0xFFFFFFFFFFF00000LL);
		return (fResult.intVal);
	else
		return getIntVal();
}

inline int32_t TreeNode::getDateIntVal()
{
	if (fResultType.colDataType == execplan::erydbSystemCatalog::DATETIME)
		return (((int32_t)(fResult.intVal >> 32) & 0xFFFFFFC0) | 0x3E);
	else if (fResultType.colDataType == execplan::erydbSystemCatalog::DATE)
		return ((fResult.intVal & 0xFFFFFFC0) | 0x3E);
	else
		return getIntVal();
}

typedef boost::shared_ptr<TreeNode> STNP;

/**
* Operations
*/
std::ostream& operator<<(std::ostream& output, const TreeNode& rhs);

}

#endif
