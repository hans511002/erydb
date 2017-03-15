#!/bin/bash
#
# $Id: test-004.sh 1538 2009-07-22 18:57:04Z dhill $

#
# Validates that FilesPerColumnPartition setting is not set lower than existing extents.
#

if [ -z "$ERYDB_INSTALL_DIR" ]; then
	test -f /etc/default/erydb && . /etc/default/erydb
fi

if [ -z "$ERYDB_INSTALL_DIR" ]; then
	ERYDB_INSTALL_DIR=/usr/local/erydb
fi

export ERYDB_INSTALL_DIR=$ERYDB_INSTALL_DIR

test -f $ERYDB_INSTALL_DIR/post/functions && . $ERYDB_INSTALL_DIR/post/functions

scrname=`basename $0`
tname="validate-partition-size"

#Don't run on first boot
if firstboot; then
        exit 0
fi

exit 0

cplogger -i 48 $scrname "$tname"

# Get the FilesPerColumnPartition setting from erydb.xml.
filesPer=$(getConfig ExtentMap FilesPerColumnPartition)

# Get the maximum segment number for all column files.
maxSeg=$(editem -i | awk -F '|' -v max=0 '{if($7>max)max=$7}END{print max+1}')

# Error and out if the maximum existing segment number is higher than the FilesPerColumnPartition setting.
if [ $maxSeg -gt $filesPer ]; then
        cplogger -c 50 $scrname "$tname" "One or more tables were populated with FilesPerColumnPartition higher than the current setting."
        exit 1
fi

cplogger -i 52 $scrname "$tname"

exit 0

