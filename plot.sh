#!/bin/bash
for file in output/*
do
    cd $file/wild
    gnuplot ../../../makegif.plt
    cd ../../../
    cd $file
    gnuplot ../../mutfig.plt
    cd ../../
done
