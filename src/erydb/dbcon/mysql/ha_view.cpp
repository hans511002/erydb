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

/***********************************************************************
*   $Id: ha_view.cpp 9642 2013-06-24 14:57:42Z rdempsey $
*
*
***********************************************************************/
 
#include "erydb_mysql.h"

#include <string>
using namespace std;

#include <boost/algorithm/string/case_conv.hpp>
using namespace boost;

#include "errorids.h"
using namespace logging;

#include "parsetree.h"
#include "simplefilter.h"
#include "erydbsystemcatalog.h"
using namespace execplan;

#include "ha_subquery.h"
#include "ha_view.h"

namespace cal_impl_if
{
extern uint32_t buildOuterJoin(gp_walk_info& gwi, SELECT_LEX& select_lex);
extern string getViewName(TABLE_LIST* table_ptr);

erydbSystemCatalog::TableAliasName& View::viewName()
{
	return fViewName;
}

void View::viewName(execplan::erydbSystemCatalog::TableAliasName& viewName)
{
	fViewName = viewName;
}

void View::transform()
{
	erydbSelectExecutionPlan* csep = new erydbSelectExecutionPlan();
	csep->sessionID(fParentGwip->sessionid);

	// gwi for the sub query
	gp_walk_info gwi;
	gwi.thd = fParentGwip->thd;

	uint32_t sessionID = csep->sessionID();
	gwi.sessionid = sessionID;
	boost::shared_ptr<erydbSystemCatalog> csc = erydbSystemCatalog::makeerydbSystemCatalog(sessionID);
	csc->identity(erydbSystemCatalog::FE);
	gwi.csc = csc;

	// traverse the table list of the view
	TABLE_LIST* table_ptr = fSelect.get_table_list();
	erydbSelectExecutionPlan::SelectList derivedTbList;

	// @bug 1796. Remember table order on the FROM list.
	gwi.clauseType = FROM;
	try {
		for (; table_ptr; table_ptr= table_ptr->next_local)
		{
			// mysql put vtable here for from sub. we ignore it
			if (string(table_ptr->table_name).find("$vtable") != string::npos)
				continue;

			string viewName = getViewName(table_ptr);

			if (table_ptr->derived)
			{
				SELECT_LEX *select_cursor = table_ptr->derived->first_select();
				FromSubQuery *fromSub = new FromSubQuery(gwi, select_cursor);
				string alias(table_ptr->alias);
				gwi.viewName = make_aliasview("", alias, table_ptr->belong_to_view->alias, "");
				algorithm::to_lower(alias);
				fromSub->alias(alias);
				gwi.derivedTbList.push_back(SCSEP(fromSub->transform()));
				// set alias to both table name and alias name of the derived table
				erydbSystemCatalog::TableAliasName tn = make_aliasview("", "", alias, viewName);
				gwi.tbList.push_back(tn);
				gwi.tableMap[tn] = make_pair(0, table_ptr);
				gwi.thd->erydb_vtable.isUnion = true; //by-pass the 2nd pass of rnd_init
			}
			else if (table_ptr->view)
			{
				// for nested view, the view name is vout.vin... format
				erydbSystemCatalog::TableAliasName tn = make_aliasview(table_ptr->db, table_ptr->table_name, table_ptr->alias, viewName);
				gwi.viewName = make_aliastable(table_ptr->db, table_ptr->table_name, viewName);
				View *view = new View(table_ptr->view->select_lex, &gwi);
				view->viewName(gwi.viewName);
				gwi.viewList.push_back(view);
				view->transform();
			}
			else
			{
				// check foreign engine tables
				bool infiniDB = (table_ptr->table ? isEryDB(table_ptr->table) : true);

				// trigger system catalog cache
				if (infiniDB)
					csc->columnRIDs(make_table(table_ptr->db, table_ptr->table_name), true);

				erydbSystemCatalog::TableAliasName tn = make_aliasview(table_ptr->db, table_ptr->table_name, table_ptr->alias, viewName, infiniDB);
				gwi.tbList.push_back(tn);
				gwi.tableMap[tn] = make_pair(0, table_ptr);
				fParentGwip->tableMap[tn] = make_pair(0, table_ptr);
			}
		}
		if (gwi.fatalParseError)
		{
			setError(gwi.thd, ER_INTERNAL_ERROR, gwi.parseErrorText);
			return;
		}
	}
	catch (ERYDBExcept& ie)
	{
		setError(gwi.thd, ER_INTERNAL_ERROR, ie.what());
		erydbSystemCatalog::removeerydbSystemCatalog(sessionID);
		return;
	}
	catch (...)
	{
		string emsg = ERYDBErrorInfo::instance()->errorMsg(ERR_LOST_CONN_EXEMGR);
		setError(gwi.thd, ER_INTERNAL_ERROR, emsg);
		erydbSystemCatalog::removeerydbSystemCatalog(sessionID);
		return;
	}

	// merge table list to parent select
	fParentGwip->tbList.insert(fParentGwip->tbList.end(), gwi.tbList.begin(), gwi.tbList.end());
	fParentGwip->derivedTbList.insert(fParentGwip->derivedTbList.end(), gwi.derivedTbList.begin(), gwi.derivedTbList.end());
	fParentGwip->correlatedTbNameVec.insert(fParentGwip->correlatedTbNameVec.end(), gwi.correlatedTbNameVec.begin(), gwi.correlatedTbNameVec.end());

	// merge view list to parent
	fParentGwip->viewList.insert(fParentGwip->viewList.end(), gwi.viewList.begin(), gwi.viewList.end());

	// merge non-collapsed outer join to parent select
	stack<ParseTree*> tmpstack;
	while (!gwi.ptWorkStack.empty())
	{
		tmpstack.push(gwi.ptWorkStack.top());
		gwi.ptWorkStack.pop();
	}

	while (!tmpstack.empty())
	{
		fParentGwip->ptWorkStack.push(tmpstack.top());
		tmpstack.pop();
	}
}

uint32_t View::processOuterJoin(gp_walk_info& gwi)
{
	return buildOuterJoin(gwi, fSelect);
}

}
