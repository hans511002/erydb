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

//  $Id: functor_bool.h 3495 2013-01-21 14:09:51Z rdempsey $

/** @file */

#ifndef FUNCTOR_BOOL_H
#define FUNCTOR_BOOL_H


#include "functor.h"


namespace funcexp
{

/** @brief Func_Bool class
  *    For function that returns a boolean result.
  *        Must implement getBoolVal()
  *        Implement any other methods that behave differently from the default.
  */
class Func_Bool : public Func
{
public:
	Func_Bool() {}
	Func_Bool(const std::string& funcName) : Func(funcName) {}
	virtual ~Func_Bool() {}

/*
	virtual bool getBoolVal(rowgroup::Row& row,
								FunctionParm& fp,
								bool& isNull,
								execplan::erydbSystemCatalog::ColType& op_ct) = 0;
*/

	int64_t getIntVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct)
	{ return (getBoolVal(row, fp, isNull, op_ct) ? 1 : 0); }

	double getDoubleVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct)
	{ return (getBoolVal(row, fp, isNull, op_ct) ? 1.0 : 0.0); }

	std::string getStrVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct)
	{ return (getBoolVal(row, fp, isNull, op_ct) ? "1" : "0"); }

	execplan::ERYDB_Decimal getDecimalVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct)
	{ return execplan::ERYDB_Decimal(getIntVal(row, fp, isNull, op_ct),0,0); }

	int32_t getDateIntVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct)
	{ isNull = true; return 0; }

	int64_t getDatetimeIntVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct)
	{ isNull = true; return 0; }
};


/** @brief Func_between class
  */
class Func_between : public Func_Bool
{
public:
	Func_between() : Func_Bool("between") {}
	virtual ~Func_between() {}

	execplan::erydbSystemCatalog::ColType operationType(FunctionParm& fp, execplan::erydbSystemCatalog::ColType& resultType);

	bool getBoolVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct);
};


/** @brief Func_notbetween class
  */
class Func_notbetween : public Func_Bool
{
public:
	Func_notbetween() : Func_Bool("notbetween") {}
	virtual ~Func_notbetween() {}

	execplan::erydbSystemCatalog::ColType operationType(FunctionParm& fp, execplan::erydbSystemCatalog::ColType& resultType);

	bool getBoolVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct);
};


/** @brief Func_in class
  */
class Func_in : public Func_Bool
{
public:
	Func_in() : Func_Bool("in") {}
	virtual ~Func_in() {}

	execplan::erydbSystemCatalog::ColType operationType(FunctionParm& fp, execplan::erydbSystemCatalog::ColType& resultType);

	bool getBoolVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct);
};


/** @brief Func_notin class
  */
class Func_notin : public Func_Bool
{
public:
	Func_notin() : Func_Bool("notin") {}
	virtual ~Func_notin() {}

	execplan::erydbSystemCatalog::ColType operationType(FunctionParm& fp, execplan::erydbSystemCatalog::ColType& resultType);

	bool getBoolVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct);
};


/** @brief Func_regexp class
  */
class Func_regexp : public Func_Bool
{
public:
	Func_regexp() : Func_Bool("regexp") {}
	virtual ~Func_regexp() {}

	execplan::erydbSystemCatalog::ColType operationType(FunctionParm& fp, execplan::erydbSystemCatalog::ColType& resultType);

	bool getBoolVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct);
};


/** @brief Func_isnull class
  */
class Func_isnull : public Func_Bool
{
public:
	/*
	 * Constructor. Pass the function name to the base constructor.
	 */
	Func_isnull():fIsNotNull(false) {}
	Func_isnull(bool isnotnull) : fIsNotNull(isnotnull) {}
	/*
	 * Destructor. ERYDB_add does not need to do anything here to clean up.
	 */
	virtual ~Func_isnull() {}

	/**
	 * Decide on the function's operation type
	 */
	execplan::erydbSystemCatalog::ColType operationType(FunctionParm& fp, execplan::erydbSystemCatalog::ColType& resultType);

	bool getBoolVal(rowgroup::Row& row,
						FunctionParm& fp,
						bool& isNull,
						execplan::erydbSystemCatalog::ColType& op_ct);

private:
	bool fIsNotNull;
};


}

#endif
