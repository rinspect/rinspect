#Tool Description
Rinspect is a tool which builds upon the popular Clang/LLVM compiler
framework for handling C code written for the Linux/PThreads
platform. It could support SC-MODE, TSO-MODE AND PSO-MODE. If test
programs has loop, it should have bounded.

#testing version
Thie version is tested on Linux 32bit machine.
MAKEFILE CHANGES, PATH AND INSPCC
BENCHMARKS PACKAGE CHANGES
CHANGE README, TESTING MACHINE


## Requirements
Download the project source code from : https://github.com/Rinspect
which contains:
llvm-3.0.src (LLVM, Clang, TAP, …)

bin (where you store the shell scripts)

build (where you will build LLVM, …)

install (where you will install LLVM, …)

test (where you will test LLVM, …)

inspect-0.3 (Inspect tool from Univ. Utah, modified version from RSS group)

clap (runtime monitor code)

smtdp

yicese-1.0.28



### LLVM Installation

The tool was developed and tested using LLVM 3.2. The source code for LLVM 3.2 can be downloaded here: http://llvm.org/releases/3.2/llvm-3.2.src.tar.gz .

Compile smt_dp:
cd src/build
../bin/config_llvm3.sh;
make;make install;

Compile clap:
cd src/clap;make


### Compile Rinspect
cd src/inspect;
make clean;
make;

### Compile target program

../bin/inspcc -o target ../*.c


##Usage

./inspect -h ; # show the command
./inspect ./target; #running under SC-MODE
./inspect --tso-mode ./target; #running under TSO-MODE
./inspect --pso-mode ./target; #running under PSO-MODE

e.g.:
../bin/inspcc -o target Benchmarks/TestToy/relaxer_tso.c
./inspect ./target; #under SC, you will get 3 runs
./inspect --tso-mode ./target; #uner TSO, you will get 4 runs



## Bugs Report
Welcome to send email to: naling@vt.edu



#Benchmarks Description

It containts two parts: one is from SV-COMP, the other is from
WMM. This includes a Makefile to automatically run the testing set.



## SV-COMP benchmarks for Rinspect
### Introduction
    At this part, test programs are mostly low level program and
    use less lock/mutex-lock. They usually have share-memory
    variable. So we would like to find out what is happening under
    relax memory model and find potential reduction.
    Expected result is shown on time.

### Atomic programs
    1.Centralized-sense-arw 
    2.CLHQueue-arw	
    3.Atomic01.c

### SV-comp and WMM
    1. DekkerSafe 
    2. LamportSafe 
    3. PetersonSafe
    4. DijkstraSafe
    5. SyzmanskiSafe
    6. Pgsql_two
    7. Pgsql_two_develope
    8. Sober
    9. Sober_fix
    10.Sync01_true 
    11.StackSafe 
    12.StackUnsafe 
    13.Stateful01_false 
    14.Stateful01_true 


## Litmus for Rinspect
121 small programs, including litmus tests for X86 TSO/PSO, standard
c prgrams, which come from
http://www.cprover.org/wmm/esop13/experiments.shtml.




## Usage
1. move fold regression-examples to src/examples/tso
    mv -r regression-examples examples/tso/.
2. go to directory tso, use cmd to run this test set:
    make clean;make check; #


