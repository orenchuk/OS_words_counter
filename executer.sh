#!/bin/bash
#N=5
#N=$@

rm res.txt
#for i in $(seq 1 $N)
for i in 1 2 4 8
do
    ./counter $i >>  res.txt
done
