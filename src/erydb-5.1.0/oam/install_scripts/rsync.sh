#!/usr/bin/expect
#
# $Id: rsync.sh 2915 2012-05-23 16:01:34Z dhill $
#
# Remote Install RPM and custom OS files from postConfigure script
# Argument 1 - Remote Server Host Name or IP address
# Argument 2 - Root Password of remote server
# Argument 3 - Debug flag 1 for on, 0 for off
set USERNAME "root@"
set SERVER [lindex $argv 0]
set PASSWORD [lindex $argv 1]
set INSTALLDIR [lindex $argv 2]
set DEBUG 0
set DEBUG [lindex $argv 3]
log_user $DEBUG
spawn -noecho /bin/bash


if { $PASSWORD == "ssh" } {
	set USERNAME ""
	set PASSWORD ""
}

set COMMAND "rsync -vopgr -e ssh --exclude=mysql/ --exclude=test/ --exclude=erydb_vtable/ --exclude=erydb_querystats/ --exclude=erydbsys/ --include=*/ --include=*/* --exclude=* $INSTALLDIR/mysql/db/ $USERNAME$SERVER:$INSTALLDIR/mysql/db/"

#
# run command
#
set timeout 60
send "$COMMAND\n"
expect {
	-re "Host key verification failed" { send_user "FAILED: Host key verification failed\n" ; exit -1}
	-re "service not known"    { send_user "           FAILED: Invalid Host\n" ; exit -1}
	-re "ssh: connect to host" { send_user "           FAILED: Invalid Host\n" ; exit -1 }
	-re "authenticity" { send "yes\n" 
						 expect {
						 	-re "word: " { send "$PASSWORD\n" }
							-re "passphrase" { send "$PASSWORD\n" }
						 }
	}
	-re "word: " { send "$PASSWORD\n" }
	-re "passphrase" { send "$PASSWORD\n" }
	-re "failed" { send_user "           FAILED: Failure, check tmp log\n" ; exit 1 }
	-re "Permission denied" { send_user "           FAILED: Invalid password\n" ; exit 1 }
	-re "total size" { exit 0 }
}
expect {
	-re "failed" { send_user "           FAILED: Failure, check tmp log\n" ; exit 1 }
	-re "Permission denied" { send_user "           FAILED: Invalid password\n" ; exit 1 }
	-re "total size" { exit 0 }
	}
}

exit 0
