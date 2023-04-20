#!/bin/bash
echo   time python3 bench.py 100000000 
time        python3 bench.py 100000000 
echo -n  "       10 * 1000000 / 100000000 = "
echo    "scale=6 ; 1000000 / 100000000" | bc
echo " microseconds"
