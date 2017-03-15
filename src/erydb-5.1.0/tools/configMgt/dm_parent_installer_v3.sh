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
set CEFLAG [lindex $argv 6]
set DEBUG [lindex $argv 7]

set ERYDBPACKAGE erydb-$PACKAGE
set MYSQLPACKAGE erydb-mysql-$PACKAGE
set MYSQLDPACKAGE erydb-mysqld-$PACKAGE
set INSTALLDIR "/usr/local"

#set SHARED "//cal6500/shared"
set SHARED "//calweb/shared"

log_user $DEBUG
spawn -noecho /bin/bash
send "rm -f $ERYDBPACKAGE\n"
# 
# delete and erase all old packages from Director Module
#
set timeout 10
send "ssh $USERNAME@$SERVER 'rm -f /root/$ERYDBPACKAGE'\n"
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
	-re "#" 						{ } abort
	-re "Permission denied, please try again"         { send_user "FAILED: Invalid password\n" ; exit -1 }
}
# 
# erase erydb packages
#
set timeout 60
send_user "Erase Old erydb Packages                    "
send "ssh $USERNAME@$SERVER 'pkill -9 mysqld'\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
# check return
expect {
	-re "# "                  { } abort
}
send "ssh $USERNAME@$SERVER 'rpm -e --nodeps \$(rpm -qa | grep '^erydb') >/dev/null 2>&1; rpm -e --nodeps \$(rpm -qa | grep '^erydb-')'\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
# check return
expect {
	-re "uninstall completed" {  } abort
	-re "# "                  {  } abort
	-re "not installed"       {  } abort
	-re "Failed dependencies" { send_user "FAILED: Failed dependencies\n" ; exit -1 }
	-re "Permission denied, please try again"   { send_user "FAILED: Invalid password\n" ; exit -1 }
}
sleep 10
send "ssh $USERNAME@$SERVER 'rm -f $INSTALLDIR/erydb/releasenum >/dev/null 2>&1; test -x $INSTALLDIR/erydb/bin/pre-uninstall && $INSTALLDIR/erydb/bin/pre-uninstall'\n"
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
# get the erydb package
#
send_user "Get erydb Packages                          "
send "smbclient $SHARED -Werydb -Uoamuser%erydb1 -c 'cd Iterations/$RELEASE/;prompt OFF;mget $PACKAGE'\n"
expect {
	-re "NT_STATUS_NO_SUCH_FILE" { send_user "FAILED: $PACKAGE not found\n" ; exit -1 }
	-re "getting" 				 { send_user "DONE" } abort
}
send_user "\n"
# 
# send the erydb package
#
send_user "Copy erydb Packages                         "
send "scp -q $PACKAGE $USERNAME@$SERVER:/root/.\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
expect {
	-re "#" 						{ send_user "DONE" } abort
	-re "scp"  						{ send_user "FAILED: SCP failure\n" ; exit -1 }
	-re "Permission denied, please try again"         { send_user "FAILED: Invalid password\n" ; exit -1 }
	-re "No such file or directory" { send_user "FAILED: Invalid package\n" ; exit -1 }
}
send_user "\n"
#send "rm -f $PACKAGE\n"
#
# install erydb package
#
set timeout 120
send_user "Install New erydb Packages                  "
send "ssh $USERNAME@$SERVER ' rpm -iv --nodeps /root/$ERYDBPACKAGE'\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
# check return
expect {
	-re "completed" { expect {
        			  -re "completed" { expect {
        						-re "completed" { send_user "DONE" } abort
						}
				}
			}
	}
	-re "Failed dependencies" { send_user "FAILED: Failed dependencies\n" ; 
								send_user "\n*** Installation Failed\n" ; 
									exit -1 }
	-re "Permission denied, please try again"   { send_user "FAILED: Invalid password\n" ; exit -1 }
}
send_user "\n"
set timeout 120
expect -re "# "
#
if { $CONFIGFILE != "NULL"} {
	#
	# copy over erydb.xml file
	#
	send_user "Copy erydb Configuration File               "
	send "scp $CONFIGFILE $USERNAME@$SERVER:/usr/local/erydb/etc/erydb.xml.rpmsave\n"
	expect -re "word: "
	# send the password
	send "$PASSWORD\n"
	expect {
		-re "100%" 				  		{ } abort
		-re "scp"  						{ send_user "FAILED: SCP failure\n" ; exit -1 }
		-re "Permission denied, please try again"         { send_user "FAILED: Invalid password\n" ; exit -1 }
		-re "No such file or directory" { send_user "FAILED: Invalid package\n" ; exit -1 }
	}
	send "scp $CONFIGFILE $USERNAME@$SERVER:/usr/local/erydb/etc/erydb.xml\n"
	expect -re "word: "
	# send the password
	send "$PASSWORD\n"
	expect {
		-re "100%" 				  		{ send_user "DONE" } abort
		-re "scp"  						{ send_user "FAILED: SCP failure\n" ; exit -1 }
		-re "Permission denied, please try again"         { send_user "FAILED: Invalid password\n" ; exit -1 }
		-re "No such file or directory" { send_user "FAILED: Invalid package\n" ; exit -1 }
	}
	send "scp $CONFIGFILE $USERNAME@$SERVER:/tmp/erydb.xml\n"
	expect -re "word: "
	# send the password
	send "$PASSWORD\n"
	expect {
		-re "100%" 				  		{ send_user " " } abort
	}
} else {
	#
	# rename previous installed config file
	#
	send_user "Copy RPM-saved erydb Configuration File     "
	send "ssh $USERNAME@$SERVER 'cd /usr/local/erydb/etc/;mv -f erydb.xml erydb.xml.install;cp -v erydb.xml.rpmsave erydb.xml'\n"
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

