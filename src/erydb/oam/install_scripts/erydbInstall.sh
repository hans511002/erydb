#!/usr/bin/expect
#
# $Id$
#
# Install Package on system

set timeout 30
set USERNAME "root"
set RPMVERSION " "
set PASSWORD " "
set MYSQLPASSWORD dummymysqlpw
set PACKAGE " "
set CONFIGFILE " "
set DEBUG 0
set NODEPS "-h"
set INSTALLDIR "/usr/local/erydb"

spawn -noecho /bin/bash

for {set i 0} {$i<[llength $argv]} {incr i} {
	set arg($i) [lindex $argv $i]
}

set i 0
while true {
	if { $i == [llength $argv] } { break }
	if { $arg($i) == "-h" } {
		send_user "\n"
		send_user "'erydbInstaller.sh' performs a system install of the erydb EryDB Packages\n"
		send_user "from the /root/ directory. These Packages would have already been installed\n"
		send_user "on the local Module.\n"
		send_user "Usage: erydbInstaller.sh -v 'erydb-version' -p 'password' -t 'package-type' -c 'config-file'-m 'mysql-password' -d\n"
		send_user "		erydb-version - EryDB Version, i.e. 1.0.0-1\n"
		send_user "		password    	- root password on the servers being installed'\n"
		send_user "		package-type 	- Package Type being installed (rpm, deb, or binary)\n"
		send_user "		config-file 	- Optional: erydb.xml config file with directory location, i.e. /root/erydb.xml\n"
		send_user "			 	 	Default version is $INSTALLDIR/etc/erydb.xml.rpmsave\n"
		send_user "		mysql-password    - MySQL password on the servers being installed'\n"		
		send_user "		-d		- Debug flag, output verbose information\n"
		exit 0
	} elseif { $arg($i) == "-v" } {
		incr i
		set RPMVERSION $arg($i)
	} elseif { $arg($i) == "-p" } {
		incr i
		set PASSWORD $arg($i)
	} elseif { $arg($i) == "-t" } {
		incr i
		set PACKAGE $arg($i)
	} elseif { $arg($i) == "-c" } {
		incr i
		set CONFIGFILE $arg($i)
	} elseif { $arg($i) == "-d" } {
		set DEBUG 1
	} elseif { $arg($i) == "-f" } {
		set NODEPS "--nodeps"
	} elseif { $arg($i) == "-m" } {
		incr i
		set MYSQLPASSWORD $arg($i)
	} elseif { $arg($i) == "-i" } {
		incr i
		set INSTALLDIR $arg($i)
	} elseif { $arg($i) == "-u" } {
		incr i
		set USERNAME $arg($i)
	}
	incr i
}

log_user $DEBUG

set timeout 2
send "$INSTALLDIR/bin/erydb status\n"
expect {
        "is running"	{ puts "EryDB is running, can't run erydbInstall.sh while EryDB is running. Exiting..\n";
						exit 1
					}
}

if { $CONFIGFILE == " " } {
	set CONFIGFILE $INSTALLDIR/etc/erydb.xml.rpmsave
}

if { [catch { open $CONFIGFILE "r"} handle ] } {
	puts "erydb Config file not found: $CONFIGFILE"; exit 1
}

exec rm -f $INSTALLDIR/etc/erydb.xml.new  > /dev/null 2>&1
exec mv -f $INSTALLDIR/etc/erydb.xml $INSTALLDIR/etc/erydb.xml.new  > /dev/null 2>&1
exec /bin/cp -f $CONFIGFILE  $INSTALLDIR/etc/erydb.xml  > /dev/null 2>&1

set timeout 2
set INSTALL 2
send "$INSTALLDIR/bin/getConfig DBRM_Controller NumWorkers\n"
expect {
        1                         { set INSTALL 1
										set PASSWORD "dummy"
										set RPMVERSION "rpm" }
}


if { $INSTALL == "2" && $PASSWORD == " "} {puts "please enter the remote server root password, enter ./erydbInstaller.sh -h for additional info"; exit 1}

