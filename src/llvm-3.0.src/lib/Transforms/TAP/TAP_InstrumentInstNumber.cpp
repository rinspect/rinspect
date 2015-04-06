//===- TAP_InstrumentInstNumber.cpp - "LLVM Pass for Calls" ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Author: Chao Wang <chaowang@vt.edu>
// Date: 7-15-2012
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "chao"
#include <map>
#include <sstream>
#include <string>
#include <cxxabi.h>
#include "llvm/Pass.h"
#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/Instructions.h"
#include "llvm/IntrinsicInst.h"
#include "llvm/Constants.h"
#include "llvm/Value.h"
#include "llvm/Type.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Target/TargetData.h"
#include "llvm/ADT/StringExtras.h"

using namespace llvm;

STATISTIC(ModuleCounter, "Counts number of modules greeted");
STATISTIC(InstCounter, "Counts number of instructions greeted");

namespace {

struct TAP_InstrumentInstNumber : public ModulePass {

  static char ID; 

  TAP_InstrumentInstNumber() : ModulePass(ID) {}

  void TAP_instrumentBasicBlock_InstNumber(BasicBlock *B);

  virtual void getAnalysisUsage(AnalysisUsage &AU) const {
    AU.addRequiredTransitive<AliasAnalysis>();
  }

  virtual bool runOnModule(Module &M) {
    ++ModuleCounter;
    errs() << "TAP_InstrumentInstNumber : ";
    errs().write_escaped(M.getModuleIdentifier()) << '\n';
    
    for (Module::iterator F = M.begin(); F != M.end(); F++) {
      for (Function::iterator B = F->begin(); B != F->end(); B++) {
        TAP_instrumentBasicBlock_InstNumber(B);
      }
    }

    //chao, in case we have more than one module
    InstCounter += (1<<16);

    return false;
  }
  
};


void TAP_InstrumentInstNumber::TAP_instrumentBasicBlock_InstNumber(BasicBlock *B)
{
  for (BasicBlock::iterator I = B->begin(); I != B->end(); I++) {
    
/* Chao: 12/26/2012 we don't seem to need this check

    if (CallInst *callI = dyn_cast<CallInst>(I)) {
      //skip the LLVM intrisic calls
      if (dyn_cast<IntrinsicInst>(callI) != NULL)  
        continue; 
      //skip the CLAP function calls
      if (callI->getCalledFunction() == NULL)     
        continue;
      if (!strncmp("clap_", callI->getCalledFunction()->getName().data(), 5))
        continue;
    }

*/  

    //assign a unique Metadata number to the instruction
    LLVMContext &C = B->getParent()->getParent()->getContext();
    Value* elts[] = { ConstantInt::get(C, APInt(32,++InstCounter)) };
    MDNode* md_node = MDNode::get(C, elts);
    I->setMetadata("clap", md_node);

  }        

}



}//namespace 

char TAP_InstrumentInstNumber::ID = 0;
static RegisterPass<TAP_InstrumentInstNumber> X("tap_inst_number", 
                                            "TAP Instruction Number Pass");
