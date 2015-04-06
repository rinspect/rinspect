bindir=`dirname $(readlink -f $0)`
TAP_PATH="$bindir/.."

$TAP_PATH/bin/clang -emit-llvm $1.c -S -o $1.ll
