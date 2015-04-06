#!/bin/bash -x
set -e

bindir=`dirname $(readlink -f $0)`

TAP_PATH=`readlink -f $bindir/..`

#echo TAP_PATH = $TAP_PATH

$TAP_PATH/llvm-3.2.src/configure CC=gcc CXX=g++ --prefix=$TAP_PATH/install-3.2  --with-llvmsrc=$TAP_PATH/llvm-3.2.src --with-llvmobj=$TAP_PATH/build-3.2 --enable-shared --enable-optimized --enable-debug-symbols --enable-assertions

