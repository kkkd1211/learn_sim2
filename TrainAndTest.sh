#!/bin/bash    
    ./k 0 $1 1 0 1 
    ./k 1 $1 0 1 0
    ./k 2 $1 0 1 0
    ./k 3 $1 0 1 0
    ./k 4 $1 0 1 0
    ./k 5 $1 0 1 0

echo "done$1_`date +%d%m-%H%M`">>README.md
