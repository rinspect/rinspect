//===- TAP_InstrumentCall.cpp - "LLVM Pass for Calls" ---------------------===//
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
#include <cxxabi.h>
#include "llvm/Pass.h"
#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/Instructions.h"
#include "llvm/IntrinsicInst.h"
#include "llvm/Constants.h"
#include "llvm/Type.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

#if 1
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#endif

STATISTIC(ModuleCounter, "Counts number of modules greeted");

// Command-line flags. {{{1
static cl::opt<std::string>
    LuConfigFileName("lu-config",
               cl::desc("Configuration file of the type state automaton"));

namespace {

std::map<StringRef,GlobalVariable*>  funcName_to_globalVar;

CallInst* TAP_createCallInstPre(CallInst *I);
CallInst* TAP_createCallInstPost(CallInst *I);
CallInst* TAP_createInvokeInstPre(InvokeInst *I);
CallInst* TAP_createInvokeInstPost(InvokeInst *I);
Constant *TAP_getInstructionNameExpr(Instruction *I);
Constant *TAP_getInstTypeNameExpr(Instruction *I);
Constant *TAP_getStringNameExpr(Module *M, StringRef &str);
StringRef TAP_demangleCxxName(StringRef &mangled);
bool TAP_skipFunction(StringRef &fname, const char *typestr);


struct TAP_InstrumentCallInst : public ModulePass {

  static char ID;

  TAP_InstrumentCallInst() : ModulePass(ID) {}

  void TAP_declareFunctions(Module *M);
  void TAP_instrumentBasicBlock_Call(BasicBlock *B);
  bool TAP_mayEscape(Instruction *I);

  virtual void getAnalysisUsage(AnalysisUsage &AU) const {
    AU.addRequiredTransitive<AliasAnalysis>();
  }

  virtual bool runOnModule(Module &M) {
    ++ModuleCounter;
    errs() << "TAP_InstrumentCallInst : ";
    errs().write_escaped(M.getModuleIdentifier()) << '\n';

    TAP_declareFunctions(&M);

    for (Module::iterator F = M.begin(); F != M.end(); F++) {
      StringRef fname = F->getName();
      //-------------------------------------------------------------------
      //chao: 7/22/2013, we may not want to skip the definitions,
      //because some of the class Constructors that we are interested
      //in monitoring may be called within __cxx_global_var_init()
      // 
      //if (TAP_skipFunction(fname, "runOnF"))  continue;
      //-------------------------------------------------------------------
      for (Function::iterator B = F->begin(); B != F->end(); B++) {
        TAP_instrumentBasicBlock_Call(B);
      }
    }

    return false;
  }

};


void TAP_InstrumentCallInst::TAP_declareFunctions(Module *M)
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
  M->getOrInsertFunction("clap_call_pre"  , FT);
  M->getOrInsertFunction("clap_call_post" , FT);
}