if { $INSTALL == "2" && $RPMVERSION == " " } {puts "please enter Package version, enter ./erydbInstaller.sh -h for additional info"; exit 1}

send_user "\n"

if { $INSTALL == "2" } {
	if { $PACKAGE == "rpm" } {
		set ERYDBPACKAGE1 /root/erydb-libs-$RPMVERSION*.rpm
		set ERYDBPACKAGE2 /root/erydb-platform-$RPMVERSION*.rpm
		set ERYDBPACKAGE3 /root/erydb-enterprise-$RPMVERSION*.rpm
		set CONNECTORPACKAGE1 /root/erydb-mysql-$RPMVERSION*.rpm
		set CONNECTORPACKAGE2 /root/erydb-storage-engine-$RPMVERSION*.rpm
		send_user "Installing EryDB Packages: $ERYDBPACKAGE1, $ERYDBPACKAGE2, $ERYDBPACKAGE3, $CONNECTORPACKAGE1, $CONNECTORPACKAGE2\n\n"
		set EEPKG "rpm"
	} elseif { $PACKAGE == "deb" } {
		set ERYDBPACKAGE1 /root/erydb-libs_$RPMVERSION*.deb
		set ERYDBPACKAGE2 /root/erydb-platform_$RPMVERSION*.deb
		set ERYDBPACKAGE3 /root/erydb-enterprise_$RPMVERSION*.deb
		set CONNECTORPACKAGE1 /root/erydb-mysql_$RPMVERSION*.deb
		set CONNECTORPACKAGE2 /root/erydb-storage-engine_$RPMVERSION*.deb
		send_user "Installing EryDB Packages: $ERYDBPACKAGE1, $ERYDBPACKAGE2, $ERYDBPACKAGE3, $CONNECTORPACKAGE1, $CONNECTORPACKAGE2\n\n"
		set EEPKG "deb"
	} elseif { $PACKAGE == "binary" } {
		set ERYDBPACKAGE /root/erydb-ent-$RPMVERSION*bin.tar.gz
		set CONNECTORPACKAGE1 "nopkg"
		set CONNECTORPACKAGE2 "nopkg"
		send_user "Installing EryDB Package: $ERYDBPACKAGE\n\n"
		set EEPKG "binary"
	} else {
		puts "please enter Valid Package Type, enter ./erydbInstaller.sh -h for additional info"; exit 1
	}
} else {
	set ERYDBPACKAGE1 "dummy.rpm"
	set ERYDBPACKAGE2 "dummy.rpm"
	set ERYDBPACKAGE3 "dummy.rpm"
	set CONNECTORPACKAGE1 "dummy.rpm"
	set CONNECTORPACKAGE2 "dummy.rpm"
	set EEPKG "rpm"
}

send_user "Performing EryDB System Install, please wait...\n"

send "$INSTALLDIR/bin/setConfig -d Installation EEPackageType $EEPKG\n" 
expect {
	-re {[$#] }                  {  }
}

send_user "\n"
set timeout 600
#
# Run installer
#
send "$INSTALLDIR/bin/installer $ERYDBPACKAGE1 $ERYDBPACKAGE2 $ERYDBPACKAGE3 $CONNECTORPACKAGE1 $CONNECTORPACKAGE2 initial $PASSWORD n $NODEPS  $MYSQLPASSWORD $DEBUG\n"
expect {
	"EryDB Install Successfully Completed" 	{ }
	"ERROR"   { send_user "FAILED: error returned from installer, execute with debug mode on to determine error\n" ; exit 1 }
	"Enter MySQL password"   { send_user "FAILED: a MySQL password is set\n" ; exit 1 }	
	timeout	{ send_user "FAILED: Timeout while running installer, execute with debug mode on to determine error\n" ; exit 1 }
}

send_user "\nerydb Package System Install Completed\n\n"

exit 0
# vim:ts=4 sw=4:

