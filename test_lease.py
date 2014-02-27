#!/usr/bin/python

# macgen.py script to generate a MAC address for guests on Xen
import random

def randomMAC():
	mac = [ 0x00, 0x03, 0x50,
		random.randint(0x00, 0x7f),
		random.randint(0x00, 0xff),
		random.randint(0x00, 0xff) ]
	return ':'.join(map(lambda x: "%02x" % x, mac))

def hostname( hostbase , n ):
	host = hostbase + "-" + str(n)
	return host

#
#print randomMAC()
#print hostname("ciao",3)

num = 0
for count in range(1,10):
    cmd = "sudo ./dhtest -m " + randomMAC() + " -h " + hostname("ciao",num) + " 2>&1"
    print cmd
    num += 1


 # TODO non finito


#!/bin/bash

#sudo ./dhtest -m  00:03:50:51:5A:B8 -h host-0 2>&1
#killall dhtest
#sudo ./dhtest -m  00:03:50:E1:8E:84 -h host-1 2>&1
#killall dhtest
#sudo ./dhtest -m  00:03:50:DE:9A:16 -h host-2 2>&1
#killall dhtest
#sudo ./dhtest -m  00:03:50:68:65:30 -h host-3 2>&1
#killall dhtest
