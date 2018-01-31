#!/bin/bash
cp para/k.txt para/k_old.txt
cp para/v.txt para/v_old.txt
cp para/training_data.txt para/training_data_old.txt
g++ *.cpp -o k -lm -O2
rm ./output/*.txt
rm ./output/*.png
rm ./output/*.gif
./k 1
./k 2
./k 3
./k 4
./k 5
./k 0
sh switch_R_C.sh
gnuplot makegif.plt
echo "done_`date +%d%m-%H%M`">>README.md
