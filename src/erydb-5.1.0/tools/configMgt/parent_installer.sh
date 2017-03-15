#!/usr/bin/expect
#
# $Id: parent_installer.sh 421 2007-04-05 15:46:55Z dhill $
#
# Parent OAM Installer, copy RPM's and custom OS files from postConfigure script
# Argument 0 - Parent OAM IP address
# Argument 1 - Root Password of Parent OAM Module
# Argument 2 - erydb Config File
# Argument 3 - Debug flag 1 for on, 0 for off

set timeout 40
set USERNAME root
set SERVER [lindex $argv 0]
set PASSWORD [lindex $argv 1]
set PACKAGE [lindex $argv 2]
set RELEASE [lindex $argv 3]
set CONFIGFILE [lindex $argv 4]
set DEBUG [lindex $argv 5]
set ERYDBPACKAGE erydb-platform-$PACKAGE
set ERYDBPACKAGE0 erydb-0$PACKAGE
set ERYDBPACKAGE1 erydb-1$PACKAGE
set ORACLEPACKAGE erydb-oracle$PACKAGE
set MYSQLPACKAGE erydb-storage-engine-$PACKAGE
set MYSQLDPACKAGE erydb-mysql-$PACKAGE

set SHARED "//calweb/shared"

log_user $DEBUG
spawn -noecho /bin/bash
send "rm -f $PACKAGE,$ERYDBPACKAGE0,$ERYDBPACKAGE1,$ORACLEPACKAGE,$MYSQLPACKAGE,$MYSQLDPACKAGE\n"
# 
# delete and erase all old packages from Director Module
#
send "ssh $USERNAME@$SERVER 'rm -f /root/erydb*.rpm'\n"
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
# erase erydb-oracle package
#
expect -re "# "
send_user "Erase Old erydb-Oracle Connector Package    "
send "ssh $USERNAME@$SERVER ' rpm -e --nodeps --allmatches erydb-oracle'\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
# check return
expect {
	-re "uninstall completed" { send_user "DONE" } abort
	-re "# "                  { send_user "DONE" } abort
	-re "not installed"       { send_user "WARNING: Package not installed" } abort
	-re "Failed dependencies" { send_user "FAILED: Failed dependencies\n" ; exit -1 }
	-re "Permission denied, please try again"   { send_user "FAILED: Invalid password\n" ; exit -1 }
}
send_user "\n"
# 
# erase erydb-mysql package
#
expect -re "# "
send_user "Erase Old erydb-Mysqld Connector Package    "
send "ssh $USERNAME@$SERVER 'pkill -9 mysqld'\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
# check return
expect {
	-re "# "                  { } abort
}
send "ssh $USERNAME@$SERVER ' rpm -e --nodeps --allmatches erydb-mysql'\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
# check return
expect {
	-re "uninstall completed" { send_user "DONE" } abort
	-re "# "                  { send_user "DONE" } abort
	-re "not installed"       { send_user "WARNING: Package not installed" } abort
	-re "Failed dependencies" { send_user "FAILED: Failed dependencies\n" ; exit -1 }
	-re "Permission denied, please try again"   { send_user "FAILED: Invalid password\n" ; exit -1 }
}
send_user "\n"
# 
# erase erydb-storage-engine package
#
expect -re "# "
send_user "Erase Old erydb-Mysql Connector Package     "
send "ssh $USERNAME@$SERVER ' rpm -e --nodeps --allmatches erydb-storage-engine'\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
# check return
expect {
	-re "uninstall completed" { send_user "DONE" } abort
	-re "# "                  { send_user "DONE" } abort
	-re "not installed"       { send_user "WARNING: Package not installed" } abort
	-re "Failed dependencies" { send_user "FAILED: Failed dependencies\n" ; exit -1 }
	-re "Permission denied, please try again"   { send_user "FAILED: Invalid password\n" ; exit -1 }
}
send_user "\n"
send "rm -f $PACKAGE\n"
# 
# erase erydb package
#
expect -re "# "
send_user "Erase Old erydb Packages                     "
send "ssh $USERNAME@$SERVER ' rpm -e --nodeps --allmatches erydb-libs erydb-platform erydb-enterprise'\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
# check return
expect {
	-re "uninstall completed" { send_user "DONE" } abort
	-re "# "                  { send_user "DONE" } abort
	-re "not installed"       { send_user "WARNING: Package not installed" } abort
	-re "Failed dependencies" { send_user "FAILED: Failed dependencies\n" ; exit -1 }
	-re "Permission denied, please try again"   { send_user "FAILED: Invalid password\n" ; exit -1 }
}
send_user "\n"
# 
# get the erydb package
#
expect -re "# "
send_user "Get erydb Package                           "
send "smbclient $SHARED -Werydb -Uoamuser%erydb1 -c 'cd Iterations/$RELEASE/;prompt OFF;mget $ERYDBPACKAGE0'\n"
expect {
	-re "NT_STATUS_NO_SUCH_FILE" { 
		send "smbclient $SHARED -Werydb -Uoamuser%erydb1 -c 'cd Iterations/$RELEASE/;prompt OFF;mget $ERYDBPACKAGE1'\n"
		expect {
			-re "NT_STATUS_NO_SUCH_FILE" { send_user "FAILED: $ERYDBPACKAGE not found\n" ; exit -1 }
			-re "getting" 				 { send_user "DONE" } abort
		}
	}
	-re "getting" 				 { send_user "DONE" } abort
}
send_user "\n"
# 
# send the erydb package
#
send_user "Copy erydb Package                          "
send "scp $ERYDBPACKAGE $USERNAME@$SERVER:/root/.\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
expect {
	-re "100%" 						{ send_user "DONE" } abort
	-re "scp"  						{ send_user "FAILED\n" ; 
				 			send_user "\n*** Installation Failed\n" ; 
							exit -1 }
	-re "Permission denied, please try again"         { send_user "FAILED: Invalid password\n" ; exit -1 }
	-re "No such file or directory" { send_user "FAILED: Invalid package\n" ; exit -1 }
}
send_user "\n"
send "rm -f $PACKAGE\n"
#
# install erydb package
#
expect -re "# "
set timeout 120
send_user "Install New erydb Package                   "
send "ssh $USERNAME@$SERVER ' rpm -ivh /root/$ERYDBPACKAGE'\n"
expect -re "word: "
# password for ssh
send "$PASSWORD\n"
# check return
expect {
	-re "completed" 		  { send_user "DONE" } abort
	-re "Failed dependencies" { send_user "FAILED: Failed dependencies\n" ; 
								send_user "\n*** Installation Failed\n" ; 
									exit -1 }
	-re "Permission denied, please try again"   { send_user "FAILED: Invalid password\n" ; exit -1 }
}
send_user "\n"
set timeout 40
expect -re "# "
send "rm -f $PACKAGE\n"
#
if { $CONFIGFILE != "NULL"} {
	#
	# copy over erydb.xml file
	#
	send_user "Copy erydb Configuration File               "
	send "scp $CONFIGFILE $USERNAME@$SERVER:/usr/local/erydb/etc/erydb.xml\n"
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
# get the erydb-oracle package
#
set timeout 40
expect -re "# "
send_user "Get erydb-Oracle Connector Package          "
send "smbclient $SHARED -Werydb -Uoamuser%erydb1 -c 'cd Iterations/$RELEASE/;prompt OFF;mget $ORACLEPACKAGE'\n"
expect {
	-re "NT_STATUS_NO_SUCH_FILE" { send_user "WARNING: $ORACLEPACKAGE not found, skipping\n" } abort
	-re "getting"	{ send_user "DONE\n"
						# 
						# send the erydb-oracle package
						#
						expect -re "# "
						send_user "Copy erydb-Oracle Connector Package         "
						send "scp $ORACLEPACKAGE $USERNAME@$SERVER:/root/.\n"
						expect -re "word: "
						# password for ssh
						send "$PASSWORD\n"
						# check return
						expect {
							-re "100%" 						{ send_user "DONE" } abort
							-re "scp"  						{ send_user "FAILED\n" ; 
													send_user "\n*** Installation Failed\n" ; 
													exit -1 }
							-re "Permission denied, please try again"         { send_user "FAILED: Invalid password\n" ; exit -1 }
							-re "No such file or directory" { send_user "FAILED: Invalid package\n" ; exit -1 }
						}
						#
						# install erydb-oracle package
						#
						send_user "\n"
						expect -re "# "
						set timeout 120
						send_user "Install erydb-Oracle Connector Package      "
						send "ssh $USERNAME@$SERVER ' rpm -ivh /root/$ORACLEPACKAGE'\n"
						expect -re "word: "
						# password for ssh
						send "$PASSWORD\n"
						# check return
						expect {
							-re "completed" 		  { send_user "DONE" } abort
							-re "Failed dependencies" { send_user "FAILED: Failed dependencies" ; exit -1 }
							-re "Permission denied, please try again"   { send_user "FAILED: Invalid password\n" ; exit -1 }
						}
						send_user "\n"
					}
}
set timeout 40
expect -re "# "
# 
# get the erydb-mysql package
#
send_user "Get erydb-Mysql Connector Package           "
send "smbclient $SHARED -Werydb -Uoamuser%erydb1 -c 'cd Iterations/$RELEASE/;prompt OFF;mget $MYSQLPACKAGE'\n"
expect {
	-re "NT_STATUS_NO_SUCH_FILE" { send_user "WARNING: $MYSQLPACKAGE not found, skipping\n" } abort
	-re "getting"	{ send_user "DONE\n"
						# 
						# send the erydb-mysql package
						#
						expect -re "# "
						send_user "Copy erydb-Mysql Connector Package          "
						send "scp $MYSQLPACKAGE $USERNAME@$SERVER:/root/.\n"
						expect -re "word: "
						# password for ssh
						send "$PASSWORD\n"
						# check return
						expect {
							-re "100%" 						{ send_user "DONE" } abort
							-re "scp"  						{ send_user "FAILED\n" ; 
													send_user "\n*** Installation Failed\n" ; 
													exit -1 }
							-re "Permission denied, please try again"         { send_user "FAILED: Invalid password\n" ; exit -1 }
							-re "No such file or directory" { send_user "FAILED: Invalid package\n" ; exit -1 }
						}
						#
						# install erydb-mysql package
						#
						send_user "\n"
						expect -re "# "
						set timeout 120
						send_user "Install erydb-Mysql Connector Package       "
						send "ssh $USERNAME@$SERVER ' rpm -ivh $MYSQLPACKAGE'\n"
						expect -re "word: "
						# password for ssh
						send "$PASSWORD\n"
						# check return
						expect {
							-re "completed" 		  { send_user "DONE" } abort
							-re "Failed dependencies" { send_user "FAILED: Failed dependencies" ; exit -1 }
							-re "Permission denied, please try again"   { send_user "FAILED: Invalid password\n" ; exit -1 }
						}
						send_user "\n"
					}
}
expect -re "# "
# 
# get the erydb-mysql package
#
send_user "Get erydb-Mysqld Package                    "
send "smbclient $SHARED -Werydb -Uoamuser%erydb1 -c 'cd Iterations/$RELEASE/;prompt OFF;mget $MYSQLDPACKAGE'\n"
expect {
	-re "NT_STATUS_NO_SUCH_FILE" { send_user "WARNING: $MYSQLDPACKAGE not found, skipping\n" } abort
	-re "getting"	{ send_user "DONE\n"
						# 
						# send the erydb-mysql package
						#
						expect -re "# "
						send_user "Copy erydb-Mysqld Package                   "
						send "scp $MYSQLDPACKAGE $USERNAME@$SERVER:.\n"
						expect -re "word: "
						# password for ssh
						send "$PASSWORD\n"
						# check return
						expect {
							-re "100%" 						{ send_user "DONE" } abort
							-re "scp"  						{ send_user "FAILED\n" ; 
													send_user "\n*** Installation Failed\n" ; 
													exit -1 }
							-re "Permission denied, please try again"         { send_user "FAILED: Invalid password\n" ; exit -1 }
							-re "No such file or directory" { send_user "FAILED: Invalid package\n" ; exit -1 }
						}
						#
						# install erydb-mysql-mysqld package
						#
						send_user "\n"
						expect -re "# "
						set timeout 120
						send_user "Install erydb-Mysqld Package                "
						send "ssh $USERNAME@$SERVER ' rpm -ivh $MYSQLDPACKAGE'\n"
						expect -re "word: "
						# password for ssh
						send "$PASSWORD\n"
						# check return
						expect {
							-re "completed" 		  { send_user "DONE" } abort
							-re "Failed dependencies" { send_user "FAILED: Failed dependencies" ; exit -1 }
							-re "Permission denied, please try again"   { send_user "FAILED: Invalid password\n" ; exit -1 }
						}
						send_user "\n"
					}
}
#
exit

