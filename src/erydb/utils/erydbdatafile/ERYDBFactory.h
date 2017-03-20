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

#ifndef ERYDBFACTORY_H_
#define ERYDBFACTORY_H_

#include <string>
#include <map>
#include <stdexcept>

#include "ERYDBDataFile.h"

namespace erydbdatafile
{

class FileFactoryBase;
class ERYDBFileSystem;

struct FileFactoryEnt
{
	FileFactoryEnt() :
		type(ERYDBDataFile::UNKNOWN),
		name("unknown"),
		factory(0),
		filesystem(0) {;}

	FileFactoryEnt(
			ERYDBDataFile::Types t,
			const std::string& n,
			FileFactoryBase* f,
			ERYDBFileSystem* fs) :
		type(t),
		name(n),
		factory(f),
		filesystem(fs) {;}

	ERYDBDataFile::Types     type;
	std::string	           name;
	FileFactoryBase*       factory;
	ERYDBFileSystem*         filesystem;
};

typedef FileFactoryEnt (*FileFactoryEntryFunc)();

/**
 * ERYDBFactory manages the factory plugins that know how to create
 * files of different types.  The plugin architecture allows ERYDB
 * to defer dependencies until plugin load.  This class is a static
 * class and is threadsafe.
 *
 */
class ERYDBFactory
{
public:
	/**
	 * This method installs the default plugs for Buffered and Unbuffered files.
	 * It is called automatically from the ERYDBPolicy::init() body so that clients
	 * don't have to worry about it.
	 */
	static bool installDefaultPlugins();

	/**
	 * This method installs a dynamic plugin.  The plugin argument must refer
	 * to a ".so" file that exposes an extern "C" functions:
	 *     FileFactoryEnt   plugin_instance()
	 */
	static bool installPlugin(const std::string& plugin);

	/**
	 * This method calls the Factory for the specified type
	 */
	static ERYDBDataFile* open(ERYDBDataFile::Types type, const char* fname, const char* mode, unsigned opts, unsigned colWidth);

	/**
	 * This retrieves the ERYDBFileSystem for the specified type
	 */
	static ERYDBFileSystem& getFs(ERYDBDataFile::Types type);

	/**
	 * This retrieves the ERYDBFileSystem for the specified type
	 */
	static const std::string& name(ERYDBDataFile::Types type);

private:
	typedef std::map<ERYDBDataFile::Types,FileFactoryEnt> FactoryMap;
	typedef FactoryMap::const_iterator FactoryMapCIter;

	static FactoryMap s_plugins;

	ERYDBFactory();
	virtual ~ERYDBFactory();
};

inline
const std::string& ERYDBFactory::name(ERYDBDataFile::Types type)
{
	if( s_plugins.find(type) == s_plugins.end() )
	{
    	throw std::runtime_error("unknown plugin type in ERYDBFactory::name");
	}

	return s_plugins[type].name;
}

}

#endif /* ERYDBFACTORY_H_ */
