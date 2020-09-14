#!/bin/bash

contest=$1
curDir="/home/denjo/kyopro/AtCoder"

if [ ${contest:0:3} = "abc" ]; then
    dir="${curDir}/ABC/${contest}"
elif [ ${contest:0:3} = "arc" ]; then
    dir="${curDir}/ARC/${contest}"
elif [ ${contest:0:3} = "agc" ]; then
    dir="${curDir}/AGC/${contest}"
else
    dir="${curDir}/others/${contest}"
fi

mkdir $dir

touch "${dir}"/{a,b,c,d,e,f}.cpp
code "${dir}"/{a,b,c,d,e,f}.cpp
