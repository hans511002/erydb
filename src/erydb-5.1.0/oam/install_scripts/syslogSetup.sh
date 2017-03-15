#!/bin/bash
#
# $Id: syslogSetup.sh 421 2007-04-05 15:46:55Z dhill $
#
# syslogSetup.sh - install / uninstall erydb system logging configuration

# no point in going any further if not root... (only works in bash)
test $EUID -eq 0 || exit 0

prefix=/usr/local
installdir=$prefix/erydb
syslog_conf=nofile
rsyslog7=0

for arg in "$@"; do
	if [ `expr -- "$arg" : '--prefix='` -eq 9 ]; then
		prefix="`echo $arg | awk -F= '{print $2}'`"
		installdir=$prefix/erydb
	elif [ `expr -- "$arg" : '--installdir='` -eq 13 ]; then
		installdir="`echo $arg | awk -F= '{print $2}'`"
		prefix=`dirname $installdir`
	elif [ `expr -- "$arg" : '--..*'` -ge 3 ]; then
		echo "ignoring unknown argument: $arg" 1>&2
	elif [ `expr -- "$arg" : '--'` -eq 2 ]; then
		shift
		break
	else
		break
	fi
	shift
done

if [ $installdir != "/usr/local/erydb" ]; then
	export ERYDB_INSTALL_DIR=$installdir
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ERYDB_INSTALL_DIR/lib
fi

erydbSyslogFile=$installdir/bin/erydbSyslog
erydbSyslogFile7=$installdir/bin/erydbSyslog7

checkSyslog() {
#check which syslog daemon is being used
#first check which is running 
daemon="nodaemon"
cnt=`ps -ef | grep -v grep | grep syslog-ng | wc -l`
if [ $cnt -gt 0 ]; then
	daemon="syslog-ng"
else cnt=`ps -ef | grep -v grep | grep rsyslog | wc -l`
	if [ $cnt -ge 1 ]; then
		daemon="rsyslog"
	else cnt=`ps -ef | grep -v grep | grep syslogd | wc -l`
		if [ $cnt -ge 1 ]; then
			if [ "$daemon" != "rsyslog" ]; then
				daemon=syslog
			fi
		fi
	fi
fi

#if none running, check installed
if [ "$daemon" = "nodaemon" ]; then

	if [ -f /etc/syslog.conf ]; then
		daemon="syslog"
		/etc/init.d/syslog start > /dev/null 2>&1
	elif [ -f /etc/rsyslog.conf ]; then
		daemon="rsyslog"
		/etc/init.d/rsyslog start > /dev/null 2>&1
	elif [ -f /etc/init.d/syslog-ng ]; then
		daemon="syslog-ng"
		/etc/init.d/syslog-ng start > /dev/null 2>&1
	fi
fi

#if none running or installed, exit
if [ "$daemon" = "nodaemon" ]; then
	echo ""
	echo "*** No System Logging Application found (syslog, rsyslog, or syslog-ng)"
	echo "*** For Erydb System Logging functionality, install a System Logging package and reinstall erydb"
	echo ""
	exit 1
fi

#check which syslog config file is installed
if [ "$daemon" = "syslog-ng" ]; then
	if [ -f /etc/syslog-ng/syslog-ng.conf ]; then
		syslog_conf=/etc/syslog-ng/syslog-ng.conf
		erydbSyslogFile=$installdir/bin/erydbSyslog-ng
		echo ""
		echo "System logging being used: syslog-ng"
		echo ""
	fi
elif [ "$daemon" = "rsyslog" ]; then
	#check if rsyslog version 7 or greater
	rsyslogd -v > /tmp/rsyslog.ver
	cnt=`grep "rsyslogd 7" /tmp/rsyslog.ver | wc -l`
	if [ $cnt -gt 0 ]; then
		rsyslog7=1
	fi
	cnt=`grep "rsyslogd 8" /tmp/rsyslog.ver | wc -l`
	if [ $cnt -gt 0 ]; then
		rsyslog7=1
	fi
	cnt=`grep "rsyslogd 9" /tmp/rsyslog.ver | wc -l`
	if [ $cnt -gt 0 ]; then
		rsyslog7=1
	fi

	if [ -f /etc/rsyslog.conf ]; then
		cnt=`grep "/etc/rsyslog.d/" /etc/rsyslog.conf | wc -l`
		if [ $cnt -gt 0 ]; then
			if [ $rsyslog7 == 1 ]; then
				syslog_conf=/etc/rsyslog.d/49-erydb.conf
			else
				syslog_conf=/etc/rsyslog.d/erydb.conf
			fi
		else
			syslog_conf=/etc/rsyslog.conf
		fi
		echo ""
		echo "System logging being used: rsyslog"
		echo ""
	fi
elif [ "$daemon" = "syslog" ]; then
	if [ -f /etc/syslog.conf ]; then
		syslog_conf=/etc/syslog.conf
		echo ""
		echo "System logging being used: syslog"
		echo ""
	elif [ -d /etc/syslog-ng/syslog-ng.conf ]; then
		syslog_conf=/etc/syslog-ng/syslog-ng.conf
		erydbSyslogFile=$installdir/bin/erydbSyslog-ng
		echo ""
		echo "System logging being used: syslog-ng"
		echo ""
	fi
else
	echo ""
	echo "*** No System Logging Application found (syslog, rsyslog, or syslog-ng)"
	echo "*** For Erydb System Logging functionality, install a System Logging package and reinstall erydb"
	echo ""
	exit 1
fi

}

