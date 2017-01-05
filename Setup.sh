#!/bin/bash
#Application path location of applicaiton

if [ "$1" = "offline" ]
then

echo "setting up offline"

ToolDAQapp=`pwd`

source ${ToolDAQapp}/ToolDAQ/root/bin/thisroot.sh

export LD_LIBRARY_PATH=${ToolDAQapp}/lib:${ToolDAQapp}/ToolDAQ/zeromq-4.0.7/lib:${ToolDAQapp}/ToolDAQ/boost_1_60_0/install/lib:${ToolDAQapp}/ToolDAQ/root/lib:${ToolDAQapp}/ToolDAQ/libpqxx-4.0.1/install/lib:$LD_LIBRARY_PATH

else

echo "setting up online"

ToolDAQapp=/home/annie/ANNIEDAQ

source ${ToolDAQapp}/ToolDAQ/root/bin/thisroot.sh

export LD_LIBRARY_PATH=`pwd`/lib:${ToolDAQapp}/ToolDAQ/zeromq-4.0.7/lib:${ToolDAQapp}/ToolDAQ/boost_1_60_0/install/lib:${ToolDAQapp}/ToolDAQ/libpqxx-4.0.1/install/lib:$LD_LIBRARY_PATH

fi