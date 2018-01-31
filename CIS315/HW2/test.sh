#! /bin/bash
start=$(date '+%s')
./a.out < inLarge1.txt
stop=$(date '+%s')
echo $((stop-start))
