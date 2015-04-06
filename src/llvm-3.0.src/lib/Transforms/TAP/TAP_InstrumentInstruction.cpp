//===- TAP_InstrumentInstruction.cpp - "LLVM Pass for Calls" ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Author: Chao Wang <chaowang@vt.edu>
// Date: 2-19-2012
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

struct TAP_InstrumentInstruction : public ModulePass {

  static char ID; 
  std::map<StringRef,GlobalVariable*>  funcName_to_globalVar;

  TAP_InstrumentInstruction() : ModulePass(ID) {}

  void TAP_declareFunctions(Module *M);
  void TAP_instrumentBasicBlock_Instruction(BasicBlock *B);
  bool TAP_mayEscape(Instruction *I);

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
    errs() << "TAP_InstrumentInstruction : ";
    errs().write_escaped(M.getModuleIdentifier()) << '\n';

    TAP_declareFunctions(&M);

    for (Module::iterator F = M.begin(); F != M.end(); F++) {
      for (Function::iterator B = F->begin(); B != F->end(); B++) {
        TAP_instrumentBasicBlock_Instruction(B);
      }
    }

    //chao, in case we have more than one module
    InstCounter += (1<<16);

    return false;
  }
  
};


void TAP_InstrumentInstruction::TAP_declareFunctions(Module *M)
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
}


// for each LLVM instruction, for example,
//
//    %x = call @foo 
//
// transform it to
//
//    call @clap_inst_pre  (3, "call", "%x", "@foo");
//    %x = call @foo
//    call @clap_inst_post (3, "call", "%x", "@foo");
//
void TAP_InstrumentInstruction::TAP_instrumentBasicBlock_Instruction(BasicBlock *B)
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
      //skip the CLAP function calls
      if (callI->getCalledFunction() == NULL)     continue;
      if (!strncmp("clap_", callI->getCalledFunction()->getName().data(), 5))
        continue;
    }

    //assign a unique Metadata number to the instruction
    LLVMContext &C = B->getParent()->getParent()->getContext();
    Value* elts[] = { ConstantInt::get(C, APInt(32,++InstCounter)) };
    MDNode* md_node = MDNode::get(C, elts);
    I->setMetadata("clap", md_node);


    CallInst *preI  = TAP_createInstructionPre(I);  
    CallInst *postI = (I->isTerminator()? NULL: TAP_createInstructionPost(I)); 
      
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

StringRef TAP_InstrumentInstruction::TAP_demangleCxxName(StringRef &mangled)
{
  StringRef res = mangled;

  int status;
  char *str = abi::__cxa_demangle(mangled.data(), 0, 0, &status);
  if (status == 0) {
    res = StringRef(str);
  }

  return res;
}

Constant *TAP_InstrumentInstruction::TAP_getStringNameExpr(Module *M, StringRef &f_nm_mangled)
{
  StringRef f_nm = TAP_demangleCxxName(f_nm_mangled);

  LLVMContext &C = M->getContext();
  
  GlobalVariable *f_name_v;
  if (funcName_to_globalVar.find(f_nm) != funcName_to_globalVar.end()) {
    f_name_v = funcName_to_globalVar[ f_nm ];
  }
  else {
    Constant *f_name = ConstantArray::get(C, f_nm);
    f_name_v = new GlobalVariable(*M, f_name->getType(), true, 
                                  GlobalValue::InternalLinkage,
                                  f_name,  "__tap_" + f_nm);
    funcName_to_globalVar[f_nm] = f_name_v;
  }
  Constant *zero_32 = Constant::getNullValue(IntegerType::getInt32Ty(C));    
  Constant *gep_params[] = { zero_32, zero_32 };
  Constant *f_name_ptr = ConstantExpr::getGetElementPtr(f_name_v, gep_params);
  return f_name_ptr;
}

Constant *TAP_InstrumentInstruction::TAP_getStringNameExpr_Inst(Module *M, StringRef &f_nm)
{
  LLVMContext &C = M->getContext();
  
  GlobalVariable *f_name_v;
  if (funcName_to_globalVar.find(f_nm) != funcName_to_globalVar.end()) {
    f_name_v = funcName_to_globalVar[ f_nm ];
  }
  else {
    Constant *f_name = ConstantArray::get(C, f_nm);
    f_name_v = new GlobalVariable(*M, f_name->getType(), true, 
                                  GlobalValue::InternalLinkage,
                                  f_name,  "__tap_inst_" + itostr(InstCounter));
    funcName_to_globalVar[f_nm] = f_name_v;
  }
  Constant *zero_32 = Constant::getNullValue(IntegerType::getInt32Ty(C));    
  Constant *gep_params[] = { zero_32, zero_32 };
  Constant *f_name_ptr = ConstantExpr::getGetElementPtr(f_name_v, gep_params);
  return f_name_ptr;
}


// given the CallInst, create a constrant string expr of the func name
Constant *TAP_InstrumentInstruction::TAP_getCalledFuncNameExpr(CallInst *I)
{
  StringRef f_nm = I->getCalledFunction()->getName();
  Module *M = I->getParent()->getParent()->getParent();
  Constant *val = TAP_getStringNameExpr(M, f_nm);
  return val; 
}

