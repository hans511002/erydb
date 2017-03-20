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
 *   $Id: erydbdmlpackage.cpp 9210 2013-01-21 14:10:42Z rdempsey $
 *
 *
 ***********************************************************************/

#include "erydbdmlpackage.h"
using namespace std;

namespace dmlpackage
{
    /**
     * Constructors/Destructors
     */

    erydbDMLPackage::erydbDMLPackage()
        :fPlan(new messageqcpp::ByteStream()), fTable(0), fHasFilter(0), fLogging(true), fIsInsertSelect(false), fIsBatchInsert(false), fIsAutocommitOn(false), fTableOid(0)
    {

    }

    erydbDMLPackage::erydbDMLPackage( std::string schemaName, std::string tableName,
        std::string dmlStatement, int sessionID )
        :fSchemaName(schemaName), fTableName( tableName ), fDMLStatement( dmlStatement ),
        fSessionID(sessionID), fPlan(new messageqcpp::ByteStream()), fTable(0), fHasFilter(false), fLogging(true), fIsInsertSelect(false), 
		fIsBatchInsert(false), fIsAutocommitOn(false), fIsWarnToError(false), fTableOid(0)
    {

    }

    erydbDMLPackage::~erydbDMLPackage()
    {
        if ( 0 != fTable )
            delete fTable;
    }

    /*
     * strip off whitespaces from a string
     */
    std::string erydbDMLPackage::StripLeadingWhitespace( std::string value )
    {
        for(;;)
        {
            string::size_type pos = value.find (' ',0);
            if (pos == 0)
            {
                value = value.substr (pos+1,10000);
            }
            else
            {                                     // no more whitespace
                break;
            }
        }
        return value;
    }

    void erydbDMLPackage::initializeTable()
    {
        if (0 == fTable)
        {
            fTable = new DMLTable();
            fTable->set_SchemaName(fSchemaName);
            fTable->set_TableName(fTableName);
        }
    }

}                                                 // namespace dmlpackage