bool TAP_skipFunction(StringRef &fname, const char *typestr)
{
  //  return true;

  if (!strncmp("clap_", fname.data(), 5)) {
    //skip the CLAP function calls
    return true;
  }

  if (1) {
    //skip the C++ standard functions calls
    StringRef fname_new = TAP_demangleCxxName(fname);
    char str[256];
    strncpy(str, fname_new.data(), 255);

    errs()<< typestr << " check " << str << "\n";

    if (!strncmp("std::", str, 5)) {
      return true;
    }
    else if (!strncmp("void std::", str, 10)) {
      return true;
    }
    else if (!strncmp("bool std::", str, 10)) {
      return true;
    }
    else if (!strncmp("int* std::", str, 10)) {
      return true;
    }
    else if (!strncmp("unsigned int const& std::", str, 25)) {
      return true;
    }
    else if (!strncmp("__gnu_cxx::", str, 11)) {
      return true;
    }
    else if (!strncmp("__cxa", str, 5)) {
      return true;
    }
    else if (!strncmp("__cxx", str, 5)) {
      return true;
    }
    else if (!strncmp("__gxx", str, 5)) {
      return true;
    }
    else if (!strncmp("llvm.", str, 5)) {
      return true;
    }
    else if (!strncmp("printf", str, 6)) {
      return true;
    }
    else if (!strncmp("pthread_self", str, 12)) {
      return true;
    }
    else if (!strncmp("operator new", str, 12)) {
      return true;
    }
    else if (!strncmp("operator delete", str, 15)) {
      return true;
    }

#if 0
    //---------------------------------------------------------- 
    // Chao: 10/1/2012, a hack for Lu's Thrift experiments
    //       skip all calls that are not "pthread_xxx" calls
    // --------------------------------------------------
    if (strncmp("pthread_",str,8)) {
      return true;
    }
#endif


#if 1 
  //lu:filter the function calls


//    if(strstr(str,"my_class::")==0) return true;

    static bool valid_filter=false;
    static bool already_read=false;
    static vector<string> filter;
//    errs() <<"File name: "<<LuConfigFileName<< '\n';


    if(already_read==false)
    {
      string line;
      ifstream myfile (LuConfigFileName.c_str());
      if (myfile.is_open())
      {
        while ( myfile.good() )
        {
          getline (myfile,line);

          if(line.length()>0){
	    errs() << LuConfigFileName.c_str() << "\t readLine: " << line << "\n";
	    filter.push_back(line);
          }
        }
        myfile.close();
        valid_filter=true;
      }

      else {
	errs() << LuConfigFileName.c_str() << ":Unable to open file";
	valid_filter=false;
      }
      already_read=true;
    }


    if(valid_filter){
		vector<string>::iterator it;
		string item;


		bool match=false;
		for(it=filter.begin();it!=filter.end();it++){
			item=(string)*it;
	    		errs()<<"\t Filter: "<<(string)*it<<"\n";

			if(strstr (str,item.c_str())) {
			        errs()<<"\t   Match: "<<item<<"\n";
	//			return false;
				match=true;
				break;
			}
		}
		if(match==false) return true;
    }
#endif


    errs()<< typestr << " keep " << str << "\n";
  }

  return false;
}



// for each LLVM instruction (LoadInst or StoreInst) 
//
//    %x = call @foo 
//
// transform it to
//
//    call @clap_call_pre  (1, "@foo");
//    %x = call @foo
//    call @clap_call_post (1, "@foo");
//
void TAP_InstrumentCallInst::TAP_instrumentBasicBlock_Call(BasicBlock *B)
{
  // for each function, prepare the "PRE" and "POST" calls
  std::vector<BasicBlock::iterator> insertPts;
  std::vector<CallInst*> insertPreIs;
  std::vector<CallInst*> insertPostIs;
  for (BasicBlock::iterator I = B->begin(); I != B->end(); I++) {

    if (CallInst *callI = dyn_cast<CallInst>(I)) {

//    	errs () << "3:cxx not skipped call" << " : " <<  fname << "\n";
      //skip the LLVM intrisic calls
      if (dyn_cast<IntrinsicInst>(callI) != NULL) continue;
      //skip unknown function calls
      if (callI->getCalledFunction() == NULL) continue;
      //skip CLAP function (and other function) calls
      StringRef fname = callI->getCalledFunction()->getName();

//      errs () << "1:cxx not skipped call" << " : " <<  fname << "\n";

      if (TAP_skipFunction(fname,"Call  ")) continue;

//      errs () << "2:cxx not skipped call" << " : " <<  fname << "\n";



      CallInst *preI  = TAP_createCallInstPre(callI);  //create "PRE"
      CallInst *postI = NULL;
      if (I->isTerminator() == false) {
        postI = TAP_createCallInstPost(callI); //create "POST"
      }
      insertPts.push_back(I);
      insertPreIs.push_back(preI);
      insertPostIs.push_back(postI);

    }
    else if (InvokeInst *invokeI = dyn_cast<InvokeInst>(I)) {
      //skip the LLVM intrisic calls
      if (dyn_cast<IntrinsicInst>(invokeI) != NULL) continue;
      //skip unknown function calls
      if (invokeI->getCalledFunction() == NULL)  continue;
      //if (invokeI->isTerminator())  continue;
      //skip CLAP function (and other function) calls
      StringRef fname = invokeI->getCalledFunction()->getName();
//      errs () << "1:cxx not skipped invoke"  << " : " <<  fname << "\n";

      if (TAP_skipFunction(fname,"Invoke")) continue;

//      errs () << "2:cxx not skipped invoke"  << " : " <<  fname << "\n";

      CallInst *preI  = TAP_createInvokeInstPre(invokeI);  //create "PRE"
      CallInst *postI = NULL;
      if (I->isTerminator() == false) {
        postI = TAP_createInvokeInstPost(invokeI); //create "POST"
      }
      insertPts.push_back(I);
      insertPreIs.push_back(preI);
      insertPostIs.push_back(postI);
    }
  }
  // inserting the "PRE" and "POST" calls
  for (unsigned int n=0; n<insertPts.size(); n++) {
    if (insertPreIs[n] != NULL)
      B->getInstList().insert( insertPts[n], insertPreIs[n] );
    if (insertPostIs[n] != NULL)
      B->getInstList().insertAfter( insertPts[n], insertPostIs[n] );
  }
}

