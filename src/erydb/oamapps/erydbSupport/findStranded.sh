#!/bin/sh

#
# This script lists Erydb data files that do not have associated extent map entries.
#
# NOTES:  
# 1) Only looks in $ERYDB_INSTALL_DIR/data* for the data files.
# 2) Only checks for an existing extent with a matching OID, doesn't validate that there is an
#    existing extent for the exact segment.
#
# Close enough for hand grenades.

if [ -z "$ERYDB_INSTALL_DIR" ]; then
	ERYDB_INSTALL_DIR=/usr/local/erydb
fi

export ERYDB_INSTALL_DIR=$ERYDB_INSTALL_DIR

if [ $ERYDB_INSTALL_DIR != "/usr/local/erydb" ]; then
	export PATH=$ERYDB_INSTALL_DIR/bin:$ERYDB_INSTALL_DIR/mysql/bin:/bin:/usr/bin
	export LD_LIBRARY_PATH=$ERYDB_INSTALL_DIR/lib:$ERYDB_INSTALL_DIR/mysql/lib/mysql
fi

cd $ERYDB_INSTALL_DIR

last=-1
existsInExtentMap=0
count=0

for i in $ERYDB_INSTALL_DIR/data*/*/*/*/*/*/FILE*cdf; do
        let count++
        oid=`$ERYDB_INSTALL_DIR/bin/file2oid.pl $i`
	if [ $last -ne $oid ]; then
		last=$oid
        	existsInExtentMap=`$ERYDB_INSTALL_DIR/bin/editem -o $oid | wc -l`
	fi
        if [ $existsInExtentMap -le 0 ]; then
                echo "Missing oid $oid path $i"
        fi
done
