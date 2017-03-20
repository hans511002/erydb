#! /bin/sh
#
#$1 = testRunID
#
host=`hostname -s`
smbclient //calweb/perf -Werydb -Uoamuser%erydb1 -D "/results/${host}" -c "lcd /root/genii/testResult;recurse;prompt OFF;mput $1"
