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

/*******************************************************************************
* $Id$
*
*******************************************************************************/


#ifndef WE_DDLCOMMON_H
#define WE_DDLCOMMON_H

#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <stdint.h>

#include <boost/any.hpp>
#include <boost/tuple/tuple.hpp>

#include "erydbsystemcatalog.h"
#include "objectidmanager.h"
#include "sessionmanager.h"
#include "ddlpkg.h"
#include "messageobj.h"
#include "we_type.h"
#include "we_define.h"
#include "writeengine.h"
#include "columnresult.h"
#include "brmtypes.h"
#include "joblist.h"

#if defined(_MSC_VER) && defined(xxxDDLPKGPROC_DLLEXPORT)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

using namespace std;
using namespace execplan;

#include <boost/algorithm/string/case_conv.hpp>
using namespace boost::algorithm;

template <class T>
bool from_string(T& t,
                 const std::string& s,
                 std::ios_base& (*f)(std::ios_base&))
{
    std::istringstream iss(s);
    return !(iss >> f >> t).fail();
}

namespace WriteEngine
{
	struct DDLColumn
    {
        execplan::erydbSystemCatalog::OID oid;
        execplan::erydbSystemCatalog::ColType colType;
        execplan:: erydbSystemCatalog::TableColName tableColName;
    };
	
	typedef std::vector<DDLColumn> ColumnList;
	
	struct DictOID
    {
        int dictOID;
        int listOID;
        int treeOID;
		int colWidth;
		int compressionType;
    };
	
