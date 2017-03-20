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

#include "ERYDBDataFile.h"

#include <stdexcept>
#include <sys/types.h>
#include <sstream>
#include <iostream>

#include "UnbufferedFile.h"
#include "BufferedFile.h"
#include "ERYDBLogger.h"
#include "ERYDBFactory.h"

using namespace std;

namespace erydbdatafile
{

ERYDBDataFile* ERYDBDataFile::open(Types type, const char* fname, const char* mode, unsigned opts, unsigned colWidth)
{
	ERYDBDataFile* ret = 0;

	try
	{
		ret = ERYDBFactory::open(type, fname, mode, opts, colWidth);
	}
	catch (std::exception& e)
	{
    	std::ostringstream oss;
		oss << "Failed to open file: " << fname << ", exception: " << e.what();
	    	ERYDBLogger::syslog(oss.str(), logging::LOG_TYPE_DEBUG);
		if( ERYDBLogger::isEnabled() )
			ERYDBLogger::logNoArg( fname, 0, e.what(), 0 );
	}

	if( ERYDBLogger::isEnabled() )
		ERYDBLogger::logOpen( type, fname, mode, opts, ret );
	return ret;
}

}
