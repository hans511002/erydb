#!/usr/bin/expect
#
# $Id$
#
# Install RPM on system
# Argument 1 - Package name being installed
# Argument 2 - Root Password of remote server
# Argument 3 - Root Password of External Mode

set timeout 10
set RPMPACKAGE " "
set PASSWORD " "
set CONFIGFILE " "
set DEBUG 0
set USERNAME "root"
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
		send_user "'postInstaller.sh' performs a system install of a erydb RPM\n"
		send_user "on a system with erydb already installed or on a new system\n"
		send_user "when the -c option is used.\n"
		send_user "\n"
		send_user "Usage: postInstaller.sh -r 'erydb-rpm' -p 'password' -c 'config-file' -d\n"
		send_user "		erydb-rpm - erydb RPM with directory locatation, i.e. /root/erydb.x.x.x.x\n"
		send_user "		password    - root password on the servers being installed'\n"
		send_user "		config-file - Optional: erydb.xml config file with directory location, i.e. /root/erydb.xml\n"
		send_user "		-d 			- Debug flag\n"
		exit
	} elseif { $arg($i) == "-r" } {
		incr i
		set RPMPACKAGE $arg($i)
	} elseif { $arg($i) == "-p" } {
		incr i
		set PASSWORD $arg($i)
	} elseif { $arg($i) == "-c" } {
		incr i
		set CONFIGFILE $arg($i)
	} elseif { $arg($i) == "-d" } {
		set DEBUG 1
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

if { $RPMPACKAGE == " " || $PASSWORD == " "} {puts "please enter both RPM and password, enter ./postInstaller.sh -h for additional info"; exit -1}

if { $CONFIGFILE == " " } {
	set CONFIGFILE $INSTALLDIR/etc/erydb.xml.rpmsave
}
if { [catch { open $CONFIGFILE "r"} handle ] } {
	puts "erydb Config file not found: $CONFIGFILE"; exit -1
}


send_user "\nPerforming erydb RPM System Install\n\n"

# 
# stopSystem
#
send_user "Stop erydb System                             "
expect -re "# "
send "$INSTALLDIR/bin/eryadmin stopSystem INSTALL y\n"
expect {
	-re "# "                  	{ send_user "DONE" }
	-re "**** stopSystem Failed" { send_user "INFO: System not running" }
}
send_user "\n"
# 
# erase package
#
send_user "Erase erydb Package on Module                 "
expect -re "# "
send "rpm -e --nodeps erydb\n"
expect {
	-re "# "                  { send_user "DONE" }
	-re "uninstall completed" { send_user "DONE" }
	-re "ERROR dependencies" { send_user "ERROR: ERROR dependencies\n" ; exit -1 }
	-re "not installed"       { send_user "INFO: Package not installed" }
}
send_user "\n"

set timeout 60
#
# install package
#
send_user "Install erydb Package on Module               "
send "rpm -ivh $RPMPACKAGE\n"
expect {
	-re "completed" 		  { send_user "DONE" }
	-re "ERROR dependencies" { send_user "ERROR: ERROR dependencies\n" ; 
								send_user "\n*** Installation ERROR\n" ; 
									exit -1 }
	-re "error" 			  { send_user "ERROR\n" ; 
								send_user "\n*** Installation ERROR\n" ; 
								exit -1 }
}
expect -re "# "
log_user 0
exec mv -f $INSTALLDIR/etc/erydb.xml $INSTALLDIR/etc/erydb.xml.new  > /dev/null 2>&1
exec mv -f $CONFIGFILE  $INSTALLDIR/etc/erydb.xml  > /dev/null 2>&1

send_user "\n"
set timeout 380
#
# Run installer
#
send_user "Run System Installer                            "
send "$INSTALLDIR/bin/installer $RPMPACKAGE initial $PASSWORD n 0\n"
expect {
	-re "reboot request successful" 			{ }
	-re "error"   								{ send_user "FAILED" ; exit -1 }
}

send_user "\nerydb RPM System Install Completed, System now rebooting\n\n"

exit 0
