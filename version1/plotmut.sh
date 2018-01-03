#!/bin/bash
rm ./mut/*/*_P.txt
sh switch_R_C_mut.sh
gnuplot mutfig.plt
