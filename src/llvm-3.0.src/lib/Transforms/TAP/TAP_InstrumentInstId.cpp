//===- TAP_InstrumentInstId.cpp - "LLVM Pass for Calls" ---------------------===//
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

struct TAP_InstrumentInstId : public ModulePass {

  static char ID; 
  std::map<StringRef,GlobalVariable*>  funcName_to_globalVar;

  TAP_InstrumentInstId() : ModulePass(ID) {}

  void TAP_declareFunctions(Module *M);
  void TAP_instrumentBasicBlock_InstId(BasicBlock *B);

  CallInst* TAP_createInstructionPre(Instruction *I);
  CallInst* TAP_createInstructionPost(Instruction *I);

  Constant *TAP_getInstructionNameExpr(Instruction *I);
  Constant *TAP_getInstTypeNameExpr(Instruction *I); 
  Constant *TAP_getStringNameExpr(Module *M, StringRef &str);
  Constant *TAP_getStringNameExpr_Inst(Module *M, StringRef &str);
  Constant *TAP_getCalledFuncNameExpr(CallInst *I);
  Constant *TAP_getInstructionAsString(Instruction *I); 
  StringRef TAP_demangleCxxName(StringRef &mangled);

  virtual void getAnalysisUsage(AnalysisUsage &AU) const {
    AU.addRequiredTransitive<AliasAnalysis>();
  }

  virtual bool runOnModule(Module &M) {
    ++ModuleCounter;
    errs() << "TAP_InstrumentInstId : ";
    errs().write_escaped(M.getModuleIdentifier()) << '\n';

    TAP_declareFunctions(&M);

    for (Module::iterator F = M.begin(); F != M.end(); F++) {
      for (Function::iterator B = F->begin(); B != F->end(); B++) {
        TAP_instrumentBasicBlock_InstId(B);
      }
    }

    //chao, in case we have more than one module
    InstCounter += (1<<16);

    return false;
  }
  
};


void TAP_InstrumentInstId::TAP_declareFunctions(Module *M)
{
  LLVMContext &C = M->getContext();
  FunctionType *FT = NULL;
  {
    Type *Result = Type::getVoidTy(C);
    std::vector<Type*> Params;
    Type *Counter = IntegerType::getInt32Ty(C);
    Params.push_back(Counter);
    bool isVarArg = true;  
    FT = FunctionType::get(Result, Params, isVarArg);
  }
  M->getOrInsertFunction("clap_inst_pre"  , FT);
  M->getOrInsertFunction("clap_inst_post" , FT);
  // void clap_inst_pre(int , ...);
  // void clap_inst_post(int , ...);
}


// for each LLVM instruction, for example,
//
//    %x = call @foo  !clap !10
//
// transform it to
//
//    call @clap_inst_pre  (1, 10);
//    %x = call @foo
//    call @clap_inst_post (1, 10);
//
void TAP_InstrumentInstId::TAP_instrumentBasicBlock_InstId(BasicBlock *B)
{
  // for each instruction, prepare the "PRE" and "POST" calls
  std::vector<BasicBlock::iterator> insertPts;
  std::vector<CallInst*> insertPreIs;
  std::vector<CallInst*> insertPostIs;
  for (BasicBlock::iterator I = B->begin(); I != B->end(); I++) {
    
    if (CallInst *callI = dyn_cast<CallInst>(I)) {
      //skip the LLVM intrisic calls
      if (dyn_cast<IntrinsicInst>(callI) != NULL)  
        continue; 
      //skip unknown function calls
      if (callI->getCalledFunction() == NULL)     
        continue;
      //skip CLAP function calls
      if (!strncmp("clap_", callI->getCalledFunction()->getName().data(), 5))
        continue;
    }

/*  This has been moved to TAP_InstrumentInstNumber.cpp
  
    //assign a unique Metadata number to the instruction
    LLVMContext &C = B->getParent()->getParent()->getContext();
    Value* elts[] = { ConstantInt::get(C, APInt(32,++InstCounter)) };
    MDNode* md_node = MDNode::get(C, elts);
    I->setMetadata("clap", md_node);
*/

    //create new instructions (pre and post)
    CallInst *preI  = TAP_createInstructionPre(I);  
    CallInst *postI = NULL;
    if (I->isTerminator() == false) {
      if (CallInst *callI = dyn_cast<CallInst>(I)) {
        if (strncmp("tap_", callI->getCalledFunction()->getName().data(), 4)) {
          //if the called function is not "tap_input_...()"
          postI = TAP_createInstructionPost(I); 
        }
      }
    }
    insertPts.push_back(I);
    insertPreIs.push_back(preI);
    insertPostIs.push_back(postI);
  }        

  // inserting the "PRE" and "POST" calls
  for (unsigned int n=0; n<insertPts.size(); n++) {
    if (insertPreIs[n] != NULL) 
      B->getInstList().insert( insertPts[n], insertPreIs[n] );
    if (insertPostIs[n] != NULL) 
      B->getInstList().insertAfter( insertPts[n], insertPostIs[n] );
  }
}


// for each function call instruction
//     %x =  call @foo (%a, %b) !clap !10
// create a new call instruction
//      call @clap_inst_pre  (1, 10)
//
CallInst* TAP_InstrumentInstId::TAP_createInstructionPre(Instruction *I0) 
{
  Module *M = I0->getParent()->getParent()->getParent();  
  LLVMContext &C = M->getContext();
  Value *preFunc  = M->getFunction("clap_inst_pre");
  std::vector<Value*> Args;
  Args.push_back( ConstantInt::get(C, APInt(32,2)) );
  Args.push_back( I0->getMetadata("clap")->getOperand(0) );
  Value *cond = NULL;
  if (BranchInst* brI = dyn_cast<BranchInst>(I0)) {
    if (brI->isConditional()) {
      cond = brI->getCondition();
    }
  }
  if (cond == NULL) {
    cond = ConstantInt::get(C,APInt(1,1));
  }
  Args.push_back( cond );
  CallInst* preI  = CallInst::Create(preFunc, Args);
  return preI;
}


// for each function call instruction
//    %x =  @foo (%a, %b)  !clap !10
// create a new call instruction
//      call @clap_inst_post  (3, 10, status, retval);
//
CallInst* TAP_InstrumentInstId::TAP_createInstructionPost(Instruction *I0) 
{
  Module *M = I0->getParent()->getParent()->getParent();  
  LLVMContext &C = M->getContext();
  Value *postFunc = M->getFunction("clap_inst_post");
  std::vector<Value*> Args;
  Args.push_back( ConstantInt::get(C, APInt(32,3)) );
  Args.push_back( I0->getMetadata("clap")->getOperand(0) );

  // whether IF or ELSE branch is taken
  Value *cond = NULL;
  if (BranchInst* brI = dyn_cast<BranchInst>(I0)) {
    if (brI->isConditional()) {
      cond = brI->getCondition();
    }
  }
  if (cond == NULL) {
    cond = ConstantInt::get(C,APInt(1,1));
  }
  Args.push_back( cond ); 

  // get the return value of the function call
  Value *value = (Value*) I0;
  Args.push_back( value );

  CallInst* postI  = CallInst::Create(postFunc, Args);
  return postI;
}



}//namespace 

char TAP_InstrumentInstId::ID = 0;
static RegisterPass<TAP_InstrumentInstId> X("tap_inst_id", 
                                            "TAP Instruction ID Pass");
