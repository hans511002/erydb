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

#ifndef FILEFACTORYBASE_H_
#define FILEFACTORYBASE_H_

namespace erydbdatafile
{

class ERYDBDataFile;

class FileFactoryBase
{
public:
	virtual ~FileFactoryBase() {;}
	virtual ERYDBDataFile* open(const char* fname, const char* mode, unsigned opts, unsigned colWidth) = 0;
};

}
#endif /* FILEFACTORYBASE_H_ */
