#!/bin/sh

# Execute like: 
# ./build_and_run template test
#                    |      |
#                    v      v
#                 folder  input

# create build dir if not exists
mkdir ./${1}/build 2> /dev/null

# compile and run
gcc -o ./${1}/build/main ./${1}/src/main.c && ./${1}/build/main ./${1}/input/${2}.txt
