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
*   $Id: ha_view.h 9210 2013-01-21 14:10:42Z rdempsey $
*
*
***********************************************************************/
/** @file */
/** class View interface */

#ifndef HA_VIEW
#define HA_VIEW

#include "erydb_mysql.h"
//#undef LOG_INFO
#include "ha_erydb_impl_if.h"

namespace execplan
{
	class erydbSystemCatalog;
}

namespace cal_impl_if
{

class View
{
public:
	View(SELECT_LEX& select, gp_walk_info* parentGwip) :
		fSelect(select),
		fParentGwip(parentGwip) {}
	~View() {}

	execplan::erydbSystemCatalog::TableAliasName& viewName();
	void viewName(execplan::erydbSystemCatalog::TableAliasName& viewName);

	/** get execution plan for this view. merge the table list and join list to the
	    parent select.
	 */
	void transform();
	uint32_t processOuterJoin(gp_walk_info& gwi);

private:
	SELECT_LEX fSelect;
	gp_walk_info* fParentGwip;
	execplan::erydbSystemCatalog::TableAliasName fViewName;
};

}

#endif
