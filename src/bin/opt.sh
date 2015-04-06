bindir=`dirname $(readlink -f $0)`
TAP_PATH="$bindir/.."

MYOPT="-debug -verify-each -std-compile-opts"
MYOPT="-std-compile-opts"
MYOPT="-instnamer -load=/home/chaowang/src/build/Release+Debug+Asserts/lib/LLVMChao.so -chao"

$TAP_PATH/install/bin/opt -S -o $1.opt.ll $MYOPT $1.bc
$TAP_PATH/install/bin/opt    -o $1.opt.bc $MYOPT $1.bc
