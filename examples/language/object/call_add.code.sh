#!/bin/bash
echo
echo add.c:
cat add.c
gcc -c add.c -o add.o
echo
echo objdump -d add.o
objdump -d add.o
echo
echo call_add.c:
cat call_add.c
gcc -c call_add.c -o call_add.o
echo
echo objdump -d call_add.o
objdump -d call_add.o
gcc -o call_add call_add.o add.o
echo
echo objdump -d call_add
objdump -d call_add