StringRef TAP_demangleCxxName(StringRef &mangled)
{
  StringRef res = mangled;

  int status;
  char *str = abi::__cxa_demangle(mangled.data(), 0, 0, &status);
  if (status == 0) {
    res = StringRef(str);
  }

  return res;
}

Constant *TAP_getStringNameExpr(Module *M, StringRef &f_nm_mangled)
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


// given the CallInst, create a constrant string expr of the func name
Constant *TAP_getCalledFuncNameExpr(CallInst *I)
{
  StringRef f_nm = I->getCalledFunction()->getName();
  Module *M = I->getParent()->getParent()->getParent();
  Constant *val = TAP_getStringNameExpr(M, f_nm);
  return val;
}


// for each function call instruction
//      @foo (%a, %b)
// create a new call instruction
//      call @clap_call_pre  ( @foo,  %a, %b );
//
CallInst* TAP_createCallInstPre(CallInst *I)
{
  CallInst *preI = NULL;

  Module *M = I->getParent()->getParent()->getParent();
  LLVMContext &C = M->getContext();
  Value *preFunc  = M->getFunction("clap_call_pre");

  std::vector<Value*> Args;
  unsigned int numArgs = I->getNumArgOperands();
  {
    // first parameter: how many argument will there be?
    Constant *val = ConstantInt::get(C, APInt(32,numArgs+1));
    Args.push_back( val );
  }
  {
    // second parameter: a string of the function's name
    Constant *f_name_ptr = TAP_getCalledFuncNameExpr(I);
    Args.push_back( f_name_ptr );
  }
  for (unsigned int n = 0; n < numArgs; n++) {
    // third parameter: the returned value
    Args.push_back( I->getArgOperand(n) );
  }

  preI  = CallInst::Create(preFunc, Args);
  return preI;
}


