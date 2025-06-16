#!/bin/bash

# Sørg for at scriptet køres som root
if [[ $EUID -ne 0 ]]; then
   echo "Dette script skal køres som root (sudo)." 
   exit 1
fi

# Opret tap0 interfacet
ip tuntap add dev tap0 mode tap user $(whoami)

# Sæt tap0 op
ip link set dev tap0 up

# Tilføj tap0 til broen br0
ip link set dev tap0 master br0

# Tjek status
echo "Interface tap0 er oprettet og tilføjet til br0:"
ip addr show tap0
bridge link show

