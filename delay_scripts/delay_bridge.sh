#! /bin/bash

# HAs to be run as sudo user
# if computer is restart or shut down all of these changes will be removed.


# definings the names of the 3 different interfaces
interfaceA=enp4s0f2 # Ethernet interface on Linux Machine
#interfaceB=enx3c18a0243911 # part of the name is the device's mac address
interfaceC=enx3c18a0243920 # part of the name is the device's mac address
br=br0

# MAC-adresses of the devices
mac_ccu=a4:ae:11:19:7b:16
mac_consumer=a0:ce:c8:c5:73:61




ip link add name $br type bridge
ip link set dev $br up

## add the bridge ports
ip link set $interfaceA up
#ip link set $interfaceB up

ip link set dev $interfaceA master $br
#ip link set dev $interfaceB master $br
ip link set dev $interfaceC master $br
ip link set dev $br up





