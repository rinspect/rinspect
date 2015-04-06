//===- TAP_InstrumentMemInst.cpp - "LLVM Pass for Ld/St" ---------------===//
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

std::map<StringRef,GlobalVariable*>  funcName_to_globalVar;

void TAP_declareFunctions(Module *M);
void TAP_instrumentBasicBlock_Inst(BasicBlock *B);
CallInst* TAP_createMemInstPre(Instruction *I);
CallInst* TAP_createMemInstPost(Instruction *I);
Constant *TAP_getInstructionNameExpr(Instruction *I);
Constant *TAP_getInstTypeNameExpr(Instruction *I); 
Constant *TAP_getStringNameExpr(Module *M, StringRef &str);


struct TAP_InstrumentMemInst : public ModulePass {

  static char ID; 

  TAP_InstrumentMemInst() : ModulePass(ID) {}
  
  virtual bool runOnModule(Module &M) {
    ++ModuleCounter;
    errs() << "TAP_InstrumentMemInst : ";
    errs().write_escaped(M.getModuleIdentifier()) << '\n';

    TAP_declareFunctions(&M);

    for (Module::iterator F = M.begin(); F != M.end(); F++) {
      for (Function::iterator B = F->begin(); B != F->end(); B++) {
        TAP_instrumentBasicBlock_Inst(B);
      }
    }
    
    return false;
  }
  
};


void TAP_declareFunctions(Module *M)
{
  LLVMContext &C = M->getContext();
  FunctionType *FT = NULL;
  {
    Type *Result = Type::getVoidTy(C);
    Type *FnName = PointerType::getUnqual(IntegerType::getInt8Ty(C));
    std::vector<Type*> Params;
    Params.push_back(FnName);
    bool isVarArg = true;  
    FT = FunctionType::get(Result, Params, isVarArg);
  }
  M->getOrInsertFunction("TAP_MEM_PRE", FT);
  M->getOrInsertFunction("TAP_MEM_POST", FT);
}


// for each LLVM instruction (LoadInst or StoreInst) 
//
//    %x = load %mem
//    store %x, %mem
//
// transform it to
//
//    call @TAP_MEM_PRE  ( "load",  %mem);
//    %x = load %mem
//    call @TAP_MEM_POST ( "load",  %x);
//    call @TAP_MEM_PRE  ( "store", %x,  %mem)
//    store %x, %mem
//    call @TAP_MEM_PRE  ( "store" )
//
void TAP_instrumentBasicBlock_Inst(BasicBlock *B)
{
  // for each load/store instruciton, prepare the "INST" call 
  std::vector<BasicBlock::iterator> insertPts;
  std::vector<CallInst*> insertPreIs;
  std::vector<CallInst*> insertPostIs;
  for (BasicBlock::iterator I = B->begin(); I != B->end(); I++) {
    if (dyn_cast<LoadInst>(I)) {
      CallInst *preI  = TAP_createMemInstPre(I);  //create "PRE"
      CallInst *postI  = TAP_createMemInstPost(I);  
      insertPts.push_back(I);
      insertPreIs.push_back(preI);
      insertPostIs.push_back(postI);
    }        
    else if (dyn_cast<StoreInst>(I)) {
      CallInst *preI = TAP_createMemInstPre(I); //create "PRE"
      CallInst *postI  = TAP_createMemInstPost(I);  
      insertPts.push_back(I);
      insertPreIs.push_back(preI);
      insertPostIs.push_back(postI);
    }
  }  
  // inserting the "PRE" calls
  for (unsigned int n=0; n<insertPts.size(); n++) {
    B->getInstList().insert( insertPts[n], insertPreIs[n] );
    B->getInstList().insertAfter( insertPts[n], insertPostIs[n] );
  }
}

Constant *TAP_getStringNameExpr(Module *M, StringRef &f_nm)
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
                                  f_name,  "__tap_" + f_nm);
    funcName_to_globalVar[f_nm] = f_name_v;
  }
  Constant *zero_32 = Constant::getNullValue(IntegerType::getInt32Ty(C));    
  Constant *gep_params[] = { zero_32, zero_32 };
  Constant *f_name_ptr = ConstantExpr::getGetElementPtr(f_name_v, gep_params);
  return f_name_ptr;
}

// given the Inst, create a constrant string expr of the inst type 
Constant *TAP_getInstTypeNameExpr(Instruction *I)
{
  StringRef it_nm = I->getOpcodeName();
  Module *M = I->getParent()->getParent()->getParent();
  Constant *val = TAP_getStringNameExpr(M, it_nm);
  return val;
}


// for each LLVM instruction 
//      %x = load %mem
// create a new call instruction
//      call @TAP_INST ( "load",  %x, %mem );
CallInst* TAP_createMemInstPre(Instruction *I) 
{
  CallInst *preI = NULL;

  Module *M = I->getParent()->getParent()->getParent();  
  Value *preFunc  = M->getFunction("TAP_MEM_PRE");
  
  std::vector<Value*> Args; 
  {
    Constant *it_name_ptr = TAP_getInstTypeNameExpr(I);
    Args.push_back( it_name_ptr );
    if (LoadInst *loadI = dyn_cast<LoadInst>(I))
      Args.push_back(  loadI->getPointerOperand() );
    else if (StoreInst *storeI = dyn_cast<StoreInst>(I))
      Args.push_back( storeI->getPointerOperand() );      
  }
  
  preI  = CallInst::Create(preFunc, Args);
  return preI;
}

CallInst* TAP_createMemInstPost(Instruction *I) 
{
  CallInst *preI = NULL;

  Module *M = I->getParent()->getParent()->getParent();  
  Value *preFunc  = M->getFunction("TAP_MEM_POST");
  
  std::vector<Value*> Args;
  {
    Constant *it_name_ptr = TAP_getInstTypeNameExpr(I);
    Args.push_back( it_name_ptr );
    if (LoadInst *loadI = dyn_cast<LoadInst>(I))
      Args.push_back(  loadI->getPointerOperand() );
    else if (StoreInst *storeI = dyn_cast<StoreInst>(I))
      Args.push_back( storeI->getPointerOperand() );      
  }

  preI  = CallInst::Create(preFunc, Args);
  return preI;
}

}//namespace

char TAP_InstrumentMemInst::ID = 0;
static RegisterPass<TAP_InstrumentMemInst> X("tap_mem", 
                                             "TAP Load/Store Module Pass");
