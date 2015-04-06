bindir=`dirname $(readlink -f $0)`
TAP_PATH="$bindir/.."

$TAP_PATH/install/bin/clang -S -emit-llvm -c -o $1.bc      $1.c
$TAP_PATH/install/bin/clang    -emit-llvm -c -o $1.bc      $1.c


