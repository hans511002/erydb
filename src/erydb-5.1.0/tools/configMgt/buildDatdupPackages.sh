#! /bin/sh
#
# $1 - release number or 'Latest' (default 'Latest')
if [ "$1" = "" ] ; then
        DIR=Latest
        REL="3.6-0"
elif [ "$1" = "Latest" ] ; then
        DIR=Latest
        REL="3.6-0"
elif [ "$2" = "" ] ; then
        DIR=$1
        REL=$1
else
        DIR=$1
        REL=$2
fi
#
if [[ $REL != *-* ]] ; then
        REL=$REL"-0"
fi
#
{
cd /root/autoOAM/
rpm -e erydb-libs erydb-platform erydb-enterprise --nodeps --allmatches
rpm -e erydb-storage-engine erydb-mysql --nodeps --allmatches
rpm -e erydb-mysql --nodeps --allmatches
rpm -e erydb-datdup --nodeps --allmatches
rm -rf /usr/local/erydb
rm -rf erydb*
rm -f *gz
#
smbclient //eryweb/shared -Werydb -Uroot%erydb1 -c "cd packages/$DIR/packages;prompt OFF;mget erydb-datdup*.rpm"
#
test -f erydb-datdup*.rpm || echo "erydb-datdup rpm"
test -f erydb-datdup*.rpm || exit -1
#
rpm -ivh erydb-datdup*.x86_64.rpm --nodeps
cd /usr/local/
tar -zcvf erydb-datdup-$REL.x86_64.bin.tar.gz erydb
mv erydb-datdup-$REL.x86_64.bin.tar.gz /root/autoOAM/
cd /root/autoOAM/
smbclient //eryweb/shared -Werydb -Uroot%erydb1 -c "cd packages/$DIR/packages;prompt OFF;del erydb-datdup*gz;mput *gz"
} > /root/autoOAM/buildDatdupPackages-$DIR.log 2>&1
#
echo "DatDup Package Build Successfully Completed"
exit 0

