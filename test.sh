#! /bin/bash

for file in `ls RAW*`
do
nfile=`echo $file | sed s:RAW::`
echo $file and $nfile
mv $file $nfile
done