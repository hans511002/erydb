#!/bin/bash
. /etc/bashrc
. /funs.sh

cfgXml=/usr/local/erydb/etc/erydb.xml
HOSTSCFG=`cat $cfgXml|grep  ModuleIPAddr |grep -v unassigned |grep -v "0.0.0.0" |sed -e 's/<\/.*//' -e 's/<.*>//' `
HOSTSCFG=($HOSTSCFG)
HOST_COUNT=${#HOSTSCFG[@]}

if [ "$HOST_COUNT" -le "1" ] ; then
    thisIP=`getHostIPFromPing $HOSTNAME`
    echo "thisIP=$thisIP"
    sed -i -e "s|<IPAddr>.*</IPAddr>|<IPAddr>$thisIP</IPAddr>|" $cfgXml 
    sed -i -e "s|<ModuleIPAddr1-1-3>.*</ModuleIPAddr1-1-3>|<ModuleIPAddr1-1-3>$thisIP</ModuleIPAddr1-1-3>|" \
    -e "s|<ModuleHostName1-1-3>.*</ModuleHostName1-1-3>|<ModuleHostName1-1-3>$HOSTNAME</ModuleHostName1-1-3>|" $cfgXml 
fi

cd /usr/local/erydb/
initFile="/usr/local/erydb/etc/erdb_init.cfg"
erydbInited=true

if [ ! -e /usr/local/erydb/data -a ! -e /usr/local/erydb/mysql/db/mysql ] ; then
    erydbInited=false
fi

if [ "$erydbInited" = "false" ] ; then
    erydbiInitParams=
    if [ -e $initFile ] ; then
        erydbiInitParams=$(cat $initFile)
    fi
    ./bin/postConfigure <<EOF
$erydbiInitParams



















EOF
else
    rm -rf /var/run/lock/subsys/erydb  /var/run/lock/subsys/mysql-erydb
    /usr/local/erydb/bin/erydb start
fi

sleep 5
ps -ef 

 

isRuned=false

echo "start end "
runPid=$(ps -ef|grep /usr/sbin/sshd |grep -v grep |awk '{print $2}')
if [ "$runPid" = "" ] ; then
    /usr/sbin/sshd -D
fi
while [ ! -e  /tmp/StopErydb ] ;  do
    eryStatus=`/usr/local/erydb/bin/erydbConsole getSystemInfo`
    echo "$eryStatus"
    if [ "$isRuned" = "false" ] ; then
        eryStatus=`echo "$eryStatus"|grep System|awk '{print $2}' `
        if [ "$eryStatus" = "ACTIVE" ] ; then
            isRuned=true;
        fi
    elif [ "$isRuned" = "true" ] ; then
        eryStatus=`echo "$eryStatus"|grep System|awk '{print $2}' `
        if [ "$eryStatus" != "ACTIVE" ] ; then
            break
        fi
    fi
    sleep 10
done
runPid=$(ps -ef|grep /usr/sbin/sshd |grep -v grep |awk '{print $2}')
kill -9 $runPid

# gunzip -c erydb-5.0.0.tar.gz |docker load
#docker run --name erydb1 -h erydb1  --network=erydb --ip=172.19.0.2  -d -v /app:/app  -v /app/data/erydb/mysql/1:/usr/local/erydb/mysql/db -v /app/data/erydb/data/1:/usr/local/erydb/data1 -v /app/data/erydb/data/2:/usr/local/erydb/data2 -v /app/data/erydb/data/3:/usr/local/erydb/data3 -v /:/$HOSTNAME --add-host=$HOSTNAME:`ping $HOSTNAME -c 1  -W 1 | grep "icmp_seq" |grep from|sed -e 's|.*(||' -e 's|).*||'`  erydb:5.0.0 3
#docker run --name erydb2 -h erydb2  --network=erydb --ip=172.19.0.3  -d -v /app:/app  -v /app/data/erydb/mysql/2:/usr/local/erydb/mysql/db -v /app/data/erydb/data/1:/usr/local/erydb/data1 -v /app/data/erydb/data/2:/usr/local/erydb/data2 -v /app/data/erydb/data/3:/usr/local/erydb/data3 -v /:/$HOSTNAME --add-host=$HOSTNAME:`ping $HOSTNAME -c 1  -W 1 | grep "icmp_seq" |grep from|sed -e 's|.*(||' -e 's|).*||'`  erydb:5.0.0 3
#docker run --name erydb3 -h erydb3  --network=erydb --ip=172.19.0.4  -d -v /app:/app  -v /app/data/erydb/mysql/3:/usr/local/erydb/mysql/db -v /app/data/erydb/data/1:/usr/local/erydb/data1 -v /app/data/erydb/data/2:/usr/local/erydb/data2 -v /app/data/erydb/data/3:/usr/local/erydb/data3 -v /:/$HOSTNAME --add-host=$HOSTNAME:`ping $HOSTNAME -c 1  -W 1 | grep "icmp_seq" |grep from|sed -e 's|.*(||' -e 's|).*||'`  erydb:5.0.0 3
