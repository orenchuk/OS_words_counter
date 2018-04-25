#!/bin/bash
N=5
rm res.txt
for i in $(seq 1 $N)
do
    ./counter >>  res.txt
done
