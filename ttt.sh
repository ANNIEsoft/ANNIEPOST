#!/bin/bash


i="0"

while [ $i -lt 45 ]
do
echo /data/output/DataR328S2p$i.root >files
./main
i=$[$i+1]
done