install() {
checkSyslog
if [ ! -z "$syslog_conf" ] ; then
	$installdir/bin/setConfig -d Installation SystemLogConfigFile ${syslog_conf} >/dev/null 2>&1
	if [ "$syslog_conf" != /etc/rsyslog.d/erydb.conf ]; then
		rm -f ${syslog_conf}.erydbSave
		cp ${syslog_conf} ${syslog_conf}.erydbSave >/dev/null 2>&1
		sed -i '/# erydb/,$d' ${syslog_conf}.erydbSave > /dev/null 2>&1
	fi

	egrep -qs 'erydb Database Platform Logging' ${syslog_conf}
	if [ $? -ne 0 ]; then
		#set the syslog for erydb logging
		# remove older version incase it was installed by previous build
		rm -rf /etc/rsyslog.d/erydb.conf
		if [ $rsyslog7 == 1 ]; then
			rm -f /etc/rsyslog.d/49-erydb.conf
			cat  ${erydbSyslogFile7} >> ${syslog_conf}
			chown syslog:adm /var/log/erydb
		else
			cat  ${erydbSyslogFile} >> ${syslog_conf}
		fi
	fi

	pkill -hup syslogd > /dev/null 2>&1
	pkill -hup syslog-ng  > /dev/null 2>&1
	pkill -hup rsyslogd  > /dev/null 2>&1
	/etc/init.d/rsyslog restart  > /dev/null 2>&1
	systemctl restart rsyslog.service > /dev/null 2>&1
fi

}

uninstall() {
checkSyslog
if [ ! -z "$syslog_conf" ] ; then
	if [ "$syslog_conf" != /etc/rsyslog.d/erydb.conf ]; then
		if [ "$syslog_conf" != /etc/rsyslog.d/49-erydb.conf ]; then
			egrep -qs 'erydb Database Platform Logging' ${syslog_conf}
			if [ $? -eq 0 ]; then
				if [ -f ${syslog_conf}.erydbSave ] ; then
					#uninstall the syslog for erydb logging
					mv -f ${syslog_conf} ${syslog_conf}.erydbBackup
					mv -f ${syslog_conf}.erydbSave ${syslog_conf} >/dev/null 2>&1
					if [ ! -f ${syslog_conf} ] ; then
						cp ${syslog_conf}.erydbBackup ${syslog_conf}
					fi
				fi
			fi
			sed -i '/# erydb/,$d' ${syslog_conf} > /dev/null 2>&1
		else
			rm -f "$syslog_conf"
		fi
	else
		rm -f "$syslog_conf"
	fi

	pkill -hup syslogd > /dev/null 2>&1
	pkill -hup syslog-ng  > /dev/null 2>&1
	/etc/init.d/rsyslog restart  > /dev/null 2>&1
	systemctl restart rsyslog.service > /dev/null 2>&1

	$installdir/bin/setConfig -d Installation SystemLogConfigFile "unassigned"

fi

}

status() {
checkSyslog
if [ ! -z "$syslog_conf" ] ; then
	egrep -qs 'erydb Database Platform Logging' ${syslog_conf}
	if [ $? -eq 0 ]; then
		echo $syslog_conf
	else
		echo "No System Log Config File configured for EryDB System Logging"
	fi
fi
}

check() {
test -f $installdir/post/functions && . $installdir/post/functions
number=$RANDOM
cplogger -i 104 "EryDB Log Test: $number"
sleep 3
egrep -qs "EryDB Log Test: $number" /var/log/erydb/info.log
if [ $? -eq 0 ]; then
	echo "EryDB System Logging working"
	exit 0
else
	echo "EryDB System Logging not working"
	exit 1
fi
}


case "$1" in
  install)
  	install
	;;
  uninstall)
  	uninstall
	;;
  status)
  	status
	;;
  check)
  	check
	;;
  *)
	echo $"Usage: $0 {install|uninstall|status|check)"
	exit 1
esac


exit 0
/
