#! /bin/bash

# HAs to be run as sudo user



# definings the names of the 3 different interfaces
interfaceA=enp4s0f2 # Ethernet interface on Linux Machine
#interfaceB=enx3c18a0243911 # part of the name is the device's mac address
interfaceC=enx3c18a0243920 # part of the name is the device's mac address
br=br0


#Delay variables
delay=800ms
jitter=0ms
packet_loss=30%





### DELAY commands

echo "Delay of $delay and packet loss of $packet_loss implemented"
# Note the delay/packet loss is only implemented on the outgoing interface. So in order to implement the delay both ways, the tc command has to be used on borth interfaces.
tc qdisc replace dev $interfaceA root netem delay $delay loss $packet_loss
tc qdisc replace dev $interfaceC root netem delay $delay loss $packet_loss

# Tmeplate for addning Jittter too (jitter can not be zero)
#tc qdisc replace dev $interfaceC root netem delay $delay $jitter distribution normal loss $packet_loss



