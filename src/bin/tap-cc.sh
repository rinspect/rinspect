bindir=`dirname $(readlink -f $0)`
TAP_PATH="$bindir/.."

OPT_FLAG="-instnamer"

$TAP_PATH/install/bin/clang -S -emit-llvm -c -o $1.bc      $1.c
$TAP_PATH/install/bin/clang    -emit-llvm -c -o $1.bc      $1.c

$TAP_PATH/install/bin/opt   -S $OPT_FLAG     -o $1.nam.bc  $1.bc
$TAP_PATH/install/bin/opt      $OPT_FLAG     -o $1.nam.ll  $1.bc

