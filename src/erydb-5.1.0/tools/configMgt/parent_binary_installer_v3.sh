#!/usr/bin/expect
#
# $Id: parent_installer.sh 421 2007-04-05 15:46:55Z dhill $
#
# Parent OAM Installer, copy RPM's and custom OS files from postConfigure script
# Argument 0 - Parent OAM IP address
# Argument 1 - Root Password of Parent OAM Module
# Argument 2 - erydb Config File
# Argument 3 - Debug flag 1 for on, 0 for off

set SERVER [lindex $argv 0]
set PASSWORD [lindex $argv 1]
set PACKAGE [lindex $argv 2]
set RELEASE [lindex $argv 3]
set CONFIGFILE [lindex $argv 4]
set USERNAME [lindex $argv 5]
set INSTALLDIR [lindex $argv 6]
set DEBUG [lindex $argv 7]

set ERYDBPACKAGE erydb-erydb-ent-*$PACKAGE

set SHARED "//calweb/shared"

set INSTALLDIRARG " "
set HOME "/root"
if { $USERNAME != "root" } {
	set INSTALLDIRARG "--installdir=$INSTALLDIR/erydb"
	set HOME $INSTALLDIR
}

log_user $DEBUG
spawn -noecho /bin/bash
send "rm -f $PACKAGE\n"
# 
# delete binary package on Parent OAM Module
#
set timeout 30
send_user "Remove erydb Packages from System           "
send "ssh $USERNAME@$SERVER 'rm -f $INSTALLDIR/erydb*.gz;rm -f /root/erydb*.rpm;rm -f /root/erydb*.gz'\n"
expect {
	-re "authenticity" { send "yes\n" 
						expect {
							-re "word: " { send "$PASSWORD\n" } abort
							}
						}
	-re "service not known" { send_user "FAILED: Invalid Host\n" ; exit -1 }
	-re "word: " { send "$PASSWORD\n" } abort
}
expect {
	-re "Permission denied, please try again"         { send_user "FAILED: Invalid password\n" ; exit -1 }
}
send_user "DONE\n"
# 
# get the erydb package
#
send_user "Get erydb Packages                          "
send "smbclient $SHARED -Werydb -Uoamuser%erydb1 -c 'cd Iterations/$RELEASE/packages;prompt OFF;mget $PACKAGE'\n"
expect {
	-re "NT_STATUS_NO_SUCH_FILE" { send_user "FAILED: $PACKAGE not found\n" ; exit -1 }
	-re "getting" 				 { send_user "DONE" } abort
}
send_user "\n"
# 
# send the erydb package
#
send_user "Copy erydb Packages                         "
send "scp $PACKAGE $USERNAME@$SERVER:$HOME/.\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
expect {
	-re "100%" 				{ send_user "DONE" } abort
	-re "scp"  						{ send_user "FAILED\n" ; 
				 			send_user "\n*** Installation Failed\n" ; 
							exit -1 }
	-re "Permission denied, please try again"         { send_user "FAILED: Invalid password\n" ; exit -1 }
	-re "No such file or directory" { send_user "FAILED: Invalid package\n" ; exit -1 }
}
send_user "\n"
# 
# uninstall erydb package
#
send_user "Erase Old erydb Package                     "
send "ssh $USERNAME@$SERVER 'pkill -9 mysqld'\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
# check return
expect {
	-re "# "                  { } abort
}
send "ssh $USERNAME@$SERVER 'rpm -e --nodeps \$(rpm -qa | grep '^erydb') >/dev/null 2>&1; rpm -e --nodeps \$(rpm -qa | grep '^erydb-')'\n"expect -re "word: "
# password for ssh
send "$PASSWORD\n"
# check return
expect {
	-re "uninstall completed" {  } abort
	-re "# "                  {  } abort
	-re "not installed"       {  } abort
	-re "Failed dependencies" {  } abort
	-re "Permission denied, please try again"   { send_user "FAILED: Invalid password\n" ; exit -1 }
}
sleep 10
send "ssh $USERNAME@$SERVER 'rm -f $INSTALLDIR/erydb/releasenum >/dev/null 2>&1; test -x $INSTALLDIR/erydb/bin/pre-uninstall && $INSTALLDIR/erydb/bin/pre-uninstall $INSTALLDIRARG'\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
# check return
expect {
	-re "# "                  { send_user "DONE" } abort
	-re "uninstall completed" { send_user "DONE" } abort
	-re "Failed dependencies" { send_user "FAILED: Failed dependencies\n" ; exit -1 }
	-re "Permission denied, please try again"   { send_user "FAILED: Invalid password\n" ; exit -1 }
}
send_user "\n"
sleep 5
#
# install erydb package
#
set timeout 30
send_user "Install New erydb Package                   "
send "ssh $USERNAME@$SERVER 'tar -C $INSTALLDIR --exclude db -zxf $HOME/$ERYDBPACKAGE;cat $INSTALLDIR/erydb/releasenum'\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
# check return
expect {
	-re "completed" 		  { send_user "DONE" } abort
	-re "release=" 		  	{ send_user "DONE" } abort
	-re "Failed dependencies" { send_user "FAILED: Failed dependencies\n" ; 
								send_user "\n*** Installation Failed\n" ; 
									exit -1 }
	-re "Permission denied, please try again"   { send_user "FAILED: Invalid password\n" ; exit -1 }
	-re "exiting now"   { send_user "FAILED: Error in tar command\n" ; exit -1 }

}
send_user "\n"
set timeout 30
send "rm -f $PACKAGE\n"
#
send_user "Run post-install script                       "
send " \n"
send date\n
send "ssh $USERNAME@$SERVER '$INSTALLDIR/erydb/bin/post-install $INSTALLDIRARG'\n"
set timeout 10
expect {
	-re "word: " { send "$PASSWORD\n" } abort
	-re "passphrase" { send "$PASSWORD\n" } abort
}
set timeout 60
# check return
expect {
	-re "EryDB syslog logging not working" { send_user "ERROR: EryDB System logging not setup\n" ; exit 1 }
	-re "Permission denied, please try again"   { send_user "ERROR: Invalid password\n" ; exit 1 }
	-re "Read-only file system" { send_user "ERROR: local disk - Read-only file system\n" ; exit 1}
	-re "Connection refused"   { send_user "ERROR: Connection refused\n" ; exit 1 }
	-re "closed"   { send_user "ERROR: Connection closed\n" ; exit 1 }
	-re "No route to host"   { send_user "ERROR: No route to host\n" ; exit 1 }
	-re "postConfigure" { send_user "DONE" } abort
	-re "# " { send_user "DONE" } abort
}
send_user "\n"
sleep 10
#
if { $CONFIGFILE != "NULL"} {
	#
	# copy over erydb.xml file
	#
	send_user "Copy erydb Configuration File               "
	send "scp $CONFIGFILE $USERNAME@$SERVER:$INSTALLDIR/erydb/etc/erydb.xml.rpmsave\n"
	expect -re "word: "
	# send the password
	send "$PASSWORD\n"
	expect {
		-re "100%" 				  		{ } abort
		-re "scp"  						{ send_user "FAILED\n" ; 
								send_user "\n*** Installation Failed\n" ; 
								exit -1 }
		-re "Permission denied, please try again"         { send_user "FAILED: Invalid password\n" ; exit -1 }
		-re "No such file or directory" { send_user "FAILED: Invalid package\n" ; exit -1 }
	}
	send "scp $CONFIGFILE $USERNAME@$SERVER:$INSTALLDIR/erydb/etc/erydb.xml\n"
	expect -re "word: "
	# send the password
	send "$PASSWORD\n"
	expect {
		-re "100%" 				  		{ send_user "DONE" } abort
		-re "scp"  						{ send_user "FAILED\n" ; 
								send_user "\n*** Installation Failed\n" ; 
								exit -1 }
		-re "Permission denied, please try again"         { send_user "FAILED: Invalid password\n" ; exit -1 }
		-re "No such file or directory" { send_user "FAILED: Invalid package\n" ; exit -1 }
	}
} else {
	#
	# rename previous installed config file
	#
	send_user "Copy RPM-saved erydb Configuration File     "
	send "ssh $USERNAME@$SERVER 'cd $INSTALLDIR/erydb/etc/;mv -f erydb.xml erydb.xml.install;cp -v erydb.xml.rpmsave erydb.xml'\n"
	expect -re "word: "
	# password for ssh
	send "$PASSWORD\n"
	# check return
	expect {
		-re "erydb.xml"         { send_user "DONE" } abort
		-re "Permission denied, please try again"   { send_user "FAILED: Invalid password\n" ; exit -1 }
	}
}
send_user "\n"
#
exit

