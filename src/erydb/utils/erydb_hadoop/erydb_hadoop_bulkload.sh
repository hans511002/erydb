#!/bin/sh
export LD_LIBRARY_PATH=/usr/local/erydb/lib:$LD_LIBRARY_PATH
export ERYDB_CONFIG_FILE=/usr/local/erydb/etc/erydb.xml
export PATH=$PATH:/usr/local/hadoop-0.20.2/bin:/usr/local/erydb/bin
export ERYDB_HOME=/usr/local/erydb/etc
hadoop dfs -cat $1 | cpimport $2 $3