// for each function call instruction
//      @foo (%a, %b)
// create a new call instruction
//      call @TAP_call_post  ( @foo,  %a, %b );
// for inspect
CallInst* TAP_createCallInstPost(CallInst *I)
{
  CallInst *postI = NULL;

  Module *M = I->getParent()->getParent()->getParent();
  LLVMContext &C = M->getContext();
  Value *postFunc  = M->getFunction("clap_call_post");

  std::vector<Value*> Args;

#if 1
//----------------------------------------------------------------------------
// chao: 1/10/2013, below is Lu's code -- I don't understand it, but it's 
// causing "src/examples/lincheck/QuasiStack/QuasiStack.cc" to fail
//----------------------------------------------------------------------------

//  int numArgs = I->getNumArgOperands();  
  int numArgs = 1;
#endif

  if ( I->getType()->isVoidTy() == false ){
	  numArgs++;
  }
  {
    // first parameter: how many argument will there be?
    Constant *val = ConstantInt::get(C, APInt(32,numArgs+1));
    Args.push_back( val );
  }
  {
    // second parameter: a string of the function's name
    Constant *f_name_ptr = TAP_getCalledFuncNameExpr(I);
    Args.push_back( f_name_ptr );
  }
  if ( I->getType()->isVoidTy() == false ) {
    // third parameter: the returned value
    Args.push_back((Value*)I);
  }

#if 1
//----------------------------------------------------------------------------
// chao: 1/10/2013, if the above change by Lu is correct (intended), then 
// we should not add the original parameters of the method
//----------------------------------------------------------------------------
  for (unsigned int n = 0; n < I->getNumArgOperands(); n++) {
     // third parameter: the returned value
     Args.push_back( I->getArgOperand(n) );
   }
#endif


  postI  = CallInst::Create(postFunc, Args);
  return postI;
}

// given the InvokeInst, create a constrant string expr of the func name
Constant *TAP_getInvokedFuncNameExpr(InvokeInst *I)
{
  StringRef f_nm = I->getCalledFunction()->getName();
  Module *M = I->getParent()->getParent()->getParent();
  Constant *val = TAP_getStringNameExpr(M, f_nm);

  //errs() << "invokedFuncName = ";
  //errs().write_escaped(f_nm) << '\n';

  return val;
}


// for each function call instruction
//      @foo (%a, %b)
// create a new call instruction
//      call @clap_call_pre  ( @foo,  %a, %b );
//
CallInst* TAP_createInvokeInstPre(InvokeInst *I)
{
  CallInst *preI = NULL;

  Module *M = I->getParent()->getParent()->getParent();
  LLVMContext &C = M->getContext();
  Value *preFunc  = M->getFunction("clap_call_pre");

  std::vector<Value*> Args;
  unsigned int numArgs = I->getNumArgOperands();
  {
    // first parameter: how many argument will there be?
    Constant *val = ConstantInt::get(C, APInt(32,numArgs+1));
    Args.push_back( val );
  }
  {
    // second parameter: a string of the function's name
    Constant *f_name_ptr = TAP_getInvokedFuncNameExpr(I);
    Args.push_back( f_name_ptr );
  }
  for (unsigned int n = 0; n < numArgs; n++) {
    // third parameter: the returned value
    Args.push_back( I->getArgOperand(n) );
  }

  preI  = CallInst::Create(preFunc, Args);
  return preI;
}


// for each function call instruction
//      @foo (%a, %b)
// create a new call instruction
//      call @TAP_call_post  ( @foo,  %a, %b );
//
CallInst* TAP_createInvokeInstPost(InvokeInst *I)
{
  CallInst *postI = NULL;

  Module *M = I->getParent()->getParent()->getParent();
  LLVMContext &C = M->getContext();
  Value *postFunc  = M->getFunction("clap_call_post");

  std::vector<Value*> Args;
  int numArgs = I->getNumArgOperands();
  {
    // first parameter: how many argument will there be?
    Constant *val = ConstantInt::get(C, APInt(32,numArgs+1));
    Args.push_back( val );
  }
  {
    // second parameter: a string of the function's name
    Constant *f_name_ptr = TAP_getInvokedFuncNameExpr(I);
    Args.push_back( f_name_ptr );
  }
  if ( I->getType()->isVoidTy() == false ) {
    // third parameter: the returned value
    Args.push_back((Value*)I);
  }

  postI  = CallInst::Create(postFunc, Args);
  return postI;
}


bool TAP_InstrumentCallInst::TAP_mayEscape(Instruction *I)
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


}//namespace

char TAP_InstrumentCallInst::ID = 0;
static RegisterPass<TAP_InstrumentCallInst> X("tap_call",
                                             "TAP Function Call Pass");
