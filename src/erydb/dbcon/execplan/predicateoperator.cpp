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

/***********************************************************************
*   $Id: predicateoperator.cpp 9306 2013-03-12 15:49:11Z rdempsey $
*
*
***********************************************************************/
#include <iostream>

#include "bytestream.h"
#include "predicateoperator.h"
#include "objectreader.h"

#include "liboamcpp.h"
using namespace oam;

using namespace std;

bool futf8 = true;

namespace {
    
/**@brief util struct for converting string to lower case */
struct to_lower
{
    char operator() (char c) const { return tolower(c); }
};

//Trim any leading/trailing ws
const string lrtrim(const string& in)
{
	string::size_type p1;
	p1 = in.find_first_not_of(" \t\n");
	if (p1 == string::npos) p1 = 0;
	string::size_type p2;
	p2 = in.find_last_not_of(" \t\n");
	if (p2 == string::npos) p2 = in.size() - 1;
	return string(in, p1, (p2 - p1 + 1));
}

}

namespace execplan {
    
/**
 * Constructors/Destructors
 */
PredicateOperator::PredicateOperator()
{
	Oam oam;
    // get and set locale language    
	string systemLang = "C";

	try{
        oam.getSystemConfig("SystemLang", systemLang);
    }
    catch(...)
    {}

    if ( systemLang != "en_US.UTF-8" &&
        systemLang.find("UTF") != string::npos )
        futf8 = true;
}

PredicateOperator::PredicateOperator(const string& operatorName)
{
	Oam oam;
    // get and set locale language    
	string systemLang = "C";

	try{
        oam.getSystemConfig("SystemLang", systemLang);
    }
    catch(...)
    {}

    if ( systemLang != "en_US.UTF-8" &&
        systemLang.find("UTF") != string::npos )
        futf8 = true;

	data(operatorName);
}					

PredicateOperator::PredicateOperator(const PredicateOperator& rhs) : Operator(rhs)
{
	Oam oam;
    // get and set locale language    
	string systemLang = "C";

	try{
        oam.getSystemConfig("SystemLang", systemLang);
    }
    catch(...)
    {}

    if ( systemLang != "en_US.UTF-8" &&
        systemLang.find("UTF") != string::npos )
        futf8 = true;

	data(rhs.data());
}

PredicateOperator:: ~PredicateOperator()
{
}

/**
 * Operations
 */

/**
 * friend function
 */
ostream& operator<<(ostream &output, const PredicateOperator& rhs) 
{
	output << rhs.toString() << endl;
	output << "OpType=" << rhs.operationType().colDataType << endl;
	return output;
} 

/**
 * The serialization interface
 */
void PredicateOperator::serialize(messageqcpp::ByteStream& b) const
{
	b << (ObjectReader::id_t) ObjectReader::PREDICATEOPERATOR;
	//b << fData;
	Operator::serialize(b);
}

void PredicateOperator::unserialize(messageqcpp::ByteStream& b)
{
	ObjectReader::checkType(b, ObjectReader::PREDICATEOPERATOR);
	//b >> fData;
	Operator::unserialize(b);
}

bool PredicateOperator::operator==(const PredicateOperator& t) const
{
	if (fData == t.fData)
		return true;
	return false;
}

bool PredicateOperator::operator==(const TreeNode* t) const
{
	const PredicateOperator *o;

	o = dynamic_cast<const PredicateOperator*>(t);
	if (o == NULL)
		return false;
	return *this == *o;
}

bool PredicateOperator::operator!=(const PredicateOperator& t) const
{
	return (!(*this == t));
}

bool PredicateOperator::operator!=(const TreeNode* t) const
{
	return (!(*this == t));
}

//FIXME: VARBINARY???
void PredicateOperator::setOpType(Type& l, Type& r)
{
	if ( l.colDataType == execplan::erydbSystemCatalog::DATETIME ||
		   l.colDataType == execplan::erydbSystemCatalog::DATE )
	{
		switch (r.colDataType)
		{
			case execplan::erydbSystemCatalog::CHAR:
			case execplan::erydbSystemCatalog::VARCHAR:	
				fOperationType = l;
				break;
			case execplan::erydbSystemCatalog::DATETIME:
				fOperationType.colDataType = execplan::erydbSystemCatalog::DATETIME;
				fOperationType.colWidth = 8;
				break;
			case execplan::erydbSystemCatalog::DATE:
				fOperationType = l;
				break;
			default:
				fOperationType.colDataType = execplan::erydbSystemCatalog::DOUBLE;
				fOperationType.colWidth = 8;
				break;
		} 
	}
	else if ( r.colDataType == execplan::erydbSystemCatalog::DATETIME ||
		   r.colDataType == execplan::erydbSystemCatalog::DATE )
	{
		switch (l.colDataType)
		{
			case execplan::erydbSystemCatalog::CHAR:
			case execplan::erydbSystemCatalog::VARCHAR:	
				fOperationType.colDataType = execplan::erydbSystemCatalog::VARCHAR;
				fOperationType.colWidth = 255;
				break;
			case execplan::erydbSystemCatalog::DATETIME:
				fOperationType.colDataType = execplan::erydbSystemCatalog::DATETIME;
				fOperationType.colWidth = 8;
				break;
			case execplan::erydbSystemCatalog::DATE:
				fOperationType = r;
				break;
			default:
				fOperationType.colDataType = execplan::erydbSystemCatalog::DOUBLE;
				fOperationType.colWidth = 8;
				break;
		} 
	}
	else if (l.colDataType == execplan::erydbSystemCatalog::DECIMAL ||
             l.colDataType == execplan::erydbSystemCatalog::UDECIMAL)
	{
		switch (r.colDataType)
		{			
			case execplan::erydbSystemCatalog::DECIMAL:
            case execplan::erydbSystemCatalog::UDECIMAL:
			{
				// should following the result type that MySQL gives
				fOperationType = l;
				fOperationType.scale = (l.scale > r.scale ? l.scale : r.scale);
				break;
			}
			case execplan::erydbSystemCatalog::INT:
			case execplan::erydbSystemCatalog::MEDINT:
			case execplan::erydbSystemCatalog::TINYINT:
			case execplan::erydbSystemCatalog::BIGINT:
            case execplan::erydbSystemCatalog::UINT:
            case execplan::erydbSystemCatalog::UMEDINT:
            case execplan::erydbSystemCatalog::UTINYINT:
            case execplan::erydbSystemCatalog::UBIGINT:
				fOperationType.colDataType = execplan::erydbSystemCatalog::DECIMAL;
				fOperationType.scale = l.scale;
				fOperationType.colWidth = 8;
				break;
			default:
				fOperationType.colDataType = execplan::erydbSystemCatalog::DOUBLE;
				fOperationType.colWidth = 8;							
		}
	}
	else if (r.colDataType == execplan::erydbSystemCatalog::DECIMAL ||
             r.colDataType == execplan::erydbSystemCatalog::UDECIMAL)
	{
		switch (l.colDataType)
		{
			case execplan::erydbSystemCatalog::DECIMAL:
            case execplan::erydbSystemCatalog::UDECIMAL:
			{
				// should following the result type that MySQL gives based on the following logic?
				// @NOTE is this trustable?
				fOperationType = fResultType;
				break;
			}
			case execplan::erydbSystemCatalog::INT:
			case execplan::erydbSystemCatalog::MEDINT:
			case execplan::erydbSystemCatalog::TINYINT:
			case execplan::erydbSystemCatalog::BIGINT:
            case execplan::erydbSystemCatalog::UINT:
            case execplan::erydbSystemCatalog::UMEDINT:
            case execplan::erydbSystemCatalog::UTINYINT:
            case execplan::erydbSystemCatalog::UBIGINT:
				fOperationType.colDataType = execplan::erydbSystemCatalog::DECIMAL;
				fOperationType.scale = r.scale;
				fOperationType.colWidth = 8;
				break;
			default:
				fOperationType.colDataType = execplan::erydbSystemCatalog::DOUBLE;			
				fOperationType.colWidth = 8;				
		}
	}
    // If both sides are unsigned, use UBIGINT as result type, otherwise
    // "promote" to BIGINT.
    else if (isUnsigned(l.colDataType) && isUnsigned(r.colDataType))
    {
        fOperationType.colDataType = execplan::erydbSystemCatalog::UBIGINT;
        fOperationType.colWidth = 8;
    }
    else if ((isSignedInteger(l.colDataType) && isUnsigned(r.colDataType)) ||
             (isUnsigned(l.colDataType) && isSignedInteger(r.colDataType)) ||
             (isSignedInteger(l.colDataType) && isSignedInteger(r.colDataType)))
    {
        fOperationType.colDataType = execplan::erydbSystemCatalog::BIGINT;
        fOperationType.colWidth = 8;
    }
	else if ((l.colDataType == execplan::erydbSystemCatalog::CHAR ||
		       l.colDataType == execplan::erydbSystemCatalog::VARCHAR) &&
		       (r.colDataType == execplan::erydbSystemCatalog::CHAR ||
		       r.colDataType == execplan::erydbSystemCatalog::VARCHAR))
	{
		if ( ( (l.colDataType == execplan::erydbSystemCatalog::CHAR && l.colWidth <= 8) ||
			  (l.colDataType == execplan::erydbSystemCatalog::VARCHAR && l.colWidth < 8) ) &&
			  ( (r.colDataType == execplan::erydbSystemCatalog::CHAR && r.colWidth <= 8) ||
			  (r.colDataType == execplan::erydbSystemCatalog::VARCHAR && r.colWidth < 8) ) )
		{
			if ( futf8 )
			{
				fOperationType.colDataType = execplan::erydbSystemCatalog::VARCHAR;
				fOperationType.colWidth = 255;
			}
			else
			{
				fOperationType.colDataType = execplan::erydbSystemCatalog::BIGINT;
				fOperationType.scale = 0;
				fOperationType.colWidth = 8;

				// @bug3532, char[] as network order int for fast comparison.
				l.colDataType = execplan::erydbSystemCatalog::STRINT;
				r.colDataType = execplan::erydbSystemCatalog::STRINT;
			}
		}
		else
		{
			fOperationType.colDataType = execplan::erydbSystemCatalog::VARCHAR;
			fOperationType.colWidth = 255;
		}
	}
	else
	{
		fOperationType.colDataType = execplan::erydbSystemCatalog::DOUBLE;	
		fOperationType.colWidth = 8;
	}
}

}  // namespace
