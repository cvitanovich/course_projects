#! /bin/bash
start=$(($(date '+%s%N')/1000000))
./a.out < inRan.txt
stop=$(($(date '+%s%N')/1000000))
echo $((stop-start))
