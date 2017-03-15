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

/******************************************************************************************
* $Id: erydberrorinfo.h 3626 2013-03-11 15:36:08Z xlou $
*
******************************************************************************************/
/**
 * @file
 */
#ifndef LOGGING_ERYDBERRORINFO_H
#define LOGGING_ERYDBERRORINFO_H

#include <string>
#include <map>

#include "messageobj.h"
#include "messagelog.h"

namespace logging {

/** @brief an ERYDB error info class
 *
 * Contains a error message map for looking up and constructing formatted message
 */

typedef std::map<unsigned, std::string> ErrorMap;

class ERYDBErrorInfo
{
public:
	static ERYDBErrorInfo* instance();
	std::string errorMsg(const unsigned eid, const Message::Args& args);
	std::string errorMsg(const unsigned eid);
	std::string errorMsg(const unsigned eid, int i);
	std::string errorMsg(const unsigned eid, const std::string& s);
	std::string logError(const logging::LOG_TYPE logLevel,
		                   const LoggingID logid,
		                   const unsigned eid,
		                   const Message::Args& args);
	~ERYDBErrorInfo();

private:
	static ERYDBErrorInfo* fInstance;
	ErrorMap fErrMap;
	ERYDBErrorInfo();
	void format(std::string& messageFormat, const Message::Args& args);
	std::string lookupError(const unsigned eid);
};

}//namespace logging

#endif
