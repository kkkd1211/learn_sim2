#!/bin/bash
rm k
rm -ri output/*
g++ code/*.cpp -o k -lm -O2
for ((i=0;i<$1;i++))
do
    pkurun-cnlong 1 1 ./TrainAndTest.sh $i
done
#sh switch.sh
#sh plot.sh

