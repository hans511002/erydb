#EryDB Server (version 5.1)
EryDB 5.1.1 is the development version of EryDB . 
It is built by porting EryDB 4.6.7 on MariaDB 10.1.14 and adding entirely 
new features not found anywhere else.

###Alpha release notice
EryDB 5.1.1 is an Alpha release. This is the first MariaDB release, not all features planned for the erydb 5.0 
series are included in this release. 

A few things to notice:
- Do not use alpha releases on production systems.

Additional features and product enhancements will be pushed in future releases. 

##The structure of this repository is:
* Branch "master" - this is the latest released version of the source code.  Each major release is tagged.
* Branch "develop" - this is the mainline development branch.

 erydb server and the engine are in separate repositories, but the engine repository is integrated into the server repository using a git "sub repository".  The server currently uses CMake but the engine is still based on autotools.

##Build dependencies
These packages need to be install along with the "group development Tools" package:

bison ncurses-devel readline-devel boost-devel perl-devel openssl-devel cmake libxml2-devel

##Building master branch
The current (1.0.1) master branch does not build properly.  This has been rectified in the *development* branch and once version 1.0.2 is released, building the master branch will work correctly.

##Building develop branch

Building can do be as a non-root user. If you do a "build install", it will install the binaries in /usr/local/erydb
and the use of sudo is required.

Currently building has only been certified on CentOS 6.6, 6.7 and 7.0.  Building on other platforms will be certified in a later release.
  
##Run dependencies
These packages need to be install:

expect perl perl-DBI openssl zlib file sudo libnl

##erydb utilizes the System Logging for logging purposes
So you will want to make sure that one of these system logging packages is installed:

  syslog, rsyslog, or syslog-ng

##Configure and Starting of erydb 

Follow the binary package install instructions in the Erydb Getting Starter Guide:
 
Commands to run as root user:

  * cd /usr/local/erydb/bin/
  * ./post-install
  * ./postConfigure

 
