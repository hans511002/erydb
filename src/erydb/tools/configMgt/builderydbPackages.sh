#! /bin/sh
#
# $1 - release number or 'Latest' (default 'Latest')
#
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
rpm -e erydb-libs erydb-platform erydb-enterprise --nodeps
rpm -e erydb-storage-engine erydb-mysql --nodeps
rpm -e erydb-mysql --nodeps
rm -rf /usr/local/erydb
rm -rf erydb*
rm -f *gz
#
smbclient //eryweb/shared -Werydb -Uroot%erydb1 -c "cd packages/$DIR;prompt OFF;mget *.rpm"
rpm -ivh erydb*.x86_64.rpm --nodeps
rpm -iq erydb >> /usr/local/erydb/releasenum
cd /usr/local/
tar -zcvf erydb-erydb-ent-$REL.x86_64.bin.tar.gz erydb
mv erydb-erydb-ent-$REL.x86_64.bin.tar.gz /root/autoOAM/
cd /root/autoOAM/
alien -ck erydb*.x86_64.rpm
tar -zcvf erydb-erydb-ent-$REL.x86_64.rpm.tar.gz *$REL*.rpm
tar -zcvf erydb-erydb-ent-$REL.amd64.deb.tar.gz *$REL*.deb

smbclient //eryweb/shared -Werydb -Uroot%erydb1 -c "cd packages/$DIR;mkdir packages;cd packages;prompt OFF;del erydb-erydb-ent*gz;mput *gz"
} > /root/autoOAM/builderydbPackages-$DIR.log 2>&1
#
echo "erydb Packages Build Successfully Completed"
exit 0

