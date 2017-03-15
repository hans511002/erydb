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

/*
 * EryDB FOSS License Exception
 * We want free and open source software applications under certain
 * licenses to be able to use the GPL-licensed EryDB erydbhdfs
 * libraries despite the fact that not all such FOSS licenses are
 * compatible with version 2 of the GNU General Public License.  
 * Therefore there are special exceptions to the terms and conditions 
 * of the GPLv2 as applied to erydbhdfs libraries, which are 
 * identified and described in more detail in the FOSS License 
 * Exception in the file utils/erydbhdfs/FOSS-EXCEPTION.txt
 */

#include "HdfsFsCache.h"

#include <boost/thread.hpp>
#include <iostream>

using namespace std;

namespace
{
	boost::mutex guard;
}

namespace erydbdatafile
{

hdfsFS HdfsFsCache::s_fs = 0;

hdfsFS HdfsFsCache::fs()
{
	boost::mutex::scoped_lock lock( guard );
	if( !s_fs )
	{
		s_fs = hdfsConnect("default", 0);
	}
	return s_fs;
}

}
