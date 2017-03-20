#!/bin/bash
#
# $Id: test-003.sh 2937 2012-05-30 18:17:09Z rdempsey $

if [ -z "$ERYDB_INSTALL_DIR" ]; then
	test -f /etc/default/erydb && . /etc/default/erydb
fi

if [ -z "$ERYDB_INSTALL_DIR" ]; then
	ERYDB_INSTALL_DIR=/usr/local/erydb
fi

export ERYDB_INSTALL_DIR=$ERYDB_INSTALL_DIR

test -f $ERYDB_INSTALL_DIR/post/functions && . $ERYDB_INSTALL_DIR/post/functions

scrname=`basename $0`
tname="check-oid-bitmap"

#Don't run on first boot
if firstboot; then
	exit 0
fi

#Make sure there is an oid bitmap file if there are any EM entries

cplogger -i 48 $scrname "$tname"

obmfile=$(getConfig OIDManager OERYDBitmapFile)
emcnt=$(editem -o 2001 | wc -l)

rc=1
if [ -f $obmfile -o $emcnt -eq 0 ]; then
	rc=0
fi

if [ $rc -ne 0 ]; then
	cplogger -c 50 $scrname "$tname" "there is no OID bitmap file but there are Extent Map entires"
	exit 1
fi

cplogger -i 52 $scrname "$tname"

exit 0

