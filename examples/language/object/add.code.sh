#!/bin/bash
echo add.c:
cat add.c
gcc -c add.c
echo objdump -d add.o
objdump -d add.o
