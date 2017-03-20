#!/bin/bash
#
# configxml	set/get an entry in erydb.xml file
#
#

if [ -z "$ERYDB_INSTALL_DIR" ]; then
	test -f /etc/default/erydb && . /etc/default/erydb
fi

if [ -z "$ERYDB_INSTALL_DIR" ]; then
	ERYDB_INSTALL_DIR=/usr/local/erydb
fi

export ERYDB_INSTALL_DIR=$ERYDB_INSTALL_DIR

InstallDir=$ERYDB_INSTALL_DIR

if [ $InstallDir != "/usr/local/erydb" ]; then
	export PATH=$InstallDir/bin:$InstallDir/mysql/bin:/bin:/usr/bin
	export LD_LIBRARY_PATH=$InstallDir/lib:$InstallDir/mysql/lib/mysql
fi

case "$1" in
 setconfig)

	if [ $# -ne 4 ]; then 
		echo $"Usage: $0 setconfig section variable set-value"
		exit 1
	fi

	oldvalue=$($InstallDir/bin/getConfig $2 $3)

	#if [ -z $oldvalue ]; then 
	#	echo "$2 / $3 not found in erydb.xml"	
	#	exit 1
	#fi

	echo "Old value of $2 / $3 is $oldvalue"

	calxml=$InstallDir/etc/erydb.xml

	seconds=$(date +%s)
	cp $calxml $calxml.$seconds
	echo
	echo "$calxml backed up to $calxml.$seconds"
	echo

	oldvalue=$($InstallDir/bin/getConfig $2 $3)

	echo "Old value of $2 / $3 is $oldvalue"

	if ( [ $# -eq 4 ] && [ -z $4 ] ); then
		$InstallDir/bin/setConfig $2 $3 ""
	else
		$InstallDir/bin/setConfig $2 $3 $4
	fi

	newvalue=$($InstallDir/bin/getConfig $2 $3)

	echo "$2 / $3 now set to $newvalue"
	;;
 
 getconfig)
	if  test ! $3 ; then 
		echo $"Usage: $0 getconfig section variable"
		exit 1
	fi

	value=$($InstallDir/bin/getConfig $2 $3)

	if [ -z $value ]; then 
		echo "$2 / $3 not found in erydb.xml"	
		exit 1
	fi

	echo "Current value of $2 / $3 is $value"	
	;;
 
 *)
	echo $"Usage: $0 {setconfig|getconfig} section variable set-value"
	exit 1

esac
# vim:ts=4 sw=4:

