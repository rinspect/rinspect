
#ifndef __INSPECTOR_LLVM_H__
#define __INSPECTOR_LLVM_H__

//CHAO:  9/18/2013
//
//I have taken these type definitions from the LLVM header file 
//
//They may be useful for Naling's project on modeling TSO/PSO

#define llvm_NotAtomic  0
#define llvm_Unordered  1
#define llvm_Monotonic  2
#define llvm_Consume    3
#define llvm_Acquire    4
#define llvm_Release    5
#define llvm_AcquireRelease  6
#define llvm_SequentiallyConsistent  7

typedef int llvm_AtomicOrdering_t;

#endif
