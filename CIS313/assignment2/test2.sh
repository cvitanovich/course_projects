#! /bin/bash
T0=$(date +%n)
python problem2-2.py problem2.input
sleep 5
T1=$(date +%n)
echo $((T1-T0))
