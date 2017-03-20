/* Copyright (C) 2014 EryDB, Inc.
   Copyright (C) 2016 MariaDB Corporaton

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

#ifndef SNMPGLOBAL_H
#define SNMPGLOBAL_H

#ifdef __linux__
#include <sys/file.h>
#include <linux/unistd.h>
#endif
#include <string>
#include <stdint.h>

#ifndef SKIP_SNMP
#include "net-snmp/net-snmp-config.h"
#include "net-snmp/net-snmp-includes.h"
#include "net-snmp/agent/net-snmp-agent-includes.h"
#else
typedef uint64_t oid;
#endif

namespace snmpmanager {

/** @brief oid type
 *1, 3, 6, 1, 4, 1, 2021, 991 
 */
typedef oid ERYDB_OID;

/** @brief constant define
 *
 */
const int SET = 1;
const int CLEAR = 0;

const std::string ACTIVE_ALARM_FILE = "/var/log/erydb/activeAlarms";
const std::string ALARM_FILE = "/var/log/erydb/alarm.log";
const std::string ALARM_ARCHIVE_FILE = "/var/log/erydb/archive";

const ERYDB_OID SNMPTRAP_OID [] = { 1, 3, 6, 1, 6, 3, 1, 1, 4, 1, 0 };
const ERYDB_OID ERYDB_TRAP_OID [] = { 1, 3, 6, 1, 4, 1, 2021, 991 };
const ERYDB_OID CALALARM_DATA_OID [] =  { 1, 3, 6, 1, 4, 1, 2021, 991, 17 };
const ERYDB_OID COMPONENT_ID_OID [] = { 1, 3, 6, 1, 4, 1, 2021, 991, 18 };
const ERYDB_OID ALARM_ID_OID [] = { 1, 3, 6, 1, 4, 1, 2021, 991, 19 };
const ERYDB_OID STATE_OID [] = { 1, 3, 6, 1, 4, 1, 2021, 991, 20 };
const ERYDB_OID SNAME_OID [] = { 1, 3, 6, 1, 4, 1, 2021, 991, 21 };
const ERYDB_OID PNAME_OID [] = { 1, 3, 6, 1, 4, 1, 2021, 991, 22 };
const ERYDB_OID PID_OID [] = { 1, 3, 6, 1, 4, 1, 2021, 991, 23 };
const ERYDB_OID TID_OID [] = { 1, 3, 6, 1, 4, 1, 2021, 991, 24 };
const bool ERYDB_SNMP_DEBUG = false;
const uint16_t INVALID_ALARM_ID = 0;
}

#endif
