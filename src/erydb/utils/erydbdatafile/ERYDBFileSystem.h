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

#ifndef ERYDBFILESYSTEM_H_
#define ERYDBFILESYSTEM_H_

#include <sys/types.h>
#include <list>
#include "ERYDBDataFile.h"
#include "ERYDBFactory.h"

namespace erydbdatafile
{

/**
 * ERYDBFileSystem is a combination abstract base class and factory. The
 * purpose is to encapsulate access to various file system functions
 * across different file system types including hdfs.
 */
class ERYDBFileSystem
{
public:
	/**
	 * The TYPE enum defines the supported underlying filesystem types
	 */
	enum Types
	{
		UNKNOWN = 0x00,
		POSIX = 0x0001,
		HDFS  = 0x0002
	};

	/**
	 * Destructor
	 */
	virtual ~ERYDBFileSystem();

	/**
	 * getFs() returns a reference to the ERYDBFileSystem instance for the
	 * specified type
	 */
	static ERYDBFileSystem& getFs(ERYDBDataFile::Types type);

	/**
	 * mkdir() creates a directory specified by pathname including any
	 * parent directories if needed.
	 * Returns 0 on success, -1 on error
	 */
	virtual int mkdir(const char *pathname) = 0;

	/**
	 * remove() removes a path from the filesystem.  It will handle
	 * both files and directories (including non-empty directories).  Note
	 * that a call to remove of a path that does not exist will return as
	 * success.
	 *
	 * Returns 0 on success, -1 on error
	 */
	virtual int remove(const char *pathname) = 0;

	/**
	 * rename() names a file, moving it between directories if required.
	 * Returns 0 on success, -1 on error
	 */
	virtual int rename(const char *oldpath, const char *newpath) = 0;

	/**
	 * size() returns the size of the file specified by path.
	 * Returns the size on success, -1 on error
	 */
	virtual off64_t size(const char* path) const = 0;

    /**
     * compressedSize() returns the decompressed size of the file
     * speicified by path.
     * Returns the size on success, -1 on error
     */
    virtual off64_t compressedSize(const char* path) const = 0;

	/**
	 * exists() checks for the existence of a particular path.
	 * Returns true if exists, false otherwise.
	 */
	virtual bool exists(const char* pathname) const = 0;

	/**
	 * listDirectory() returns the contents of the directory as a
	 * list of strings.  For now, no indication of whether each
	 * item is a file or directory - both files and subdirectories
	 * will be returned.
	 * Returns 0 on success.  -1 on error (incl if directory does
	 * not exist.
	 */

	virtual int listDirectory(const char* pathname, std::list<std::string>& contents) const = 0;

	/**
	 * isDir() returns whether or not the path is a directory
	 */
	virtual bool isDir(const char* pathname) const = 0;

	/**
	 * copyfile() copies the source file to the destination file
	 * Returns 0 on success.  -1 on error.
	 */
	virtual int copyFile(const char* srcPath, const char* destPath) const = 0;

	/**
	 * isFsUp() checks if the filesystem is up
	 * Returns 0 on success.  -1 on error.
	 */
	virtual bool filesystemIsUp() const { return true; }

protected:
	ERYDBFileSystem( Types type );

private:
	Types m_type;
};

/**
 * getFs() returns a reference to the ERYDBFileSystem instance for the
 * specified type
 */
inline
ERYDBFileSystem& ERYDBFileSystem::getFs(ERYDBDataFile::Types type)
{
	return ERYDBFactory::getFs(type);
}

}

#endif /* ERYDBFILESYSTEM_H_ */
