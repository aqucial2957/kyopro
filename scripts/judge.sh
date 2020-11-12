#!/bin/bash

if [ $# -ne 1 ]; then
    echo "error: missing argument"
    echo "Usage: j problem" 1>&2
    exit 1
fi

problem=$1
contest=${problem%_*}
suffix=${problem##*_}

kprDir=$(dirname $(cd $(dirname $0); pwd))
curDir="$kprDir/AtCoder"

if [ ${contest:0:3} = "abc" ]; then
    dir="${curDir}/ABC"
elif [ ${contest:0:3} = "arc" ]; then
    dir="${curDir}/ARC"
elif [ ${contest:0:3} = "agc" ]; then
    dir="${curDir}/AGC"
else
    dir="${curDir}/others"
fi

path="${dir}/${contest}/${suffix}.cpp"
url="https://atcoder.jp/contests/${contest}/tasks/${problem//-/_}"

#test
oj d $url
g++ -std=gnu++17 -Wall -Wextra -O2 $path
oj t

#submit if succeeded all testcases
if [ $? -eq 0 ]; then
    oj s -y -w 0 $url $path
fi

rm -f a.out
rm -rf test