#! bin/bash

#Written by Frederik

#makes comma seperated
sleep_timer=5 # Set this value to the pool interval
loop_count=10 # set this counter to how many samples you want


for i in {1..10}
do
    offset="$(timedatectl timesync-status | grep "Offset")"
    packet_count="$(timedatectl timesync-status | grep "Packet")"
    time="$(date)"
    echo $offset","$packet_count","$time >> stats.csv
    sleep 3
    done

echo "Program is done"

#echo timedatectl timesync-status | grep "Offset" >> file.csv
#echo , >> file.csv
#echo date >> file.csv



