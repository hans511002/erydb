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

package erydb.hadoop.example;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;
import java.sql.*;
import java.util.Date;
import java.util.Formatter;
import java.io.IOException;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.lib.db.*;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.*;
import org.apache.hadoop.mapreduce.lib.output.*;
import org.apache.hadoop.mapred.JobClient;
import org.apache.hadoop.mapred.JobConf;
import org.apache.hadoop.mapred.Mapper;
import org.apache.hadoop.mapred.Reducer;
import org.apache.hadoop.mapred.TextInputFormat;
import org.apache.hadoop.mapred.SequenceFileInputFormat;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.util.*;
import org.apache.hadoop.*;

import erydb.hadoop.db.*;

public class EryDBOutputDriver extends Configured implements Tool
{
	public int run (String[] args) throws Exception
	{	
		Configuration conf = new Configuration();
		JobConf jobconf = new JobConf(conf, InfiniDoopDriver.class);
		DBConfiguration.configureDB(jobconf,
		 		    "com.mysql.jdbc.Driver",
		 		    "jdbc:mysql://srvswint4/tpch1","root", "");
		String [] fields = { "n_nationkey", "n_name" };
		String [] outFields = {"id", "name"};
		jobconf.setInputFormat(ERYDBFileInputFormat.class);
		jobconf.setOutputFormat(EryDBOutputFormat.class);
		jobconf.setOutputKeyClass(NullWritable.class);
		jobconf.setOutputValueClass(Text.class);
		EryDBOutputFormat.setOutput(jobconf, "db", outFields);
		EryDBConfiguration erydbconf = new EryDBConfiguration(jobconf);
		erydbconf.setInputPath("input");
		erydbconf.setOutputPath("output");
		erydbconf.setEryDBHome("/usr/local/erydb");

		jobconf.setMapperClass(InfiniDoopMapper.class);
		jobconf.setNumMapTasks(1);
		jobconf.setNumReduceTasks(2);
		JobClient client = new JobClient();
		client.setConf(jobconf);
		try {
			JobClient.runJob(jobconf);
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		return 0;
}

public static void main(String [] args) throws Exception
{
	int ret = ToolRunner.run(new EryDBOutputDriver(), args);
	System.exit(ret);
}

}
