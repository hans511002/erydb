#!/usr/bin/env bash
#

trim(){
echo "$1" | grep -o "[^ ]\+\( \+[^ ]\+\)*"
}

testHostNmap(){
    type=`nmap $1 -p 22 --max-rtt-timeout 30ms  |grep 22/tcp |awk '{print $2}'`
    if [ "$type" = "open" -o  "$type" = "filtered" ] ; then
        echo "true"
    else   
        echo "false"
    fi
}

getHostIPFromPing(){
    thisIP=$(ping $1 -c 1  -W 1 | grep "icmp_seq" |grep from|sed -e 's|.*(||' -e 's|).*||') 
    if [ "$thisIP" = "" ] ; then
        thisIP=$(ping $1 -c 1 -W 1 | grep "bytes of data" |awk  '{print $3}'|sed -e 's|.*(||' -e 's|).*||')
    fi
    echo "$thisIP"
}

#返回昨天日期
get_before_dates()
{
 yyyymmdd=$1
 num=$2
 for ((i=0;i<num;i=i+1))
do
  yyyymmdd=`get_before_date $yyyymmdd`
done

 echo $yyyymmdd
}

#返回昨天日期
get_before_date()
{
	Y=`expr substr $1 1 4`
	M=`expr substr $1 5 2`
	D=`expr substr $1 7 2`
	YY=`expr $Y - 1`
	MM=`expr $M - 1`
	DD=`expr $D - 1`
	MM=`printf "%02d" $MM`
	DD=`printf "%02d" $DD`
	dd=$Y$MM
	dad=`get_mon_days $dd`
	be_date=$Y$M$DD
    if [ "$D" == "01" ] ; then
		if [ $M -ne 01 ]
		then
			be_date=$Y$MM$dad
		else
			be_date=$YY"1231"
		fi
	fi
	echo $be_date
}
get_next_date()
{
	Y=`expr substr $1 1 4`
	M=`expr substr $1 5 2`
	D=`expr substr $1 7 2`
	YY=`expr $Y + 1`
	MM=`expr $M + 1`
	DD=`expr $D + 1`
	MM=`printf "%02d" $MM`
	DD=`printf "%02d" $DD`
	dd=$Y$M
	dad=`get_mon_days $dd`
	be_date=$Y$M$DD
    if [ "$D" == "$dad" ] ; then
		if [ $M -ne 12 ]
		then
			be_date=$Y$MM"01"
		else
			be_date=$YY"0101"
		fi
	fi
	echo $be_date
}
get_before_month()
{
	Y=`echo $1|cut -c 1-4`
	M=`echo $1|cut -c 5-6`
	D=01
	day=$Y$M$D
	day=`get_before_date $day`
	before_month=`echo $day|cut -c 1-6`
	echo $before_month
}
get_mon_days()
{
    Y=`expr substr $1 1 4`
	M=`expr substr $1 5 2`
	case $M in
    01|03|05|07|08|10|12)
      dd=31 ;;
   04|06|09|11)
      dd=30 ;;
    *)
    if [ $((Y%4)) -eq 0 ] ; then
	   dd=29
	else
	   dd=28
	fi
    ;;
  esac
echo $dd
}

#返回月份的天数
get_mon_days()
{
	Y=`expr substr $1 1 4`
	M=`expr substr $1 5 2`
	r1=`expr $Y \% 4`
	r2=`expr $Y \% 100`
	r3=`expr $Y \% 400`

	case $M in
	01|03|05|07|08|10|12) days=31;;
	04|06|09|11) days=30;;
	esac
	if [ $M -eq 02 ]
	then
        if [ r1 -eq 0 -a r2 -ne 0 -o r3 -eq 0 ]
        then
                days=29
        else
                days=28
        fi
	fi
	echo $days
}
 
#返回下月
get_next_month()
{
	Y=`echo $1|cut -c 1-4`
	M=`echo $1|cut -c 5-6`
	D=`get_mon_days $Y$M"01"`
	day=$1$D
	day=`get_next_date $day`
	next_month=`echo $day|cut -c 1-6`
	echo $next_month
}

#返回前几个月
get_before_months()
{
	loop=1
	month_no=$1
	while [ $loop -lt $2 ] || [ $loop -eq $2 ]
	do
		month_no=`get_before_month $month_no`
		loop=`expr $loop + 1`
	done
	
	echo $month_no
}

#返回后几个月
get_next_months()
{
	loop=1
	month_no=$1
	while [ $loop -lt $2 ] || [ $loop -eq $2 ]
	do
		month_no=`get_next_month $month_no`
		loop=`expr $loop + 1`
	done
	
	echo $month_no
}

cmpVersion(){
	v1=$1
	v2=$2
	v1=${v1//./ }
	v2=${v2//./ }
	V1=($v1)
	V2=($v2)
	l1=${#V1[@]}
	l2=${#V2[@]}
	len=0
	while true ;  do
	  v1=-1
	  v2=-1
	  if [ "$l1" -gt "$len" ] ; then
	  	v1=${V1[$len]}
	  fi
	  if [ "$l2" -gt "$len" ] ; then
	  	v2=${V2[$len]}
	  fi
	  #echo "v1=$v1  v2=$v2  l1=$l1 l2=$l2"
	  ((len++))
		if  [ "$v1" -eq "-1" -a "$v2" -eq "-1" ] ; then   # (v1 == -1 && v2 == -1) {
				echo 0
				break
		elif [ "$v1" -gt "-1" -a "$v2" -eq "-1" ] ; then #  (v1 > -1 && v2 == -1) {
				if [ "$v1" = "0" ] ; then
					continue
				fi
				echo "1" 
				break
		elif [ "$v1" -eq "-1" -a "$v2" -gt "-1" ] ; then #  (v1 == -1 && v2 > -1) {
				if [ "$v2" = "0" ] ; then
					continue
				fi
				echo "-1" 
				break
		else
				if [ "$v1" -gt "$v2" ] ; then
					echo "1"
					break
				elif [ "$v1" -lt "$v2" ] ; then
				   echo "-1"
					 break
			  else
			  	 continue
				fi 
		fi
	done
}
