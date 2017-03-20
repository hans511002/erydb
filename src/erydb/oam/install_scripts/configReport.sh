#!/bin/bash
#
# $Id: hardwareReport.sh 421 2007-04-05 15:46:55Z dhill $
#
if [ $1 ] ; then
        MODULE=$1
else
        MODULE="pm1"
fi

if [ $2 ] ; then
        INSTALLDIR=$2
else
        INSTALLDIR="/usr/local/erydb"
fi

if [ $USER = "root" ]; then
	SUDO=" "
else
	SUDO="sudo"
fi

$SUDO rm -f /tmp/${MODULE}_configReport.txt

{
echo " "
echo "******************** Configuration/Status Report for ${MODULE} ********************"
echo " "

systemctl=`which systemctl 2>/dev/null`
if [ -n "$systemctl" ]; then
        echo "-- systemctl configuration --"
        echo " "
        echo "################# systemctl list-unit-files --type=service | grep erydb #################"
        echo " "
        $SUDO systemctl list-unit-files --type=service | grep erydb 2>/dev/null
else
  chkconfig=`which chkconfig 2>/dev/null`
  if [ -n "$chkconfig" ]; then
	echo "-- chkconfig configuration --"
	echo " "
	echo "################# chkconfig --list | grep erydb #################"
	echo " "
	$SUDO chkconfig --list | grep erydb 2>/dev/null
  else
    updaterc=`which update-rc.d 2>/dev/null`
    if [ -n "$updaterc" ]; then
	echo "-- services configuration --"
	echo " "
	echo "################# service --status-all | grep erydb #################"
	echo " "
	$SUDO service --status-all | grep erydb 2>/dev/null
   fi
 fi
fi

echo " "
echo "-- fstab Configuration --"
echo " "
echo "################# cat /etc/fstab #################"
echo " "
$SUDO cat /etc/fstab 2>/dev/null

echo " "
echo "-- Server Processes --"
echo " "
echo "################# ps axu #################"
echo " "
$SUDO ps axu

echo " "
echo "-- Server Processes with resource usage --"
echo " "
echo "################# top -b -n 1 #################"
echo " "
$SUDO top -b -n 1

} > /tmp/${MODULE}_configReport.txt

exit 0