Constant *TAP_InstrumentInstruction::TAP_getInstructionAsString(Instruction *I)
{
  std::string ss;
  raw_string_ostream raw_ss(ss);
  I->print(raw_ss, 0);

  errs() << "\n ss = " << ss << "\n";

  StringRef ss_ref = ss;

  Module *M = I->getParent()->getParent()->getParent();
  Constant *val = TAP_getStringNameExpr_Inst(M, ss_ref);
  return val; 
}

bool TAP_InstrumentInstruction::TAP_mayEscape(Instruction *I) 
{
  bool res = false;

  if (AliasAnalysis* AA = getAnalysisIfAvailable<AliasAnalysis>()) {
    // AliasAnalysis is available.

    Function *F = I->getParent()->getParent();
    Module *M = F->getParent();

    Value* Pointer = NULL;
    unsigned ValueSize = (unsigned) AliasAnalysis::UnknownSize;
    if (StoreInst* S = dyn_cast<StoreInst>(I)) {
      Pointer = S->getPointerOperand();
      Type* ValueType = S->getValueOperand()->getType();
      ValueSize = AA->getTypeStoreSize(ValueType);
    }
    else if (LoadInst* S = dyn_cast<LoadInst>(I)) {
      Pointer = S->getPointerOperand();
      Type* ValueType = S->getType();
      ValueSize = AA->getTypeStoreSize(ValueType);
    }
    else {
      assert(0 && "TAP_mayEscape: instruction is neither Load nor Store");
    }
    
    if (res == false) {
      // does it alias to a function parameter?
      for (Function::arg_iterator AI = F->arg_begin(), AE = F->arg_end(); 
           AI != AE; ++AI) {
        if (isa<PointerType>(AI->getType())) {
          AliasAnalysis::AliasResult R = AA->alias(Pointer, ValueSize, AI, ~0U);
          if (R != AliasAnalysis::NoAlias) {
            res = true;
            break;
          }
        }
      }
    }
    
    if (res == false) {
      // does it alias to a global variable?
      for (Module::global_iterator GI = M->global_begin(), GE = M->global_end();
           GI != GE; ++GI) {
        AliasAnalysis::AliasResult R = AA->alias(Pointer, ValueSize, GI, ~0U);
        if (R != AliasAnalysis::NoAlias) {
          res = true;
          break;
        }
      }
    }
    
  }

  return res;
}



// for each function call instruction
//     %x =  call @foo (%a, %b)
// create a new call instruction
//      call @clap_inst_pre  (5, "call", "@foo", "%a", "%b" );
//
CallInst* TAP_InstrumentInstruction::TAP_createInstructionPre(Instruction *I0) 
{
  Module *M = I0->getParent()->getParent()->getParent();  
  LLVMContext &C = M->getContext();
  Value *preFunc  = M->getFunction("clap_inst_pre");
  std::vector<Value*> Args;

/*
  if (CallInst* I = dyn_cast<CallInst>(I0)) {
    unsigned int numArgs = I->getNumArgOperands();
    // ( n_param, call, fname, fparam1, fparam2, ... )
    Args.push_back( ConstantInt::get(C, APInt(32,numArgs+3)) );
    Args.push_back("call");
    Args.push_back( TAP_getCalledFuncNameExpr(I) );
    for (unsigned int n = 0; n < I->getNumArgOperands(); n++) {
      Args.push_back( I->getArgOperand(n) );
    }
  }
*/

  Args.push_back( ConstantInt::get(C, APInt(32,1)) );
  Args.push_back( I0->getMetadata("clap")->getOperand(0) );
//  Args.push_back( TAP_getInstructionAsString(I0) );
  CallInst* preI  = CallInst::Create(preFunc, Args);
  return preI;
}


// for each function call instruction
//    %x =  @foo (%a, %b)
// create a new call instruction
//      call @TAP_call_post  (4, call, @foo, %x );
//
CallInst* TAP_InstrumentInstruction::TAP_createInstructionPost(Instruction *I0) 
{
  Module *M = I0->getParent()->getParent()->getParent();  
  LLVMContext &C = M->getContext();
  Value *postFunc = M->getFunction("clap_inst_post");
  std::vector<Value*> Args;

/*
  if (CallInst* I = dyn_cast<CallInst>(I0)) {
    unsigned int numArgs = (I->getType()->isVoidTy()? 0:1);
    // ( n_param, call, fname, ... )
    Args.push_back( ConstantInt::get(C, APInt(32,numArgs+3)) );
    Args.push_back( ((Value*)I) );
    Args.push_back( "call" );
    Args.push_back( TAP_getCalledFuncNameExpr(I) );
    if (numArgs == 1) {
      Args.push_back((Value*)I);
    }
  }
*/
 
  Args.push_back( ConstantInt::get(C, APInt(32,1)) );
  Args.push_back( I0->getMetadata("clap")->getOperand(0) );
//  Args.push_back( TAP_getInstructionAsString(I0) );
  CallInst* postI  = CallInst::Create(postFunc, Args);
  return postI;
}



}//namespace 

char TAP_InstrumentInstruction::ID = 0;
static RegisterPass<TAP_InstrumentInstruction> X("tap_instruction", 
                                                 "TAP Instruction Pass");
