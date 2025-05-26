#! /bin/bash

# HAs to be run as sudo user
# if computer is restart or shut down all of these changes will not be removed.


# definings the names of the 3 different interfaces
interfaceA=enp4s0f2 # Ethernet interface on Linux Machine
#interfaceB=enx3c18a0243911 # part of the name is the device's mac address
interfaceC=enx3c18a0243920 # part of the name is the device's mac address
br=br0





### DELAY MAANNN
echo "Delay for interfaces $interfaceA and $InterfaceC have been removed"
#Note if qdics have not been modified on interface, the OS will throw and error and ignore that command.
tc qdisc del dev $interfaceA root 
tc qdisc del dev $interfaceC root 


