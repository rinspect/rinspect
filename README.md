Rinspect is a tool which builds upon the popular Clang/LLVM compiler framework for handling C code written for the Linux/PThreads platform. It could support sequential memory model, total store order memory model and partial store order memory order. If test programs has loop, it should have bounded.


# Architecture
Rinspect is based on the inspect project developed by Formal VerIfication Group in Utah University. It adapts the same server/client architecture. Basically, this project ships with a modified LLVM to compile/instruct the to-be-verified source code with additional components. The to-be-verified program is then able to communicate with the verifying program called scheduler through Unix-domain socket. The scheduler controls execution traces and collects execution history of the to-be-tested program through the this communication channel. Then using the algorithm we develop on PLDI 2015, the scheduler is able to report bugs of the being-verified source code caused by relaxed memory model.

## Project directory structure

* src
    * bin
    * clap
    * inspect-0.3 (our main source code)
    * llvm-3.0.src (modified LLVM)
    * smt_dp
    * yices-1.0.28
    * examples
* benchmarks
    * regression-examples
        * SV-comp
        * Litmus

# Installation


Download the project source code from [https://github.com/nana1904/rinspect/](https://github.com/nana1904/rinspect/)

All the following steps are only tested on a Linux Mint LMDE 32-bit machine. They are likely to work on Ubuntu 32-bit systems or other Linux systems, but not guaranteed. OS X system probably not be able to compile this program, but if you try, please report any problems to us.

## Compile the included LLVM
Compiling LLVM will take half to one hour. Please be patient.

Before compiling LLVM, make sure that you compile smt_dp first:
```sh
cd src/smt_dp
make
```

Then compile LLVM:
``` sh
mkdir build                     # in src 
cd build
../bin/config_llvm3.sh
make
make install                   # the executable files will be installed in src/install/bin
```

## Compile clap:

```sh
cd src/clap
make
```

### Compile rinspect

```sh
cd src/inspect-0.3
make clean
make
```


# Usage
The first step to use this program is to compile the to-be-verified code, hereafter we call it target program.

## Compile target program
```sh
../bin/inspcc -o target ../*.c         # use the shell script at src/bin to compile the target program
```

## Usage examples
Our executable program is in src/inspect-0.3, called inspect. Following are some usage examples.

```sh
./inspect -h                                  # show help information
./inspect ./target                          # running under sequential memory model
./inspect --tso-mode ./target        # running under total store order memory model
./inspect --pso-mode ./target       # running under partial store order memory model
```

e.g.:

```sh
../bin/inspcc -o target examples/regression-examples/TestToy/relaxer_tso.c
./inspect ./target                              # under SC, you will get 3 runs
./inspect --tso-mode ./target           # under TSO, you will get 4 runs
```

# Benchmarks
We use two sets of benchmark codes from SV-COMP, WMM/Litmus.

## SV-COMP and WMM benchmarks
SV-COMP benchmarks are mostly low level programs which use less lock/mutex-lock, and usually have share-memory variable.

    1. DekkerSafe 
    2. LamportSafe 
    3. PetersonSafe
    4. DijkstraSafe
    5. SyzmanskiSafe
    6. Pgsql_two
    7. Pgsql_two_developer
    8. Sober
    9. Sober_fix
    10.Sync01_true 
    11.StackSafe 
    12.StackUnsafe 
    13.Stateful01_false 
    14.Stateful01_true 
    15.Centralized-sense-arw 
    16.CLHQueue-arw	
    17.Atomic01

## Litmus
121 small programs, including litmus tests for X86 TSO/PSO, standard
c programs, which come from [http://www.cprover.org/wmm/esop13/experiments.shtml](http://www.cprover.org/wmm/esop13/experiments.shtml).




## Usage
1. move fold regression-examples to “src/examples/”:

    `mv -f regression-examples examples/.`
2. go to directory regression-examples, use make to run this test set:

```sh
     make clean
     make check
``` 



## Known Issues


Welcome to send email to: naling@vt.edu at RSS group at Virginia Tech.



