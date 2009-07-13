#!/bin/sh

ARCH=`uname -p`
OUTPUT_FILE=libjfuse-freebsd-${ARCH}.so

g++ -D_FILE_OFFSET_BITS=64 -I/usr/local/include -I/usr/local/diablo-jdk1.6.0/include -I/usr/local/diablo-jdk1.6.0/include/freebsd -L/usr/local/lib -lfuse -Wall -g -o ${OUTPUT_FILE} -shared src/native/*.cpp
