#! /bin/bash

# HAs to be run as sudo user
# if computer is restart or shut down all of these changes will be removed.

# definings the names
interfaceA=enp4s0f2 # Connect to CCU
# TO see which adapter is which look at the mac-address that is written on the adapter itself.
interfaceB=enx3c18a0243911 # Connect to switch.
interfaceC=enx3c18a0243920 # COnnect to replay attacker.
br=br0

# MAC-adresses of the devices
mac_ccu=a4:ae:11:19:7b:16
mac_consumer=a0:ce:c8:c5:73:61

echo $interfaceA
echo $interfaceB
echo $bridgename


ip link add name $br type bridge
ip link set dev $br up

## add the bridge ports
ip link set $interfaceA up
ip link set $interfaceB up

ip link set dev $interfaceA master $br
ip link set dev $interfaceB master $br
ip link set dev $interfaceC master $br
ip link set dev $br up

# To dissable mac learning and on the bridge port

bridge link set dev $interfaceC  learning off
bridge link set dev $interfaceC  learning_sync off
bridge link set dev $interfaceC  flood off #to prevent unødvendig mac flood

##############
# NOT USED
#############
# To remove all ip-adresses on interfaces can solve some issues
#ip addr del address dev $interfaceA
#ip route del address dev $interfaceB

#ip addr del route dev $interfaceA
#ip route del route dev $interfaceB
