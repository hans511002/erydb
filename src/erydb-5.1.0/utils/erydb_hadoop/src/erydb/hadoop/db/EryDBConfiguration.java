/*
 * Copyright (c) 2014 EryDB, Inc.
 *
 * EryDB, Inc. licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package erydb.hadoop.db;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import org.apache.hadoop.mapred.JobConf;
import org.apache.hadoop.mapred.lib.db.DBInputFormat.NullDBWritable;
import org.apache.hadoop.mapred.lib.db.*;


/**
 * A container for configuration property names for jobs with DB input/output. 
 * <br>
 * The job can be configured using the static methods in this class, 
 * {@link DBInputFormat}, and {@link DBOutputFormat}. 
 * <p> 
 * Alternatively, the properties can be set in the configuration with proper
 * values. 
 *   
 * @see DBConfiguration#configureDB(JobConf, String, String, String, String)
 * @see DBInputFormat#setInput(JobConf, Class, String, String)
 * @see DBInputFormat#setInput(JobConf, Class, String, String, String, String...)
 * @see DBOutputFormat#setOutput(JobConf, String, String...)
 */
public class EryDBConfiguration{

/** Input schema name */
public static final String INPUT_SCHEMA_NAME_PROPERTY = "erydb_hadoop.input.schema.name";

/** Output schema name */
public static final String OUTPUT_SCHEMA_NAME_PROPERTY = "erydb_hadoop.output.schema.name";

/** Output table name */
public static final String OUTPUT_TABLE_NAMES_PROPERTY = "erydb_hadoop.output.table.name";

/** @EryDB Split key for split the query task */
public static final String INPUT_SPLITKEY_NAME_PROPERTY = "erydb_hadoop.splitkey.name";

/** @EryDB Split key min value */
public static final String INPUT_SPLITKEY_MIN_VAL = "erydb_hadoop.splitkey.min.value";

/** @EryDB Split key max value */
public static final String INPUT_SPLITKEY_MAX_VAL = "erydb_hadoop.splitkey.max.value";

/** @EryDB HOME path */
public static final String ERYDB_HOME = "erydb_hadoop.erydb.home.path";

/** Input dir */
public static final String INPUT_PATH = "mapred.input.dir";

/** Output dir */
public static final String OUTPUT_PATH = "mapred.output.dir";

/**
 * Sets the DB access related fields in the JobConf.  
 * @param job the job
 * @param driverClass JDBC Driver class name
 * @param dbUrl JDBC DB access URL. 
 * @param userName DB access username 
 * @param passwd DB access passwd
 */
public static void configureDB(JobConf job, String driverClass, String dbUrl
    , String userName, String passwd)
{

	job.set(DBConfiguration.DRIVER_CLASS_PROPERTY, driverClass);
	job.set(DBConfiguration.URL_PROPERTY, dbUrl);
	if(userName != null)
    job.set(DBConfiguration.USERNAME_PROPERTY, userName);
	if(passwd != null)
    job.set(DBConfiguration.PASSWORD_PROPERTY, passwd);    
}

/**
 * Sets the DB access related fields in the JobConf.  
 * @param job the job
 * @param driverClass JDBC Driver class name
 * @param dbUrl JDBC DB access URL. 
 */
public static void configureDB(JobConf job, String driverClass, String dbUrl) 
{
  configureDB(job, driverClass, dbUrl, null, null);
}

private JobConf job;

public EryDBConfiguration(JobConf job) 
{
	this.job = job;
}

/** Returns a connection object o the DB 
 * @throws ClassNotFoundException 
 * @throws SQLException
 */
Connection getConnection() throws IOException
{
	try 
	{
		Class.forName(job.get(DBConfiguration.DRIVER_CLASS_PROPERTY));
	}catch (ClassNotFoundException exception)
	{
		throw new IOException("Conection driver can not be loaded", exception);
	}
	
	try
	{
		if(job.get(DBConfiguration.USERNAME_PROPERTY) == null)
		{
			return DriverManager.getConnection(job.get(DBConfiguration.URL_PROPERTY));
		} 
		else 
		{
			return DriverManager.getConnection(
			      job.get(DBConfiguration.URL_PROPERTY), 
			      job.get(DBConfiguration.USERNAME_PROPERTY), 
			      job.get(DBConfiguration.PASSWORD_PROPERTY));
		}
	}catch (SQLException exception)
	{
		throw new IOException("Conection can not be established", exception);
	}
}

String getInputSchemaName() 
{
	return job.get(EryDBConfiguration.INPUT_SCHEMA_NAME_PROPERTY);
}

void setInputSchemaName(String schemaName) 
{
	job.set(EryDBConfiguration.INPUT_SCHEMA_NAME_PROPERTY, schemaName);
}
 
String getInputTableName() 
{
	return job.get(DBConfiguration.INPUT_TABLE_NAME_PROPERTY);
}

void setInputTableName(String tableName) 
{
	job.set(DBConfiguration.INPUT_TABLE_NAME_PROPERTY, tableName);
}

String[] getInputFieldNames() 
{
	return job.getStrings(DBConfiguration.INPUT_FIELD_NAMES_PROPERTY);
}

void setInputFieldNames(String... fieldNames) 
{
	job.setStrings(DBConfiguration.INPUT_FIELD_NAMES_PROPERTY, fieldNames);
}

String getInputConditions() 
{
	return job.get(DBConfiguration.INPUT_CONDITIONS_PROPERTY);
}

void setInputConditions(String conditions) 
{
	if (conditions != null && conditions.length() > 0)
		job.set(DBConfiguration.INPUT_CONDITIONS_PROPERTY, conditions);
}

String getInputOrderBy() 
{
	return job.get(DBConfiguration.INPUT_ORDER_BY_PROPERTY);
}
 
/** @EryDB */
void setSplitKey(String key) 
{
	job.setStrings(EryDBConfiguration.INPUT_SPLITKEY_NAME_PROPERTY, key);
}
 
/** @EryDB */
String getSplitKey()
{
	return job.get(EryDBConfiguration.INPUT_SPLITKEY_NAME_PROPERTY);
}
 
/** @EryDB */
public void setMinVal(long value) 
{
	job.setLong(INPUT_SPLITKEY_MIN_VAL, value);
}
 
/** @EryDB */
public Long getMinVal() 
{
	if(job.get(INPUT_SPLITKEY_MIN_VAL)==null) 
		return null;
	return job.getLong(INPUT_SPLITKEY_MIN_VAL, -1);
}
 
/** @EryDB */
public void setMaxVal(long value) 
{
	job.setFloat(INPUT_SPLITKEY_MAX_VAL, value);
}
 
/** @EryDB */
public Long getMaxVal() 
{
	if(job.get(INPUT_SPLITKEY_MAX_VAL)==null) 
		return null;
	return job.getLong(INPUT_SPLITKEY_MAX_VAL, -1);
}
 
void setInputOrderBy(String orderby) 
{
	if(orderby != null && orderby.length() >0) 
	{
		job.set(DBConfiguration.INPUT_ORDER_BY_PROPERTY, orderby);
	}
}

String getInputQuery() 
{
	return job.get(DBConfiguration.INPUT_QUERY);
}

void setInputQuery(String query) 
{
	if(query != null && query.length() >0) 
	{
		job.set(DBConfiguration.INPUT_QUERY, query);
	}
}
 
String getInputCountQuery() 
{
	return job.get(DBConfiguration.INPUT_COUNT_QUERY);
}
 
void setInputCountQuery(String query) 
{
	if(query != null && query.length() >0) 
	{
		job.set(DBConfiguration.INPUT_COUNT_QUERY, query);
	}
}


Class<?> getInputClass() 
{
	return job.getClass(DBConfiguration.INPUT_CLASS_PROPERTY, NullDBWritable.class);
}

void setInputClass(Class<? extends DBWritable> inputClass) 
{
	job.setClass(DBConfiguration.INPUT_CLASS_PROPERTY, inputClass, DBWritable.class);
}
 
String getOutputSchemaName() 
{
	return job.get(EryDBConfiguration.OUTPUT_SCHEMA_NAME_PROPERTY);
}

void setOutputSchemaName(String schemaName) 
{
	job.set(EryDBConfiguration.OUTPUT_SCHEMA_NAME_PROPERTY, schemaName);
}
 
String[] getOutputTableNames() 
{
	return job.getStrings(EryDBConfiguration.OUTPUT_TABLE_NAMES_PROPERTY);
}

void setOutputTableNames(String... tableNames) 
{
	job.setStrings(EryDBConfiguration.OUTPUT_TABLE_NAMES_PROPERTY, tableNames);
}

String[] getOutputFieldNames() 
{
	return job.getStrings(DBConfiguration.OUTPUT_FIELD_NAMES_PROPERTY);
}

void setOutputFieldNames(String... fieldNames) 
{
	job.setStrings(DBConfiguration.OUTPUT_FIELD_NAMES_PROPERTY, fieldNames);
}
 
public String getEryDBHome()
{
	return job.get(EryDBConfiguration.ERYDB_HOME);
}
 
public void setEryDBHome(String path)
{
	job.set(EryDBConfiguration.ERYDB_HOME, path);
}
 
public String getInputPath()
{
	return job.get(EryDBConfiguration.INPUT_PATH);
}
 
public void setInputPath(String path)
{
	job.set(EryDBConfiguration.INPUT_PATH, path);
}
 
public String getOutputPath()
{
	return job.get(EryDBConfiguration.OUTPUT_PATH);
}
 
public void setOutputPath(String path)
{
	job.set(EryDBConfiguration.OUTPUT_PATH, path);
}

}


