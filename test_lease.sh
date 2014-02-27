#!/bin/bash

# Author Simone Cianni <simone.cianni@bticino.it>

#
# use : test_lease.sh [ncycle] [hostnamebase]
#

ncycle=$1
hostbase=$2
#..=$3

if [ ! $1 ]; then
	ncycle=1
fi

if [ ! $2 ]; then
	hostbase=host
fi

function randomMAC()
{
	LC_CTYPE=C
	local MAC=00:03:50 #bticino
	for i in {1..3}
	do
	IFS= read -d '' -r -n 1 char < /dev/urandom
	MAC+=$(printf -- ':%02x\n' "'$char")
	done
	#printf '%s\n' "$MAC"
	echo $MAC
}

function hosts() {
	echo $1-$2
}

for (( i=1; i<=$ncycle; i++ ))
do
	echo -e "\n Execute $i times \n"
	sudo ./dhtest -m $(randomMAC) -h $(hosts $hostbase $i) 2>&1
	killall dhtest
done

#sudo ./dhtest -m  00:03:50:51:5A:B8 -h host-0 2>&1
#killall dhtest
#sudo ./dhtest -m  00:03:50:E1:8E:84 -h host-1 2>&1
#killall dhtest

