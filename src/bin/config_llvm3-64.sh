#!/bin/bash -x
set -e

bindir=`dirname $(readlink -f $0)`

TAP_PATH=`readlink -f $bindir/..`

#echo TAP_PATH = $TAP_PATH

$TAP_PATH/llvm-3.0.src/configure CC=gcc CXX=g++ --prefix=$TAP_PATH/install  --with-llvmsrc=$TAP_PATH/llvm-3.0.src --with-llvmobj=$TAP_PATH/build --enable-shared --enable-optimized --enable-debug-symbols --enable-assertions

if [ ! -d "$TAP_PATH/build/Release+Debug+Asserts" ];
then 
    mkdir $TAP_PATH/build/Release+Debug+Asserts
fi

if [ ! -d "$TAP_PATH/build/Release+Debug+Asserts/lib" ];
then
    mkdir $TAP_PATH/build/Release+Debug+Asserts/lib
fi

