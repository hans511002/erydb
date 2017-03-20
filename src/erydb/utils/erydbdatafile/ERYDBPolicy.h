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

#ifndef ERYDBPOLICY_H_
#define ERYDBPOLICY_H_

#include <string>
#include <stdint.h>

#include <boost/thread/mutex.hpp>

#include "ERYDBDataFile.h"
#include "ERYDBFileSystem.h"
#include "ERYDBFactory.h"

namespace erydbdatafile
{

/**
 * ERYDBPolicy is a static class that is used to manage the interaction
 * between the rest of erydb and the erydbdatafile subsystem.  It supports
 * mapping from a file/directory path and context (currently PrimProc or
 * WriteEngineServer) to a file and filesystem type
 */
class ERYDBPolicy
{
public:
	/**
	 * Define the contexts recognized by ERYDBPolicy.  The same file may be
	 * opened as a different type depending on the context (for ex. data
	 * files are buffered in WriteEngine and Unbuffered in PrimProc).
	 */
	enum Contexts {
		PRIMPROC,
		WRITEENG
	};

	/**
	 * Config the ERYDBPolicy based on the erydb.xml
	 */
	static void configERYDBPolicy();


	/**
	 * Initialize the ERYDBDataFile subsystem.  This should be called once
	 * by the main thread of the application prior to any other use of the
     * library. 
     * bEnableLogging -- for debug only. 
     * bUseRdwrMemBuffer -- If true, use Memory Buffered files (class HdfsRdwrMemBuffer) until hdfsRdwrBufferMaxSize 
     *                    memory is used, then switch to file buffering until mem used is below hdfsRdwrBufferMaxSize.
     * hdfsRdwrScratch -- where to store file-buffered HDFS files (class HdfsRdwrFileBuffer) - it should name
	 *  				  a writable directory with sufficient space to store all needed buffers (size-TBD?).
	 * hdfsRdwrBufferMaxSize -- When RdwrMemBuffers get this big, switch to file buffers .
	 */
	static void init( bool bEnableLogging, bool bUseRdwrMemBuffer, const std::string& hdfsRdwrScratch, int64_t hdfsRdwrBufferMaxSize );

	/**
	 * Load a new filetype plugin.  Return value indicates success(true)
	 * or failure (false)
	 */
	static bool installPlugin(const std::string& plugin);

	/**
	 * Accessor method that returns whether or not HDFS is enabled
	 */
	static bool useHdfs();

	/**
	 * Accessor method that returns whether to use HDFS memory buffers
	 */
	static bool useRdwrMemBuffer();

    /**
     * Accessor method that returns the max amount of mem buff to use before switching to file buffering
     */
    static size_t hdfsRdwrBufferMaxSize();

    /**
     * Accessor method that returns the directory to place our temp hdfs buffer files
     */
    static const std::string& hdfsRdwrScratch();

    /**
	 * getType() returns the proper ERYDBDataFile::Types for a file given a
	 * path for the path and a context in which it will be interacted with.
	 */
	static ERYDBDataFile::Types getType( const std::string& path, Contexts ctxt );

	/**
	 * getFs() returns a reference to the proper ERYDBFileSystem instance that
	 * is able to interact with the file/directory specified by path
	 */
	static ERYDBFileSystem& getFs( const std::string& path );

	/**
	 * These are convenience functions that simplify the syntax required to
	 * make a filesystem call.  Each of the calls determines the proper
	 * FileSystem to reference for the specified path and then performs the
	 * actual call.  Documentation for these will not be duplicated here -
	 * please see ERYDBFileSystem.h.
	 */
	static int mkdir(const char *pathname);
	static off64_t size(const char* path);
    static off64_t compressedSize(const char* path);
	static int remove(const char *pathname);
	static int rename(const char *oldpath, const char *newpath);
	static bool exists(const char* pathname);
	static int listDirectory(const char* pathname, std::list<std::string>& contents);
	static bool isDir(const char* pathname);
	static int copyFile(const char* srcPath, const char* destPath);

private:
	/**
	 * don't allow this class to be constructed.  It exposes a purely
	 * static interface
	 */
	ERYDBPolicy();

	static bool isLocalFile( const std::string& path );

	static bool s_usehdfs;
    static bool s_bUseRdwrMemBuffer;
	static std::string s_hdfsRdwrScratch;
    static int64_t s_hdfsRdwrBufferMaxSize; 
    static bool s_configed;
    static boost::mutex s_mutex;
};

inline
const std::string& ERYDBPolicy::hdfsRdwrScratch()
{
	return s_hdfsRdwrScratch;
}

inline
bool ERYDBPolicy::useHdfs()
{
	return s_usehdfs;
}

inline
bool ERYDBPolicy::useRdwrMemBuffer()
{
	return s_bUseRdwrMemBuffer;
}

inline
size_t ERYDBPolicy::hdfsRdwrBufferMaxSize()
{
	return s_hdfsRdwrBufferMaxSize;
}

inline
int ERYDBPolicy::mkdir(const char *pathname)
{
	return ERYDBPolicy::getFs( pathname ).mkdir( pathname );
}

inline
off64_t ERYDBPolicy::size(const char* path)
{
	return ERYDBPolicy::getFs( path ).size( path );
}

inline
off64_t ERYDBPolicy::compressedSize(const char* path)
{
    return ERYDBPolicy::getFs( path ).compressedSize( path );
}

inline
int ERYDBPolicy::remove(const char *pathname)
{
	return ERYDBPolicy::getFs( pathname ).remove( pathname );
}

inline
int ERYDBPolicy::rename(const char *oldpath, const char *newpath)
{
	return ERYDBPolicy::getFs( oldpath ).rename( oldpath, newpath );
}

inline
bool ERYDBPolicy::exists(const char *pathname)
{
	return ERYDBPolicy::getFs( pathname ).exists( pathname );
}

inline
int ERYDBPolicy::listDirectory(const char* pathname, std::list<std::string>& contents)
{
	return ERYDBPolicy::getFs( pathname ).listDirectory( pathname, contents );
}

inline
bool ERYDBPolicy::isDir(const char *pathname)
{
	return ERYDBPolicy::getFs( pathname ).isDir( pathname );
}

inline
int ERYDBPolicy::copyFile(const char* srcPath, const char* destPath)
{
	return ERYDBPolicy::getFs( srcPath ).copyFile( srcPath, destPath );
}

}

#endif /* ERYDBPOLICY_H_ */
