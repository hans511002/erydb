#! /bin/sh
#

version=$1
OS=x86_64

cd /home/nightly/rpm/ > /dev/null 2>&1
cd RPMS/$OS/ > /dev/null 2>&1
test -f erydb-plafform-$version*.rpm || echo "no rpm"
test -f  erydb-plafform-$version*.rpm || exit -1
rpm -qi -p  erydb-plafform-$version*.rpm >  erydb-plafform-$OS-rpm-info.txt
echo " " >>  erydb-plafform-$OS-rpm-info.txt
echo "MD5SUM" >>  erydb-plafform-$OS-rpm-info.txt
md5sum  erydb-plafform-$version*.rpm >>  erydb-plafform-$OS-rpm-info.txt
echo " " >>  erydb-plafform-$OS-rpm-info.txt
#
test -f erydb-storage-engine-*.rpm || echo "no rpm"
test -f  erydb-storage-engine-*.rpm || exit -1
rpm -qi -p  erydb-storage-engine-*.rpm >  erydb-storage-engine-$OS-rpm-info.txt
echo " " >>  erydb-storage-engine-$OS-rpm-info.txt
echo "MD5SUM" >>  erydb-storage-engine-$OS-rpm-info.txt
md5sum  erydb-storage-engine-*.rpm >>  erydb-storage-engine-$OS-rpm-info.txt
echo " " >>  erydb-storage-engine-$OS-rpm-info.txt
#
test -f erydb-mysql-*.rpm || echo "no rpm"
test -f  erydb-mysql-*.rpm || exit -1
rpm -qi -p  erydb-mysql-*.rpm >  erydb-mysql-$OS-rpm-info.txt
echo " " >>  erydb-mysql-$OS-rpm-info.txt
echo "MD5SUM" >>  erydb-mysql-$OS-rpm-info.txt
md5sum  erydb-mysql-*.rpm >>  erydb-mysql-$OS-rpm-info.txt
echo " " >>  erydb-mysql-$OS-rpm-info.txt
#
