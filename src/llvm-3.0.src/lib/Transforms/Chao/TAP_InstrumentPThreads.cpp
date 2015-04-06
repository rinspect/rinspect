//===- TAP_InstrumentPThreads.cpp - TAP Front-end tool @ VT " ------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements a Module Pass that replace the POSIX Thread routines
// with the corresponding TAP routines.
//
// Author: Chao Wang <chaowang@vt.edu>  
// Date: 2-19-2012
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "chao"
#include <map>
#include "llvm/Pass.h"
#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/Instructions.h"
#include "llvm/Constants.h"
#include "llvm/Type.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
using namespace llvm;

STATISTIC(ModuleCounter, "Counts number of modules greeted");

namespace {

void TAP_replaceFunctions(Module *M);
std::string TAP_getReplaceFuncName(Function &func);


struct TAP_PThreads : public ModulePass {
  static char ID; 
  TAP_PThreads() : ModulePass(ID) {}

  virtual bool runOnModule(Module &M) {
    ++ModuleCounter;
    errs() << "TAP_InstrumentPThreads: Module ";
    errs().write_escaped(M.getModuleIdentifier()) << '\n';
    TAP_replaceFunctions(&M);
    return false;
  }
  
};

void TAP_replaceFunctions(Module *M)
{
  for (Module::iterator F = M->begin(); F != M->end(); F++) {
    if (F->isDeclaration()) {
      Function &func = *F;
      std::string func_name = TAP_getReplaceFuncName(func);
      if (func_name != "") {
        func.setName( func_name );
      }
      errs() << "func->getName() = ";
      errs().write_escaped(func.getName()) << '\n';      
    }
  }
}

std::string functionToBeReplaced[] = 
{
  "pthread_create",         "TAP_thread_create",    // 0
  "pthread_join",           "TAP_thread_join",      // 1

  "pthread_mutex_init",      "TAP_mutex_init",      // 2
  "pthread_mutex_destroy",   "TAP_mutex_destroy",   // 3
  "pthread_mutex_lock",      "TAP_mutex_lock",      // 4
  "pthread_mutex_unlock",    "TAP_mutex_unlock",    // 5
  "pthread_mutex_trylock",   "TAP_mutex_trylock",   // 6
  "pthread_mutex_timedlock", "TAP_mutex_timedlock", // 7

  "pthread_cond_init",      "TAP_cond_init",        // 8    
  "pthread_cond_destroy",   "TAP_cond_destroy",     // 9
  "pthread_cond_signal",    "TAP_cond_signal",      // 10
  "pthread_cond_broadcast", "TAP_cond_broadcast",   // 11
  "pthread_cond_wait",      "TAP_cond_wait",        // 12
  "pthread_cond_timedwait", "TAP_cond_timedwait",   // 13

  "pthread_rwlock_init",     "TAP_rwlock_init",     // 14 
  "pthread_rwlock_destroy",  "TAP_rwlock_destroy",  // 15
  "pthread_rwlock_rdlock",   "TAP_rwlock_rdlock",   // 16
  "pthread_rwlock_wrlock",   "TAP_rwlock_wrlock",   // 17
  "pthread_rwlock_tryrdlock","TAP_rwlock_tryrdlock",// 18 
  "pthread_rwlock_trywrlock","TAP_rwlock_trywrlock",// 19
  "pthread_rwlock_unlock",   "TAP_rwlock_unlock",   // 20

  "", ""
};
  
std::string TAP_getReplaceFuncName(Function &func)
{
  std::string func_name = func.getName();
  std::string new_name = "";

  for (unsigned n = 0; functionToBeReplaced[n] != ""; n += 2) {
    if (func_name == functionToBeReplaced[n]) {
      new_name = functionToBeReplaced[n+1];
      break;
    }
  }

  return new_name;
} 

}//namespace


char TAP_PThreads::ID = 0;
static RegisterPass<TAP_PThreads> X("tap_pthreads", 
                                    "TAP Replacing PThreads Module Pass");
