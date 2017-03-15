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

#include "ERYDBFactory.h"

#include <boost/thread.hpp>
#include <sstream>
#ifndef _MSC_VER
#include <dlfcn.h>
#endif
#include <string.h>
#include <errno.h>
#include <iostream>

#include "FileFactoryBase.h"
#include "BufferedFileFactory.h"
#include "UnbufferedFileFactory.h"
#include "PosixFileSystem.h"
#include "ERYDBLogger.h"

using namespace std;
namespace
{
	boost::mutex fac_guard;
}

namespace erydbdatafile
{

ERYDBFactory::FactoryMap ERYDBFactory::s_plugins;

bool ERYDBFactory::installDefaultPlugins()
{
	// protect these methods since we are changing our static data structure
	boost::mutex::scoped_lock lock( fac_guard );

	s_plugins[ERYDBDataFile::BUFFERED] = FileFactoryEnt(ERYDBDataFile::BUFFERED, "buffered", new BufferedFileFactory(), new PosixFileSystem());
	s_plugins[ERYDBDataFile::UNBUFFERED] = FileFactoryEnt(ERYDBDataFile::UNBUFFERED, "unbuffered", new UnbufferedFileFactory(), new PosixFileSystem());

	return false;
}

bool ERYDBFactory::installPlugin(const std::string& plugin)
{
#ifdef _MSC_VER
	ostringstream oss;
    oss << "EryDB for Windows does not support plugins: plugin = " << plugin;
	throw std::runtime_error(oss.str());
#else
	// protect these methods since we are changing our static data structure
	boost::mutex::scoped_lock lock( fac_guard );

	void* handle = dlopen(plugin.c_str(), RTLD_LAZY);
	if( handle == NULL )
	{
    	std::ostringstream oss;
    	oss << "ERYDBFactory::installPlugin: dlopen for " << plugin << " failed: " << dlerror();
    	ERYDBLogger::syslog(oss.str(), logging::LOG_TYPE_ERROR);
		return false;
	}

	void* functor = dlsym(handle, "plugin_instance");
	if( functor == NULL )
	{
        std::ostringstream oss;
        oss << "ERYDBFactory::installPlugin: dlsym for plugin_instance() failed. plugin " << plugin << dlerror();
        ERYDBLogger::syslog(oss.str(), logging::LOG_TYPE_ERROR);
		return false;
	}
	FileFactoryEnt ent = (*(FileFactoryEntryFunc)functor)();
	s_plugins[ent.type] = ent;

    std::ostringstream oss;
    oss << "ERYDBFactory::installPlugin: installed filesystem plugin " << plugin;
    ERYDBLogger::syslog(oss.str(), logging::LOG_TYPE_DEBUG);
	return true;
#endif
}

ERYDBDataFile* ERYDBFactory::open(ERYDBDataFile::Types type, const char* fname, const char* mode, unsigned opts, unsigned colWidth)
{
	if( s_plugins.find(type) == s_plugins.end() )
	{
		ostringstream oss;
		oss << "Cannot find factory plugin type " << (int) type << " to open file: " << fname;
    	throw std::runtime_error(oss.str());
	}

	return s_plugins[type].factory->open(fname, mode, opts, colWidth);
}

ERYDBFileSystem& ERYDBFactory::getFs(ERYDBDataFile::Types type)
{
	if( s_plugins.find(type) == s_plugins.end() )
	{
		ostringstream oss;
		oss << "Cannot find filesystem for plugin type " << (int) type;
    	throw std::runtime_error(oss.str());
	}

	return *(s_plugins[type].filesystem);
}

}
