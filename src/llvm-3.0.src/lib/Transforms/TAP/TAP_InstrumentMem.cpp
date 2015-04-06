//===- TAP_InstrumentMem.cpp - "LLVM Pass for Ld/St" ---------------===//
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
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Target/TargetData.h"
#include "llvm/ADT/StringExtras.h"

using namespace llvm;

STATISTIC(ModuleCounter, "Counts number of modules greeted");

namespace {

std::map<StringRef,GlobalVariable*>  funcName_to_globalVar;

CallInst* TAP_createMemInstPre(Instruction *I);
CallInst* TAP_createMemInstPost(Instruction *I);
CallInst* TAP_createLoadStorePre(Instruction *I);
CallInst* TAP_createLoadStorePost(Instruction *I);
Constant *TAP_getInstructionNameExpr(Instruction *I);
Constant *TAP_getInstTypeNameExpr(Instruction *I); 
Constant *TAP_getStringNameExpr(Module *M, StringRef &str);


struct TAP_InstrumentMemInst : public ModulePass {

  static char ID; 

  TAP_InstrumentMemInst() : ModulePass(ID) {}

  void TAP_declareFunctions(Module *M);
  void TAP_instrumentBasicBlock_Inst(BasicBlock *B);
  bool TAP_mayEscape(Instruction *I);

