#!/bin/bash 
set -e

bindir=`dirname $(readlink -f $0)`

TAP_PATH=`readlink -f $bindir/..`

#echo TAP_PATH = $TAP_PATH

./configure --with-llvmsrc=$TAP_PATH/llvm-3.0.src --with-llvmobj=$TAP_PATH//build  LLVMCC=clang LLVMCXX=clang++ LLVMCC_OPTION=clang  --with-uclibc=$TAP_PATH/uClibc --enable-posix-runtime $@

