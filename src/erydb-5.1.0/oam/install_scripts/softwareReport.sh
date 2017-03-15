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

$SUDO rm -f /tmp/${MODULE}_softwareReport.txt

{
echo " "
echo "******************** Software Report for ${MODULE} ********************"
echo " "

echo " "
echo "-- Erydb Package Details --"
echo " "
echo "################# erydbConsole geterydbsoftwareinfo #################"
echo " "
$INSTALLDIR/bin/erydbConsole getsoftwareinfo

if [ -e $INSTALLDIR/releasenum ];then
  echo " "
  echo "-- Erydb Release Number file --"
  echo " "
  echo "################# cat $INSTALLDIR/releasenum #################"
  echo " "
  cat $INSTALLDIR/releasenum
fi

echo " "
echo "-- Erydb Storage Configuration --"
echo " "
echo "################# erydbConsole getStorageConfig #################"
echo " "
$INSTALLDIR/bin/erydbConsole getStorageConfig

} > /tmp/${MODULE}_softwareReport.txt

exit 0
