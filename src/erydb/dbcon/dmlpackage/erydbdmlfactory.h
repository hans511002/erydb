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
 *   $Id: erydbdmlfactory.h 9210 2013-01-21 14:10:42Z rdempsey $
 *
 *
 ***********************************************************************/
/** @file */
#ifndef ERYDBDMLFACTORY_H
#define ERYDBDMLFACTORY_H
#include <string>
#include "dmlpackage.h"
#include "erydbdmlpackage.h"
#include "vendordmlstatement.h"
#include <boost/thread.hpp>

#if defined(_MSC_VER) && defined(xxxERYDBDMLFACTORY_DLLEXPORT)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif
namespace dmlpackage
{

class erydbDMLFactory
{
    /** @brief a concrete implementation responsible for creating
     * the proper concrete realization of a erydbDMLPackage
     * given a VendorDMLStatement.
     */
public:

    /** @brief factory method
     *
     * @param vpackage the VendorDMLStatement
     * @param defaultSchema the default schema to be used for DML statements
     */
    EXPORT static dmlpackage::erydbDMLPackage* makeerydbDMLPackage (dmlpackage::VendorDMLStatement& vpackage,
            std::string defaultSchema = "" );

    /** @brief old factory method!
     *
     * @param vpackage the VendorDMLStatement
     */
    EXPORT static dmlpackage::erydbDMLPackage* makeerydbDMLPackageFromBuffer(dmlpackage::VendorDMLStatement& vpackage);
	
	EXPORT static dmlpackage::erydbDMLPackage* makeerydbDMLPackageFromMysqlBuffer(dmlpackage::VendorDMLStatement& vpackage);
	static dmlpackage::erydbDMLPackage* makeerydbUpdatePackageFromMysqlBuffer(dmlpackage::VendorDMLStatement& vpackage, dmlpackage::UpdateSqlStatement& updateStmt);

protected:

private:
	static boost::mutex fParserLock;
};

}

#undef EXPORT

#endif                                            //ERYDBDMLFACTORY_H
