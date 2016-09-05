#!/bin/bash
. /etc/bashrc
nohup /erydb.sh "$@" 2>&1 >&1 &
/usr/sbin/sshd -D
