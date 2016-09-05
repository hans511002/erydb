#!/bin/bash
. /etc/bashrc
. /funs.sh

hostCount=$1

hostCount=${hostCount:=1}

cd /usr/local/erydb/
initFile="/usr/local/erydb/etc/erdb_init.cfg"
isFirstRun=false
erydbInited=true

isRunedInStart=false
if [ ! -e /usr/local/erydb/data -a ! -e /usr/local/erydb/mysql/db/mysql ] ; then
    erydbInited=false
fi
if [ -f /usr/local/erydb/mysql/bin/libgalera_smm.so ] ; then
    isFirstRun=true
fi
if [ "$hostCount" = "1" ] ; then
    if [ "$isFirstRun" = "true" -o "$erydbInited" = "false" ] ; then
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
    isRunedInStart=true
else
    if [ "$isFirstRun" = "false" -a "$erydbInited" = "true" ] ; then
        rm -rf /var/run/lock/subsys/erydb  /var/run/lock/subsys/mysql-erydb
        /usr/local/erydb/bin/erydb start
        isRunedInStart=true
    fi
fi
sleep 5
ps -ef 

if [ "$isRunedInStart" = "true" ] ; then
    runPid=$(ps -ef|grep /usr/sbin/sshd |grep -v grep |awk '{print $2}')
    if [ "$runPid" = "" ] ; then
        /usr/sbin/sshd -D
    fi
    while [ ! -e  /tmp/StopErydb ] ;  do
      sleep 2
    done
    runPid=$(ps -ef|grep /usr/sbin/sshd |grep -v grep |awk '{print $2}')
    kill -9 $runPid
else
    runPid=$(ps -ef|grep /usr/sbin/sshd |grep -v grep |awk '{print $2}')
    if [ "$runPid" = "" ] ; then
        /usr/sbin/sshd  -D
    fi
    haveConfigs=false
    rm -rf /tmp/StopErydb
    while [ ! -e  /tmp/StopErydb ] ;  do
        sleep 2
        postConfigure=$(ps -ef|grep postConfigure |grep -v grep |awk '{print $2}')
        if [ "$postConfigure" != "" ] ; then
            haveConfigs=true
        fi
    done
    if [ "$haveConfigs" = "true" ] ; then
         while [ -e  /tmp/StopErydb ] ;  do
          sleep 2
        done
        while [ ! -e  /tmp/StopErydb ] ;  do
          sleep 2
        done
    fi

    runPid=$(ps -ef|grep /usr/sbin/sshd |grep -v grep |awk '{print $2}')
    kill -9 $runPid
fi


# gunzip -c erydb-5.0.0.tar.gz |docker load
#docker run --name erydb1 -h erydb1  --network=erydb --ip=172.19.0.2  -d -v /app:/app  -v /app/data/erydb/mysql/1:/usr/local/erydb/mysql/db -v /app/data/erydb/data/1:/usr/local/erydb/data1 -v /app/data/erydb/data/2:/usr/local/erydb/data2 -v /app/data/erydb/data/3:/usr/local/erydb/data3 -v /:/$HOSTNAME --add-host=$HOSTNAME:`ping $HOSTNAME -c 1  -W 1 | grep "icmp_seq" |grep from|sed -e 's|.*(||' -e 's|).*||'`  erydb:5.0.0 3
#docker run --name erydb2 -h erydb2  --network=erydb --ip=172.19.0.3  -d -v /app:/app  -v /app/data/erydb/mysql/2:/usr/local/erydb/mysql/db -v /app/data/erydb/data/1:/usr/local/erydb/data1 -v /app/data/erydb/data/2:/usr/local/erydb/data2 -v /app/data/erydb/data/3:/usr/local/erydb/data3 -v /:/$HOSTNAME --add-host=$HOSTNAME:`ping $HOSTNAME -c 1  -W 1 | grep "icmp_seq" |grep from|sed -e 's|.*(||' -e 's|).*||'`  erydb:5.0.0 3
#docker run --name erydb3 -h erydb3  --network=erydb --ip=172.19.0.4  -d -v /app:/app  -v /app/data/erydb/mysql/3:/usr/local/erydb/mysql/db -v /app/data/erydb/data/1:/usr/local/erydb/data1 -v /app/data/erydb/data/2:/usr/local/erydb/data2 -v /app/data/erydb/data/3:/usr/local/erydb/data3 -v /:/$HOSTNAME --add-host=$HOSTNAME:`ping $HOSTNAME -c 1  -W 1 | grep "icmp_seq" |grep from|sed -e 's|.*(||' -e 's|).*||'`  erydb:5.0.0 3
