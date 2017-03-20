How to use the EryDB UDF SDK

Make sure you have a working GCC C++ compiler system, version 4.1.2 or later. You 
also must have the libxml2-devel package installed.
Obtain the EryDB source distribution for your version of EryDB 
from github.com.
Ideally, the machine you are compiling on and deploying on are the same machine. If this 
is not possible, they must have the same EryDB software installation.

Unpack the source tar file

Go into the utils/udfsdk directory.

At this point you can use the erydb_add() function template in udferydb.cpp and udfmysql.cpp
files to create your own function or just try that function as is.
Make the library
Stop EryDB
Copy the libudf_mysql.so.1.0.0 and libudfsdk.so.1.0.0 file to /usr/local/erydb/lib on
every EryDB node
Start EryDB
In the directory /usr/local/erydb/mysql/lib64/mysql/plugin create a symbolic link called 
libudf_msql.so to the file /usr/local/erydb/lib/libudf_msql.so.1.0.0
In the mysql client add the function (e.g. "create function erydb_add returns integer soname 
'libudf_msql.so';")
You should now be able to use the erydb_add() function in the select and/or where clauses 
of SQL statements.
