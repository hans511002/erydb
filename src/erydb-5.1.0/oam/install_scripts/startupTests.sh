#!/bin/bash
#
# $Id: startupTests.sh 2937 2012-05-30 18:17:09Z rdempsey $
#
# startupTests - perform sanity testing on system DB at system startup time
#				 called by Process-Monitor

if [ -z "$ERYDB_INSTALL_DIR" ]; then
	test -f /etc/default/erydb && . /etc/default/erydb
fi

if [ -z "$ERYDB_INSTALL_DIR" ]; then
	ERYDB_INSTALL_DIR=/usr/local/erydb
fi

export ERYDB_INSTALL_DIR=$ERYDB_INSTALL_DIR

test -f $ERYDB_INSTALL_DIR/post/functions && . $ERYDB_INSTALL_DIR/post/functions

for testScript in $ERYDB_INSTALL_DIR/post/*.sh; do
	if [ -x $testScript ]; then
		eval $testScript
		rc=$?
		if [ $rc -ne 0 ]; then
			cplogger -c 51 $testScript
			echo "FAILED, check Critical log for additional info"
			exit $rc
		fi
	fi
done
echo "OK"

cplogger -i 54

exit 0

