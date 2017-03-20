/* c-basic-offset: 4; tab-width: 4; indent-tabs-mode: nil
 * vi: set shiftwidth=4 tabstop=4 expandtab:
 *  :indentSize=4:tabSize=4:noTabs=true:
 *
 * Copyright (C) 2016 MariaDB Corporaton
 *
 * This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include "erydb_mysql.h"
#include <vector>

#include <boost/shared_ptr.hpp>
#include "erydbsystemcatalog.h"
#include "dataconvert.h"


// Required declaration as it isn't in a MairaDB include
bool schema_table_store_record(THD *thd, TABLE *table);

ST_FIELD_INFO is_erydb_tables_fields[] =
{
    {"TABLE_SCHEMA", 64, MYSQL_TYPE_STRING, 0, 0, 0, 0},
    {"TABLE_NAME", 64, MYSQL_TYPE_STRING, 0, 0, 0, 0},
    {"OBJECT_ID", 11, MYSQL_TYPE_LONG, 0, 0, 0, 0},
    {"CREATION_DATE", 0, MYSQL_TYPE_DATE, 0, 0, 0, 0},
    {"COLUMN_COUNT", 11, MYSQL_TYPE_LONG, 0, 0, 0, 0},
    {"AUTOINCREMENT", 11, MYSQL_TYPE_LONG, 0, MY_I_S_MAYBE_NULL, 0, 0},
    {0, 0, MYSQL_TYPE_NULL, 0, 0, 0, 0}
};

static int is_erydb_tables_fill(THD *thd, TABLE_LIST *tables, COND *cond)
{
    CHARSET_INFO *cs = system_charset_info;
    TABLE *table = tables->table;

    boost::shared_ptr<execplan::erydbSystemCatalog> systemCatalogPtr =
        execplan::erydbSystemCatalog::makeerydbSystemCatalog(execplan::erydbSystemCatalog::erydb_tid2sid(thd->thread_id));

    const std::vector< std::pair<execplan::erydbSystemCatalog::OID, execplan::erydbSystemCatalog::TableName> > catalog_tables
        = systemCatalogPtr->getTables();

    for (std::vector<std::pair<execplan::erydbSystemCatalog::OID, execplan::erydbSystemCatalog::TableName> >::const_iterator it = catalog_tables.begin();
         it != catalog_tables.end(); ++it)
    {
        execplan::erydbSystemCatalog::TableInfo tb_info = systemCatalogPtr->tableInfo((*it).second);
        std::string create_date = dataconvert::DataConvert::dateToString((*it).second.create_date);
        table->field[0]->store((*it).second.schema.c_str(), (*it).second.schema.length(), cs);
        table->field[1]->store((*it).second.table.c_str(), (*it).second.table.length(), cs);
        table->field[2]->store((*it).first);
        table->field[3]->store(create_date.c_str(), create_date.length(), cs);
        table->field[4]->store(tb_info.numOfCols);
        if (tb_info.tablewithautoincr)
        {
            table->field[5]->set_notnull();
            table->field[5]->store(systemCatalogPtr->nextAutoIncrValue((*it).second));
        }
        else
        {
            table->field[5]->set_null();
        }
        table->field[5]->store(tb_info.tablewithautoincr);
        if (schema_table_store_record(thd, table))
            return 1;
    }

    return 0;
}

static int is_erydb_tables_plugin_init(void *p)
{
    ST_SCHEMA_TABLE *schema = (ST_SCHEMA_TABLE*) p;
    schema->fields_info = is_erydb_tables_fields;
    schema->fill_table = is_erydb_tables_fill;
    return 0;
}

static struct st_mysql_information_schema is_erydb_tables_plugin_version =
{ MYSQL_INFORMATION_SCHEMA_INTERFACE_VERSION };

maria_declare_plugin(is_erydb_tables_plugin)
{
    MYSQL_INFORMATION_SCHEMA_PLUGIN,
    &is_erydb_tables_plugin_version,
    "ERYDB_TABLES",
    "MariaDB Corporaton",
    "An information schema plugin to list EryDB tables",
    PLUGIN_LICENSE_GPL,
    is_erydb_tables_plugin_init,
    //is_erydb_tables_plugin_deinit,
    NULL,
    0x0100,
    NULL,
    NULL,
    "1.0",
    MariaDB_PLUGIN_MATURITY_STABLE
}
maria_declare_plugin_end;


