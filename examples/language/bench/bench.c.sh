#!/bin/bash
echo     "  "  time ./bench 1000000000
time                 ./bench 1000000000
echo -n     "1.8 * 1000000 / 1000000000 = "
echo    "scale=6 ; 1000000 / 1000000000" | bc
echo " microseconds"