	struct extentInfo
	{
		uint16_t dbRoot;
		uint32_t partition;
		uint16_t segment;
		bool operator==(const extentInfo& rhs) const { return (dbRoot == rhs.dbRoot && partition == rhs.partition && segment == rhs.segment); }
		bool operator!=(const extentInfo& rhs) const { return !(*this == rhs); }
	};
inline void  getColumnsForTable(uint32_t sessionID, std::string schema,std::string table,
		ColumnList& colList)
{

	erydbSystemCatalog::TableName tableName;
	tableName.schema = schema;
	tableName.table = table;
	std::string err;
	try
	{
		boost::shared_ptr<erydbSystemCatalog> systemCatalogPtr = erydbSystemCatalog::makeerydbSystemCatalog(sessionID);
		systemCatalogPtr->identity(erydbSystemCatalog::EC);

		const erydbSystemCatalog::RIDList ridList = systemCatalogPtr->columnRIDs(tableName);

		erydbSystemCatalog::RIDList::const_iterator rid_iterator = ridList.begin();
		while (rid_iterator != ridList.end())
		{
			erydbSystemCatalog::ROPair roPair = *rid_iterator;

			DDLColumn column;
			column.oid = roPair.objnum;
			column.colType = systemCatalogPtr->colType(column.oid);
			column.tableColName = systemCatalogPtr->colName(column.oid);

			colList.push_back(column);

			++rid_iterator;
		}

	}
	catch (exception& ex)
	{

		err = "DDLPackageProcessor::getColumnsForTable: while reading columns for table " +  schema + '.' + table + ": " + ex.what();
		throw std::runtime_error(err);
	}
	catch (...)
	{
		err = "DDLPackageProcessor::getColumnsForTable: caught unkown exception!" ;
		throw std::runtime_error(err);
	}

}

inline boost::any getNullValueForType(const execplan::erydbSystemCatalog::ColType& colType)
{
	boost::any value;
	switch(colType.colDataType)
	{
		case execplan::erydbSystemCatalog::BIT:
			break;

		case execplan::erydbSystemCatalog::TINYINT:
			{
				char tinyintvalue = joblist::TINYINTNULL;
				value = tinyintvalue;

			}
			break;

		case execplan::erydbSystemCatalog::UTINYINT:
			{
				uint8_t tinyintvalue = joblist::UTINYINTNULL;
				value = tinyintvalue;

			}
			break;

		case execplan::erydbSystemCatalog::SMALLINT:
			{
				short smallintvalue = joblist::SMALLINTNULL;
				value = smallintvalue;
			}
			break;

		case execplan::erydbSystemCatalog::USMALLINT:
			{
				uint16_t smallintvalue = joblist::USMALLINTNULL;
				value = smallintvalue;
			}
			break;

		case execplan::erydbSystemCatalog::MEDINT:
		case execplan::erydbSystemCatalog::INT:
			{
				int intvalue = joblist::INTNULL;
				value = intvalue;
			}
			break;

		case execplan::erydbSystemCatalog::UMEDINT:
		case execplan::erydbSystemCatalog::UINT:
			{
				uint32_t intvalue = joblist::UINTNULL;
				value = intvalue;
			}
			break;

		case execplan::erydbSystemCatalog::BIGINT:
			{
				long long bigint = joblist::BIGINTNULL;
				value = bigint;
			}
			break;

        case execplan::erydbSystemCatalog::UBIGINT:
            {
                uint64_t bigint = joblist::UBIGINTNULL;
                value = bigint;
            }
            break;

        case execplan::erydbSystemCatalog::DECIMAL:
		case execplan::erydbSystemCatalog::UDECIMAL:
			{
				if (colType.colWidth <= execplan::erydbSystemCatalog::FOUR_BYTE)
				{
					short smallintvalue = joblist::SMALLINTNULL;
					value = smallintvalue;
				}
				else if (colType.colWidth <= 9)
				{
					int intvalue = joblist::INTNULL;
					value = intvalue;
				}
				else if (colType.colWidth <= 18)
				{
					long long eightbyte = joblist::BIGINTNULL;
					value = eightbyte;
				}
				else
				{
					WriteEngine::Token nullToken;
					value = nullToken;
				}
			}
			break;
		case execplan::erydbSystemCatalog::FLOAT:
		case execplan::erydbSystemCatalog::UFLOAT:
			{
				uint32_t jlfloatnull = joblist::FLOATNULL;
				float* fp = reinterpret_cast<float*>(&jlfloatnull);
				value = *fp;
			}
			break;

		case execplan::erydbSystemCatalog::DOUBLE:
		case execplan::erydbSystemCatalog::UDOUBLE:
			{
				uint64_t jldoublenull = joblist::DOUBLENULL;
				double* dp = reinterpret_cast<double*>(&jldoublenull);
				value = *dp;
			}
			break;

		case execplan::erydbSystemCatalog::DATE:
			{
				int d = joblist::DATENULL;
				value = d;
			}
			break;

		case execplan::erydbSystemCatalog::DATETIME:
			{
				long long d = joblist::DATETIMENULL;
				value = d;
			}
			break;

		case execplan::erydbSystemCatalog::CHAR:
			{
				std::string charnull;
				if (colType.colWidth == execplan::erydbSystemCatalog::ONE_BYTE)
				{
					//charnull = joblist::CHAR1NULL;
					charnull = "\376";
					value = charnull;
				}
				else if (colType.colWidth == execplan::erydbSystemCatalog::TWO_BYTE)
				{
					//charnull = joblist::CHAR2NULL;
					charnull = "\377\376";
					value = charnull;
				}
				else if (colType.colWidth <= execplan::erydbSystemCatalog::FOUR_BYTE)
				{
					//charnull = joblist::CHAR4NULL;
					charnull = "\377\377\377\376";
					value = charnull;
				}
				else
				{
					WriteEngine::Token nullToken;
					value = nullToken;
				}

			}
			break;
		case execplan::erydbSystemCatalog::VARCHAR:
			{
				std::string charnull;
				if (colType.colWidth == execplan::erydbSystemCatalog::ONE_BYTE)
				{
					//charnull = joblist::CHAR2NULL;
					charnull = "\377\376";
					value = charnull;
				}
				else if (colType.colWidth < execplan::erydbSystemCatalog::FOUR_BYTE)
				{
					//charnull = joblist::CHAR4NULL;
					charnull = "\377\377\377\376";
					value = charnull;
				}
				else
				{
					WriteEngine::Token nullToken;
					value = nullToken;
				}

			}
			break;
		case execplan::erydbSystemCatalog::VARBINARY:
			{
				std::string charnull;
				if (colType.colWidth == execplan::erydbSystemCatalog::ONE_BYTE)
				{
					//charnull = joblist::CHAR2NULL;
					charnull = "\377\376";
					value = charnull;
				}
				else if (colType.colWidth < execplan::erydbSystemCatalog::FOUR_BYTE)
				{
					//charnull = joblist::CHAR4NULL;
					charnull = "\377\377\377\376";
					value = charnull;
				}
				else
				{
					WriteEngine::Token nullToken;
					value = nullToken;
				}

			}
			break;


		default:
			throw std::runtime_error("getNullValueForType: unkown column data type");
			break;

	}

	return value;
}

inline int convertDataType(int dataType)
{
	int erydbDataType;

	switch (dataType)
	{
		case ddlpackage::DDL_CHAR:
			erydbDataType = erydbSystemCatalog::CHAR;
			break;

		case ddlpackage::DDL_VARCHAR:
			erydbDataType = erydbSystemCatalog::VARCHAR;
			break;

		case ddlpackage::DDL_VARBINARY:
			erydbDataType = erydbSystemCatalog::VARBINARY;
			break;

		case ddlpackage::DDL_BIT:
			erydbDataType = erydbSystemCatalog::BIT;
			break;

		case ddlpackage::DDL_REAL:
		case ddlpackage::DDL_DECIMAL:
		case ddlpackage::DDL_NUMERIC:
		case ddlpackage::DDL_NUMBER:
			erydbDataType = erydbSystemCatalog::DECIMAL;
			break;

		case ddlpackage::DDL_FLOAT:
			erydbDataType = erydbSystemCatalog::FLOAT;
			break;

		case ddlpackage::DDL_DOUBLE:
			erydbDataType = erydbSystemCatalog::DOUBLE;
			break;

		case ddlpackage::DDL_INT:
		case ddlpackage::DDL_INTEGER:
			erydbDataType = erydbSystemCatalog::INT;
			break;

		case ddlpackage::DDL_BIGINT:
			erydbDataType = erydbSystemCatalog::BIGINT;
			break;

		case ddlpackage::DDL_MEDINT:
			erydbDataType = erydbSystemCatalog::MEDINT;
			break;

		case ddlpackage::DDL_SMALLINT:
			erydbDataType = erydbSystemCatalog::SMALLINT;
			break;

		case ddlpackage::DDL_TINYINT:
			erydbDataType = erydbSystemCatalog::TINYINT;
			break;

		case ddlpackage::DDL_DATE:
			erydbDataType = erydbSystemCatalog::DATE;
			break;

		case ddlpackage::DDL_DATETIME:
			erydbDataType = erydbSystemCatalog::DATETIME;
			break;

		case ddlpackage::DDL_CLOB:
			erydbDataType = erydbSystemCatalog::CLOB;
			break;

		case ddlpackage::DDL_BLOB:
			erydbDataType = erydbSystemCatalog::BLOB;
			break;

        case ddlpackage::DDL_UNSIGNED_TINYINT:
            erydbDataType = erydbSystemCatalog::UTINYINT;
            break;

        case ddlpackage::DDL_UNSIGNED_SMALLINT:
            erydbDataType = erydbSystemCatalog::USMALLINT;
            break;

        case ddlpackage::DDL_UNSIGNED_INT:
            erydbDataType = erydbSystemCatalog::UINT;
            break;

        case ddlpackage::DDL_UNSIGNED_BIGINT:
            erydbDataType = erydbSystemCatalog::UBIGINT;
            break;

        case ddlpackage::DDL_UNSIGNED_DECIMAL:
        case ddlpackage::DDL_UNSIGNED_NUMERIC:
            erydbDataType = erydbSystemCatalog::UDECIMAL;
            break;

        case ddlpackage::DDL_UNSIGNED_FLOAT:
            erydbDataType = erydbSystemCatalog::UFLOAT;
            break;

        case ddlpackage::DDL_UNSIGNED_DOUBLE:
            erydbDataType = erydbSystemCatalog::UDOUBLE;
            break;

        default:
			throw runtime_error("Unsupported datatype!");

	}

	return erydbDataType;
}

inline void findColumnData(uint32_t sessionID, execplan::erydbSystemCatalog::TableName& systableName,
		const std::string& colName, DDLColumn& sysCol)
{
	ColumnList columns;
	ColumnList::const_iterator column_iterator;
	std::string err;
	try
	{
		getColumnsForTable(sessionID, systableName.schema,systableName.table, columns);
		column_iterator = columns.begin();
		while (column_iterator != columns.end())
		{
			sysCol = *column_iterator;
			boost::to_lower(sysCol.tableColName.column);

			if (colName == sysCol.tableColName.column)
			{
				break;
			}
			++column_iterator;
		}
	}
	catch (exception& ex)
	{
		err = ex.what();
		throw std::runtime_error(err);
	}
	catch (...)
	{
		err = "findColumnData:Unknown exception caught";
		throw std::runtime_error(err);
	}
}

inline void convertRidToColumn(uint64_t& rid, unsigned& dbRoot, unsigned& partition,
				unsigned& segment, unsigned filesPerColumnPartition,
				unsigned  extentsPerSegmentFile, unsigned extentRows,
				unsigned startDBRoot, unsigned dbrootCnt)
{
	partition = rid / (filesPerColumnPartition * extentsPerSegmentFile * extentRows);

	segment = (((rid % (filesPerColumnPartition * extentsPerSegmentFile * extentRows)) / extentRows)) % filesPerColumnPartition;

	dbRoot = ((startDBRoot - 1 + segment) % dbrootCnt) + 1;

	//Calculate the relative rid for this segment file
	uint64_t relRidInPartition = rid - ((uint64_t)partition * (uint64_t)filesPerColumnPartition * (uint64_t)extentsPerSegmentFile * (uint64_t)extentRows);
	erydbassert(relRidInPartition <= (uint64_t)filesPerColumnPartition * (uint64_t)extentsPerSegmentFile * (uint64_t)extentRows);
	uint32_t numExtentsInThisPart = relRidInPartition / extentRows;
	unsigned numExtentsInThisSegPart = numExtentsInThisPart / filesPerColumnPartition;
	uint64_t relRidInThisExtent = relRidInPartition - numExtentsInThisPart * extentRows;
	rid = relRidInThisExtent +  numExtentsInThisSegPart * extentRows;
}

}
#undef EXPORT
#endif

