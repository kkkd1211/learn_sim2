#!/bin/bash
rm k
g++ code/*.cpp -o k -lm -O2

./k 0 1 1 0 1 
./k 1 1 0 1 0
./k 2 1 0 1 0
./k 3 1 0 1 0
./k 4 1 0 1 0
./k 5 1 0 1 0

sh switch.sh
sh plot.sh


echo "done_`date +%d%m-%H%M`">>README.md
