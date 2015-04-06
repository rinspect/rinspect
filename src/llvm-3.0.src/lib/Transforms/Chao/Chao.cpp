//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
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

void TAP_replaceFunctions(Module *M);
void TAP_declareFunctions(Module *M);
void TAP_instrumentModule(Module *M);

void TAP_instrumentBasicBlock_Call(BasicBlock *B);
void TAP_instrumentBasicBlock_Inst(BasicBlock *B);

CallInst* TAP_createCallInstPre(CallInst *I);
CallInst* TAP_createCallInstPost(CallInst *I); 
CallInst* TAP_createInstPre(Instruction *I);
CallInst* TAP_createInstPost(Instruction *I);
Constant *TAP_getCalledFuncNameExpr(CallInst *I); 
Constant *TAP_getInstructionNameExpr(Instruction *I);
std::vector<Value*> getInstructionOpsAsParams(Instruction *I);
Constant *TAP_getInstTypeNameExpr(Instruction *I); 
Constant *TAP_getStringNameExpr(Module *M, StringRef &str);
std::string TAP_getReplaceFuncName(Function &func);


struct ChaoModule : public ModulePass {

  static char ID; 

  ChaoModule() : ModulePass(ID) {}
  
  virtual bool runOnModule(Module &M) {
    ++ModuleCounter;
    errs() << "ChaoModule : ";
    errs().write_escaped(M.getModuleIdentifier()) << '\n';

    TAP_replaceFunctions(&M);
    TAP_declareFunctions(&M);
    TAP_instrumentModule(&M);
    
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
  M->getOrInsertFunction("TAP_CALL_PRE", FT);
  M->getOrInsertFunction("TAP_CALL_POST", FT);
  M->getOrInsertFunction("TAP_INST_PRE", FT);
  M->getOrInsertFunction("TAP_INST_POST", FT);
}


void TAP_instrumentModule(Module *M)
{
  for (Module::iterator F = M->begin(); F != M->end(); F++) {
    for (Function::iterator B = F->begin(); B != F->end(); B++) {
      TAP_instrumentBasicBlock_Call(B);
      TAP_instrumentBasicBlock_Inst(B);
    }
  }
}


// for each non-system call, e.g. 
//
//    %x = call @foo (%a, %b)
//
// transform it to
//
//    call @TAP_call_pre  ( @foo,  %a, %b );
//    %x = call @foo (%a, %b)
//    call @TAP_call_post ( @foo,  %x );
//
void TAP_instrumentBasicBlock_Call(BasicBlock *B)
{
  // for each function, prepare the "PRE" and "POST" calls
  std::vector<BasicBlock::iterator> insertPts;
  std::vector<CallInst*> insertPreIs;
  std::vector<CallInst*> insertPostIs;
  for (BasicBlock::iterator I = B->begin(); I != B->end(); I++) {
    if (CallInst *callI = dyn_cast<CallInst>(I)) {
      CallInst *preI  = TAP_createCallInstPre(callI);  //create "PRE"
      CallInst *postI = TAP_createCallInstPost(callI); //create "POST"
      insertPts.push_back(I);
      insertPreIs.push_back(preI);
      insertPostIs.push_back(postI);
    }        
  }  
  // inserting the "PRE" and "POST" calls
  for (unsigned int n=0; n<insertPts.size(); n++) {
    B->getInstList().insert( insertPts[n], insertPreIs[n] );
    B->getInstList().insertAfter( insertPts[n], insertPostIs[n] );
  }
}

// for each LLVM instruction 
//
//    %x = load %mem
//    store %x, %mem
//
// transform it to
//
//    call @TAP_INST  ( "load",  %x,  %mem);
//    %x = load %mem
//    call @TAP_INST  ( "store", %x,  %mem)
//    store %x, %mem
//
void TAP_instrumentBasicBlock_Inst(BasicBlock *B)
{
  // for each load/store instruciton, prepare the "INST" call 
  std::vector<BasicBlock::iterator> insertPts;
  std::vector<CallInst*> insertPreIs;
  std::vector<CallInst*> insertPostIs;
  for (BasicBlock::iterator I = B->begin(); I != B->end(); I++) {
    if (dyn_cast<CallInst>(I)) {
      continue;
    }
    else if (dyn_cast<LoadInst>(I)) {
      CallInst *preI  = TAP_createInstPre(I);  //create "PRE"
      CallInst *postI  = TAP_createInstPost(I);  
      insertPts.push_back(I);
      insertPreIs.push_back(preI);
      insertPostIs.push_back(postI);
    }        
    else if (dyn_cast<StoreInst>(I)) {
      CallInst *preI = TAP_createInstPre(I); //create "PRE"
      CallInst *postI  = TAP_createInstPost(I);  
      insertPts.push_back(I);
      insertPreIs.push_back(preI);
      insertPostIs.push_back(postI);
    }
    else if (I->isTerminator() == false){
      CallInst *preI = TAP_createInstPre(I);
      CallInst *postI  = TAP_createInstPost(I);  
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


// for each function call instruction
//      @foo (%a, %b)
// create a new call instruction
//      call @TAP_call_pre  ( @foo,  %a, %b );
CallInst* TAP_createCallInstPre(CallInst *I) 
{
  CallInst *preI = NULL;

  Module *M = I->getParent()->getParent()->getParent();  
  //LLVMContext &C = M->getContext();

  Value *preFunc  = M->getFunction("TAP_CALL_PRE");
  
  std::vector<Value*> Args;
  Constant *f_name_ptr = TAP_getCalledFuncNameExpr(I);
  Args.push_back( f_name_ptr );
  for (unsigned int n = 0; n < I->getNumArgOperands(); n++) {
    Args.push_back( I->getArgOperand(n) );
  }

  preI  = CallInst::Create(preFunc, Args);
  return preI;
}


// for each function call instruction
//      @foo (%a, %b)
// create a new call instruction
//      call @TAP_call_post  ( @foo,  %a, %b );
CallInst* TAP_createCallInstPost(CallInst *I) 
{
  CallInst *postI = NULL;

  Module *M = I->getParent()->getParent()->getParent();  
  //LLVMContext &C = M->getContext();

  Value *postFunc  = M->getFunction("TAP_CALL_POST");

  std::vector<Value*> Args;
  Constant *f_name_ptr = TAP_getCalledFuncNameExpr(I);
  Args.push_back( f_name_ptr );
  if ( I->getType()->isVoidTy() == false ) {
    Args.push_back((Value*)I);
  }
  /*
  for (unsigned int n = 0; n < I->getNumArgOperands(); n++) {
    Args.push_back( I->getArgOperand(n) );
  }
  */
  postI  = CallInst::Create(postFunc, Args);
  return postI;
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


// given the CallInst, create a constrant string expr of the func name
Constant *TAP_getCalledFuncNameExpr(CallInst *I)
{
  StringRef f_nm = I->getCalledFunction()->getName();
  Module *M = I->getParent()->getParent()->getParent();
  Constant *val = TAP_getStringNameExpr(M, f_nm);
  return val; 
}

Constant *TAP_getInstructionNameExpr(Instruction *I)
{
  StringRef f_nm = I->getName();
  Module *M = I->getParent()->getParent()->getParent();
  Constant *val = TAP_getStringNameExpr(M, f_nm);
  return val; 
}

// given the Inst, create a constrant string expr of the inst type 
Constant *TAP_getInstTypeNameExpr(Instruction *I)
{
  StringRef it_nm = I->getOpcodeName();
  /*
  if (dyn_cast<LoadInst>(I)) {
    it_nm = "load";
  }
  else if (dyn_cast<StoreInst>(I)) {
    it_nm = "store";
  }
  else {
    it_nm = I->getOpcodeName();
  }
  */
  Module *M = I->getParent()->getParent()->getParent();
  Constant *val = TAP_getStringNameExpr(M, it_nm);
  return val;
}


// for each LLVM instruction 
//      %x = load %mem
// create a new call instruction
//      call @TAP_INST ( "load",  %x, %mem );
CallInst* TAP_createInstPre(Instruction *I) 
{
  CallInst *preI = NULL;

  Module *M = I->getParent()->getParent()->getParent();  
  Value *preFunc  = M->getFunction("TAP_INST_PRE");
  
  std::vector<Value*> Args; 
  {
    Constant *it_name_ptr = TAP_getInstTypeNameExpr(I);
    Args.push_back( it_name_ptr );
    for (unsigned int n = 0; n < I->getNumOperands(); n++) {
      Args.push_back( I->getOperand(n) );
    }
  }
  
  preI  = CallInst::Create(preFunc, Args);
  return preI;
}

CallInst* TAP_createInstPost(Instruction *I) 
{
  CallInst *preI = NULL;

  Module *M = I->getParent()->getParent()->getParent();  
  Value *preFunc  = M->getFunction("TAP_INST_POST");
  
  std::vector<Value*> Args;
  {
    Constant *it_name_ptr = TAP_getInstTypeNameExpr(I);
    Args.push_back( it_name_ptr );
    if ( I->getType()->isVoidTy() == false ) {
      Value *val = I;
      Args.push_back(val);
    }
    /*
    for (unsigned int n = 0; n < I->getNumOperands(); n++) {
      Args.push_back( I->getOperand(n) );
    }
    */
  }

  preI  = CallInst::Create(preFunc, Args);
  return preI;
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

/// WriteInstruction - Emit an instruction to the specified stream.
std::vector<Value*> getInstructionOpsAsParams(Instruction *I) 
{
  std::vector<Value*> Args;

  // insert Opcode Name of the instruction
  {
    Constant * it_nm = TAP_getInstTypeNameExpr(I);
    Args.push_back( it_nm );
  }

  // insert the operands of the instruction
  switch (I->getOpcode()) {
  default:
    if (Instruction::isCast(I->getOpcode())) {
      /*
      Code = bitc::FUNC_CODE_INST_CAST;
      if (!PushValueAndType(I->getOperand(0), InstID, Vals, VE))
        AbbrevToUse = FUNCTION_INST_CAST_ABBREV;
      Vals.push_back(VE.getTypeID(I->getType()));
      Vals.push_back(GetEncodedCastOpcode(I->getOpcode()));
      */
    } else {
      /*
      assert(isa<BinaryOperator>(I) && "Unknown instruction!");
      Code = bitc::FUNC_CODE_INST_BINOP;
      if (!PushValueAndType(I->getOperand(0), InstID, Vals, VE))
        AbbrevToUse = FUNCTION_INST_BINOP_ABBREV;
      Vals.push_back(VE.getValueID(I->getOperand(1)));
      Vals.push_back(GetEncodedBinaryOpcode(I->getOpcode()));
      uint64_t Flags = GetOptimizationFlags(&I);
      if (Flags != 0) {
        if (AbbrevToUse == FUNCTION_INST_BINOP_ABBREV)
          AbbrevToUse = FUNCTION_INST_BINOP_FLAGS_ABBREV;
        Vals.push_back(Flags);
      }
      */
    }
    break;

  case Instruction::GetElementPtr:
    /*
    Code = bitc::FUNC_CODE_INST_GEP;
    if (cast<GEPOperator>(&I)->isInBounds())
      Code = bitc::FUNC_CODE_INST_INBOUNDS_GEP;
    for (unsigned i = 0, e = I->getNumOperands(); i != e; ++i)
      PushValueAndType(I->getOperand(i), InstID, Vals, VE);
    */
    break;
  case Instruction::ExtractValue: {
   /*
    Code = bitc::FUNC_CODE_INST_EXTRACTVAL;
    PushValueAndType(I->getOperand(0), InstID, Vals, VE);
    const ExtractValueInst *EVI = cast<ExtractValueInst>(&I);
    for (unsigned *i = EVI->idx_begin(), *e = EVI->idx_end(); i != e; ++i)
      Vals.push_back(*i);
    */
    break;
  }
  case Instruction::InsertValue: {
    /*
    Code = bitc::FUNC_CODE_INST_INSERTVAL;
    PushValueAndType(I->getOperand(0), InstID, Vals, VE);
    PushValueAndType(I->getOperand(1), InstID, Vals, VE);
    const InsertValueInst *IVI = cast<InsertValueInst>(&I);
    for (unsigned *i = IVI->idx_begin(), *e = IVI->idx_end(); i != e; ++i)
      Vals.push_back(*i);
    */
    break;
  }
  case Instruction::Select:
    /*
    Code = bitc::FUNC_CODE_INST_VSELECT;
    PushValueAndType(I->getOperand(1), InstID, Vals, VE);
    Vals.push_back(VE.getValueID(I->getOperand(2)));
    PushValueAndType(I->getOperand(0), InstID, Vals, VE);
    */
    break;
  case Instruction::ExtractElement:
    /*
    Code = bitc::FUNC_CODE_INST_EXTRACTELT;
    PushValueAndType(I->getOperand(0), InstID, Vals, VE);
    Vals.push_back(VE.getValueID(I->getOperand(1)));
    */
    break;
  case Instruction::InsertElement:
    /*
    Code = bitc::FUNC_CODE_INST_INSERTELT;
    PushValueAndType(I->getOperand(0), InstID, Vals, VE);
    Vals.push_back(VE.getValueID(I->getOperand(1)));
    Vals.push_back(VE.getValueID(I->getOperand(2)));
    */
    break;
  case Instruction::ShuffleVector:
    /*
    Code = bitc::FUNC_CODE_INST_SHUFFLEVEC;
    PushValueAndType(I->getOperand(0), InstID, Vals, VE);
    Vals.push_back(VE.getValueID(I->getOperand(1)));
    Vals.push_back(VE.getValueID(I->getOperand(2)));
    */
    break;
  case Instruction::ICmp:
  case Instruction::FCmp:
    // compare returning Int1Ty or vector of Int1Ty
    /*
    Code = bitc::FUNC_CODE_INST_CMP2;
    PushValueAndType(I->getOperand(0), InstID, Vals, VE);
    Vals.push_back(VE.getValueID(I->getOperand(1)));
    Vals.push_back(cast<CmpInst>(I).getPredicate());
    */
    break;

  case Instruction::Ret:
    {
      /*
      Code = bitc::FUNC_CODE_INST_RET;
      unsigned NumOperands = I->getNumOperands();
      if (NumOperands == 0)
        AbbrevToUse = FUNCTION_INST_RET_VOID_ABBREV;
      else if (NumOperands == 1) {
        if (!PushValueAndType(I->getOperand(0), InstID, Vals, VE))
          AbbrevToUse = FUNCTION_INST_RET_VAL_ABBREV;
      } else {
        for (unsigned i = 0, e = NumOperands; i != e; ++i)
          PushValueAndType(I->getOperand(i), InstID, Vals, VE);
      }
      */
    }
    break;
  case Instruction::Br:
    {
      /*
      Code = bitc::FUNC_CODE_INST_BR;
      BranchInst &II = cast<BranchInst>(I);
      Vals.push_back(VE.getValueID(II->getSuccessor(0)));
      if (II->isConditional()) {
        Vals.push_back(VE.getValueID(II->getSuccessor(1)));
        Vals.push_back(VE.getValueID(II->getCondition()));
      }
      */
    }
    break;
  case Instruction::Switch:
    /*
    Code = bitc::FUNC_CODE_INST_SWITCH;
    Vals.push_back(VE.getTypeID(I->getOperand(0)->getType()));
    for (unsigned i = 0, e = I->getNumOperands(); i != e; ++i)
      Vals.push_back(VE.getValueID(I->getOperand(i)));
    */
    break;
  case Instruction::IndirectBr:
    /*
    Code = bitc::FUNC_CODE_INST_INDIRECTBR;
    Vals.push_back(VE.getTypeID(I->getOperand(0)->getType()));
    for (unsigned i = 0, e = I->getNumOperands(); i != e; ++i)
      Vals.push_back(VE.getValueID(I->getOperand(i)));
    */
    break;
      
  case Instruction::Invoke: {
    /*
    const InvokeInst *II = cast<InvokeInst>(&I);
    const Value *Callee(II->getCalledValue());
    PointerType *PTy = cast<PointerType>(Callee->getType());
    FunctionType *FTy = cast<FunctionType>(PTy->getElementType());
    Code = bitc::FUNC_CODE_INST_INVOKE;

    Vals.push_back(VE.getAttributeID(II->getAttributes()));
    Vals.push_back(II->getCallingConv());
    Vals.push_back(VE.getValueID(II->getNormalDest()));
    Vals.push_back(VE.getValueID(II->getUnwindDest()));
    PushValueAndType(Callee, InstID, Vals, VE);

    // Emit value #'s for the fixed parameters.
    for (unsigned i = 0, e = FTy->getNumParams(); i != e; ++i)
      Vals.push_back(VE.getValueID(I->getOperand(i)));  // fixed param.

    // Emit type/value pairs for varargs params.
    if (FTy->isVarArg()) {
      for (unsigned i = FTy->getNumParams(), e = I->getNumOperands()-3;
           i != e; ++i)
        PushValueAndType(I->getOperand(i), InstID, Vals, VE); // vararg
    }
    */
    break;
  }
  case Instruction::Resume:
    /*
    Code = bitc::FUNC_CODE_INST_RESUME;
    PushValueAndType(I->getOperand(0), InstID, Vals, VE);
    */
    break;
  case Instruction::Unwind:
    /*
    Code = bitc::FUNC_CODE_INST_UNWIND;
    */
    break;
  case Instruction::Unreachable:
    /*
    Code = bitc::FUNC_CODE_INST_UNREACHABLE;
    AbbrevToUse = FUNCTION_INST_UNREACHABLE_ABBREV;
    */
    break;

  case Instruction::PHI: {
    /*
    const PHINode &PN = cast<PHINode>(I);
    Code = bitc::FUNC_CODE_INST_PHI;
    Vals.push_back(VE.getTypeID(PN.getType()));
    for (unsigned i = 0, e = PN.getNumIncomingValues(); i != e; ++i) {
      Vals.push_back(VE.getValueID(PN.getIncomingValue(i)));
      Vals.push_back(VE.getValueID(PN.getIncomingBlock(i)));
    }
    */
    break;
  }

  case Instruction::LandingPad: {
    /*
    const LandingPadInst &LP = cast<LandingPadInst>(I);
    Code = bitc::FUNC_CODE_INST_LANDINGPAD;
    Vals.push_back(VE.getTypeID(LP.getType()));
    PushValueAndType(LP.getPersonalityFn(), InstID, Vals, VE);
    Vals.push_back(LP.isCleanup());
    Vals.push_back(LP.getNumClauses());
    for (unsigned I = 0, E = LP.getNumClauses(); I != E; ++I) {
      if (LP.isCatch(I))
        Vals.push_back(LandingPadInst::Catch);
      else
        Vals.push_back(LandingPadInst::Filter);
      PushValueAndType(LP.getClause(I), InstID, Vals, VE);
    }
    */
    break;
  }

  case Instruction::Alloca:
    /*
    Code = bitc::FUNC_CODE_INST_ALLOCA;
    Vals.push_back(VE.getTypeID(I->getType()));
    Vals.push_back(VE.getTypeID(I->getOperand(0)->getType()));
    Vals.push_back(VE.getValueID(I->getOperand(0))); // size.
    Vals.push_back(Log2_32(cast<AllocaInst>(I).getAlignment())+1);
    */
    break;

  case Instruction::Load:
    /*
    if (cast<LoadInst>(I).isAtomic()) {
      Code = bitc::FUNC_CODE_INST_LOADATOMIC;
      PushValueAndType(I->getOperand(0), InstID, Vals, VE);
    } else {
      Code = bitc::FUNC_CODE_INST_LOAD;
      if (!PushValueAndType(I->getOperand(0), InstID, Vals, VE))  // ptr
        AbbrevToUse = FUNCTION_INST_LOAD_ABBREV;
    }
    Vals.push_back(Log2_32(cast<LoadInst>(I).getAlignment())+1);
    Vals.push_back(cast<LoadInst>(I).isVolatile());
    if (cast<LoadInst>(I).isAtomic()) {
      Vals.push_back(GetEncodedOrdering(cast<LoadInst>(I).getOrdering()));
      Vals.push_back(GetEncodedSynchScope(cast<LoadInst>(I).getSynchScope()));
    }
    */
    {
      //Value *V = I;
     /*
      std::string vnm = V->getNameStr();
      if (isa<GlobalValue>) {
        GlobalValue *gv = M->getNamedValue( "@"+vnm );
      }
      else {
        StringRef nm = isa<GlobalValue>(V)? ("@"+vnm): ("%"+vnm);
     */
      //Args.push_back(V);
    }
    Args.push_back(I->getOperand(0));
    break;
  case Instruction::Store:
    /*
    if (cast<StoreInst>(I).isAtomic())
      Code = bitc::FUNC_CODE_INST_STOREATOMIC;
    else
      Code = bitc::FUNC_CODE_INST_STORE;
    PushValueAndType(I->getOperand(1), InstID, Vals, VE);  // ptrty + ptr
    Vals.push_back(VE.getValueID(I->getOperand(0)));       // val.
    Vals.push_back(Log2_32(cast<StoreInst>(I).getAlignment())+1);
    Vals.push_back(cast<StoreInst>(I).isVolatile());
    if (cast<StoreInst>(I).isAtomic()) {
      Vals.push_back(GetEncodedOrdering(cast<StoreInst>(I).getOrdering()));
      Vals.push_back(GetEncodedSynchScope(cast<StoreInst>(I).getSynchScope()));
    }
    */
    Args.push_back(I->getOperand(0));
    Args.push_back(I->getOperand(1));
    break;
  case Instruction::AtomicCmpXchg:
    /*
    Code = bitc::FUNC_CODE_INST_CMPXCHG;
    PushValueAndType(I->getOperand(0), InstID, Vals, VE);  // ptrty + ptr
    Vals.push_back(VE.getValueID(I->getOperand(1)));       // cmp.
    Vals.push_back(VE.getValueID(I->getOperand(2)));       // newval.
    Vals.push_back(cast<AtomicCmpXchgInst>(I).isVolatile());
    Vals.push_back(GetEncodedOrdering(
                     cast<AtomicCmpXchgInst>(I).getOrdering()));
    Vals.push_back(GetEncodedSynchScope(
                     cast<AtomicCmpXchgInst>(I).getSynchScope()));
    */
    break;
  case Instruction::AtomicRMW:
    /*
    Code = bitc::FUNC_CODE_INST_ATOMICRMW;
    PushValueAndType(I->getOperand(0), InstID, Vals, VE);  // ptrty + ptr
    Vals.push_back(VE.getValueID(I->getOperand(1)));       // val.
    Vals.push_back(GetEncodedRMWOperation(
                     cast<AtomicRMWInst>(I).getOperation()));
    Vals.push_back(cast<AtomicRMWInst>(I).isVolatile());
    Vals.push_back(GetEncodedOrdering(cast<AtomicRMWInst>(I).getOrdering()));
    Vals.push_back(GetEncodedSynchScope(
                     cast<AtomicRMWInst>(I).getSynchScope()));
    */
    break;
  case Instruction::Fence:
    /*
    Code = bitc::FUNC_CODE_INST_FENCE;
    Vals.push_back(GetEncodedOrdering(cast<FenceInst>(I).getOrdering()));
    Vals.push_back(GetEncodedSynchScope(cast<FenceInst>(I).getSynchScope()));
    */
    break;
  case Instruction::Call: {
    /*
    const CallInst &CI = cast<CallInst>(I);
    PointerType *PTy = cast<PointerType>(CI.getCalledValue()->getType());
    FunctionType *FTy = cast<FunctionType>(PTy->getElementType());

    Code = bitc::FUNC_CODE_INST_CALL;

    Vals.push_back(VE.getAttributeID(CI.getAttributes()));
    Vals.push_back((CI.getCallingConv() << 1) | unsigned(CI.isTailCall()));
    PushValueAndType(CI.getCalledValue(), InstID, Vals, VE);  // Callee

    // Emit value #'s for the fixed parameters.
    for (unsigned i = 0, e = FTy->getNumParams(); i != e; ++i)
      Vals.push_back(VE.getValueID(CI.getArgOperand(i)));  // fixed param.

    // Emit type/value pairs for varargs params.
    if (FTy->isVarArg()) {
      for (unsigned i = FTy->getNumParams(), e = CI.getNumArgOperands();
           i != e; ++i)
        PushValueAndType(CI.getArgOperand(i), InstID, Vals, VE);  // varargs
    }
    */
    break;
  }
  case Instruction::VAArg:
    /*
    Code = bitc::FUNC_CODE_INST_VAARG;
    Vals.push_back(VE.getTypeID(I->getOperand(0)->getType()));   // valistty
    Vals.push_back(VE.getValueID(I->getOperand(0))); // valist.
    Vals.push_back(VE.getTypeID(I->getType())); // restype.
    */
    break;
  }

  return Args;
}


}//namespace

char ChaoModule::ID = 0;
static RegisterPass<ChaoModule> X("chaomodule", "Chao's Module Pass");