  virtual void getAnalysisUsage(AnalysisUsage &AU) const {
    AU.addRequiredTransitive<AliasAnalysis>();
  }

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


void TAP_InstrumentMemInst::TAP_declareFunctions(Module *M)
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
  M->getOrInsertFunction("clap_load_pre"  , FT);
  M->getOrInsertFunction("clap_load_post" , FT);
  M->getOrInsertFunction("clap_store_pre" , FT);
  M->getOrInsertFunction("clap_store_post", FT);
  M->getOrInsertFunction("clap_cmpxchg_pre" , FT);
  M->getOrInsertFunction("clap_cmpxchg_post", FT);
  M->getOrInsertFunction("clap_atomicrmw_pre" , FT);
  M->getOrInsertFunction("clap_atomicrmw_post", FT);
}


// for each LLVM instruction (LoadInst or StoreInst) 
//
//    %x = load %mem
//    store %x, %mem
//
// transform it to
//
//    call @clap_load_pre  (%mem);
//    %x = load %mem
//    call @clap_load_post (%mem);
//
//    call @clap_store_pre  (%mem)
//    store %x, %mem
//    call @clap_store_post (%mem)
//
void TAP_InstrumentMemInst::TAP_instrumentBasicBlock_Inst(BasicBlock *B)
{
  // for each load/store instruciton, prepare the "INST" call 
  std::vector<BasicBlock::iterator> insertPts;
  std::vector<CallInst*> insertPreIs;
  std::vector<CallInst*> insertPostIs;
  for (BasicBlock::iterator I = B->begin(); I != B->end(); I++) {
    if (dyn_cast<LoadInst>(I)) {
      if (TAP_mayEscape(I) == true) {
        CallInst *preI  = TAP_createLoadStorePre(I);  
        CallInst *postI  = TAP_createLoadStorePost(I);  
        insertPts.push_back(I);
        insertPreIs.push_back(preI);
        insertPostIs.push_back(postI);
      }
    }        
    else if (dyn_cast<StoreInst>(I)) {
      if (TAP_mayEscape(I) == true) {
        CallInst *preI  = TAP_createLoadStorePre(I);  
        CallInst *postI  = TAP_createLoadStorePost(I);  
        insertPts.push_back(I);
        insertPreIs.push_back(preI);
        insertPostIs.push_back(postI);
      }
    }
    else if (dyn_cast<AtomicCmpXchgInst>(I)) {
      if (TAP_mayEscape(I) == true) {
        CallInst *preI  = TAP_createLoadStorePre(I);  
        CallInst *postI  = TAP_createLoadStorePost(I);  
        insertPts.push_back(I);
        insertPreIs.push_back(preI);
        insertPostIs.push_back(postI);
      }
    }
    else if (dyn_cast<AtomicRMWInst>(I)) {
      if (TAP_mayEscape(I) == true) {
        CallInst *preI  = TAP_createLoadStorePre(I);  
        CallInst *postI  = TAP_createLoadStorePost(I);  
        insertPts.push_back(I);
        insertPreIs.push_back(preI);
        insertPostIs.push_back(postI);
      }
    }
  }  
  // inserting the "PRE" and "POST" calls
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

int TAP_getBitWidth(Value *ptr)
{
  if (ptr->getType()->isIntegerTy()) {
    if (ptr->getType()->isIntegerTy(8))   return 8;
    if (ptr->getType()->isIntegerTy(16))   return 16;
    if (ptr->getType()->isIntegerTy(32))   return 32;
    if (ptr->getType()->isIntegerTy(64))   return 64;
    return sizeof(int);
  }
  if (ptr->getType()->isPointerTy())
    return sizeof(int*);
  return 0;
}

  // void clap_load_pre( num_params, addr, clapId);
  // void clap_store_pre( num_params, addr, value, clapId);
  // void clap_cmpxchg_pre( num_params, addr, 
CallInst* TAP_createLoadStorePre(Instruction *I) 
{
  CallInst *preI = NULL;

  Module *M = I->getParent()->getParent()->getParent();  
  LLVMContext &C = M->getContext();
  Value *preFunc  = NULL; 
  
  std::vector<Value*> Args; 

  if (LoadInst *loadI = dyn_cast<LoadInst>(I)) {
    preFunc = M->getFunction("clap_load_pre");
    Constant *val = ConstantInt::get(C, APInt(32,4));
    Value *ptr = loadI->getPointerOperand();
    Constant *ord = ConstantInt::get(C, APInt(32,(int)loadI->getOrdering()));
    int bitwidth = TAP_getBitWidth(loadI);
    Constant *typ = ConstantInt::get(C, APInt(32,bitwidth));
    Value *clap_id = loadI->getMetadata("clap")->getOperand(0);
    Args.push_back( val );
    Args.push_back( ptr );
    Args.push_back( ord );
    Args.push_back( typ );
    Args.push_back( clap_id);
  }
  else if (StoreInst *storeI = dyn_cast<StoreInst>(I)) {
    preFunc = M->getFunction("clap_store_pre");
    Constant *val = ConstantInt::get(C, APInt(32,5));
    Value *ptr = storeI->getPointerOperand();
    Constant *ord = ConstantInt::get(C, APInt(32,(int)storeI->getOrdering()));
    int bitwidth = TAP_getBitWidth(storeI->getValueOperand());
    Constant *typ = ConstantInt::get(C, APInt(32,bitwidth));
    Value *clap_id = storeI->getMetadata("clap")->getOperand(0);
    Args.push_back( val );
    Args.push_back( ptr );
    Args.push_back( storeI->getValueOperand() );   
    Args.push_back( ord );
    Args.push_back( typ );
    Args.push_back( clap_id );
  }
  else if (AtomicCmpXchgInst *cmpxchgI = dyn_cast<AtomicCmpXchgInst>(I)) {
    preFunc = M->getFunction("clap_cmpxchg_pre");
    Constant *val = ConstantInt::get(C, APInt(32,6));
    Value *ptr = cmpxchgI->getPointerOperand();
    Constant *ord = ConstantInt::get(C, APInt(32,(int)cmpxchgI->getOrdering()));
    int bitwidth = TAP_getBitWidth(cmpxchgI->getCompareOperand());
    Constant *typ = ConstantInt::get(C, APInt(32,bitwidth));
    Value *clap_id = cmpxchgI->getMetadata("clap")->getOperand(0);
    Args.push_back( val );   
    Args.push_back( ptr );
    Args.push_back( cmpxchgI->getCompareOperand() );   
    Args.push_back( cmpxchgI->getNewValOperand() );
    Args.push_back( ord );
    Args.push_back( typ );
    Args.push_back( clap_id );
  }
  else if (AtomicRMWInst *rmwI = dyn_cast<AtomicRMWInst>(I)) {
    preFunc = M->getFunction("clap_atomicrmw_pre");
    Constant *val = ConstantInt::get(C, APInt(32,5));
    Value *ptr = rmwI->getPointerOperand();
    Constant *ord = ConstantInt::get(C, APInt(32,(int)rmwI->getOrdering()));
    int bitwidth = TAP_getBitWidth(rmwI->getValOperand());
    Constant *typ = ConstantInt::get(C, APInt(32,bitwidth));
    Value *clap_id = rmwI->getMetadata("clap")->getOperand(0);
    Args.push_back( val );   
    Args.push_back( ptr );
    Args.push_back( rmwI->getValOperand() );   
    Args.push_back( ord );
    Args.push_back( typ );
    Args.push_back( clap_id );
  }
  else 
    assert( 0 && "TAP_createLoadStorePre() expects Load/Store/AtomicCmpXchg/AtomicRMW" );

  

  preI  = CallInst::Create(preFunc, Args);
  return preI;
}

CallInst* TAP_createLoadStorePost(Instruction *I) 
{
  CallInst *postI = NULL;

  Module *M = I->getParent()->getParent()->getParent();  
  LLVMContext &C = M->getContext();
  Value *postFunc  = NULL; 
  
  std::vector<Value*> Args; 

  if (LoadInst *loadI = dyn_cast<LoadInst>(I)) {
    postFunc = M->getFunction("clap_load_post");
    Constant *val = ConstantInt::get(C, APInt(32,4));
    Value *ptr = loadI->getPointerOperand();
    Constant *ord = ConstantInt::get(C, APInt(32,(int)loadI->getOrdering()));
    int bitwidth = TAP_getBitWidth(loadI);
    Constant *typ = ConstantInt::get(C, APInt(32,bitwidth));
    Value *clap_id = loadI->getMetadata("clap")->getOperand(0);
    Args.push_back( val );
    Args.push_back( ptr );
    Args.push_back( ord );
    Args.push_back( typ );
    Args.push_back( clap_id);
  }
  else if (StoreInst *storeI = dyn_cast<StoreInst>(I)) {
    postFunc = M->getFunction("clap_store_post");
    Constant *val = ConstantInt::get(C, APInt(32,5));
    Value *ptr = storeI->getPointerOperand();
    Constant *ord = ConstantInt::get(C, APInt(32,(int)storeI->getOrdering()));
    int bitwidth = TAP_getBitWidth(storeI->getValueOperand());
    Constant *typ = ConstantInt::get(C, APInt(32,bitwidth));
    Value *clap_id = storeI->getMetadata("clap")->getOperand(0);
    Args.push_back( val );
    Args.push_back( ptr );
    Args.push_back( storeI->getValueOperand() );   
    Args.push_back( ord );
    Args.push_back( typ );
    Args.push_back( clap_id );
  }
  else if (AtomicCmpXchgInst *cmpxchgI = dyn_cast<AtomicCmpXchgInst>(I)) {
    postFunc = M->getFunction("clap_cmpxchg_post");
    Constant *val = ConstantInt::get(C, APInt(32,6));
    Value *ptr = cmpxchgI->getPointerOperand();
    Constant *ord = ConstantInt::get(C, APInt(32,(int)cmpxchgI->getOrdering()));
    int bitwidth = TAP_getBitWidth(cmpxchgI->getCompareOperand());
    Constant *typ = ConstantInt::get(C, APInt(32,bitwidth));
    Value *clap_id = cmpxchgI->getMetadata("clap")->getOperand(0);
    Args.push_back( val );   
    Args.push_back( ptr );
    Args.push_back( cmpxchgI->getCompareOperand() );   
    Args.push_back( cmpxchgI->getNewValOperand() );
    Args.push_back( ord );
    Args.push_back( typ );
    Args.push_back( clap_id );
  }
  else if (AtomicRMWInst *rmwI = dyn_cast<AtomicRMWInst>(I)) {
    postFunc = M->getFunction("clap_atomicrmw_post");
    Constant *val = ConstantInt::get(C, APInt(32,5));
    Value *ptr = rmwI->getPointerOperand();
    Constant *ord = ConstantInt::get(C, APInt(32,(int)rmwI->getOrdering()));
    int bitwidth = TAP_getBitWidth(rmwI->getValOperand());
    Constant *typ = ConstantInt::get(C, APInt(32,bitwidth));
    Value *clap_id = rmwI->getMetadata("clap")->getOperand(0);
    Args.push_back( val );   
    Args.push_back( ptr );
    Args.push_back( rmwI->getValOperand() );   
    Args.push_back( ord );
    Args.push_back( typ );
    Args.push_back( clap_id );
  }
  else 
    assert( 0 && "TAP_createLoadStorePost() expects Load/Store/AtomicCmpXchg/AtomicRMW" ); 

  postI  = CallInst::Create(postFunc, Args);
  return postI;
}


bool TAP_InstrumentMemInst::TAP_mayEscape(Instruction *I) 
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
    else if (AtomicCmpXchgInst* S = dyn_cast<AtomicCmpXchgInst>(I)) {
      Pointer = S->getPointerOperand();
      Type* ValueType = S->getType();
      ValueSize = AA->getTypeStoreSize(ValueType);
    }
    else if (AtomicRMWInst* S = dyn_cast<AtomicRMWInst>(I)) {
      Pointer = S->getPointerOperand();
      Type* ValueType = S->getType();
      ValueSize = AA->getTypeStoreSize(ValueType);
    }
    else {
      assert(0 && "TAP_mayEscape: instruction is neither Load nor Store");
    }
    
#if 1
//chao: this is very expensive

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
#else

    // return TRUE only if the  mem address is a global variable
    if (res == false) {
      // does it alias to a global variable?
      for (Module::global_iterator GI = M->global_begin(), GE = M->global_end();
           GI != GE; ++GI) {
        if (GI->hasName() && Pointer->hasName()) {
          std::string GI_name = GI->getName();
          std::string Pointer_name = Pointer->getName();
          if (!strcmp(GI_name.c_str(),Pointer_name.c_str())) {
            res = true;
            break;
          }
        }
      }
    }
#endif
    
  }

  return res;
}


}//namespace 

char TAP_InstrumentMemInst::ID = 0;
static RegisterPass<TAP_InstrumentMemInst> X("tap_mem", 
                                             "TAP Load/Store Module Pass");
