bindir=`dirname $(readlink -f $0)`
TAP_PATH="$bindir/.."

$TAP_PATH/bin/clang -emit-llvm $1.c -c -o $1.bc
