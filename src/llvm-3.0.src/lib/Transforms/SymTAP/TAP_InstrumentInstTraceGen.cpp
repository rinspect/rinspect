//===- TAP_InstrumentInstTraceGen.cpp - "LLVM Pass for Calls" -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Author: Chao Wang <chaowang@vt.edu>
//         Bing Liu
// Date: 11-22-2012 23:18 pm
//
// Description: Weakest Pre-Condition part updated;
//              Left tasks:
//                1. add the update of count_Trace[];
//                2. check the correctness of WP calculation and WP formula translation;
//                3. replace function need to be re-considered;
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "chao"
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cxxabi.h>
#include "llvm/Pass.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/DerivedTypes.h"
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
#include "llvm/Support/CommandLine.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//This header file defined the class of branch State <bState>;
#include <SymTAP.h>
#include <TableWP.h>
#include <BLiuValue.h>
#include <stack>
#include <vector>

//chao, this is a hack
#include "../../../../smt_dp/yices_dp.hh"

#define DBG_MSG(A)  errs()<< "warning in file: " << __FILE__ << ", line: " \
  << __LINE__ << " : " << (A)                                           

using namespace llvm;

STATISTIC(ModuleCounter, "Counts number of modules greeted");

static cl::opt<std::string> 
InputTraceFile("tap-tgen-in", cl::init(""),
               cl::desc("Specify TAP inst id trace input filename"));

static cl::opt<std::string>
OutputTraceFile("tap-tgen-out", cl::init(""),
               cl::desc("Specify TAP inst trace output filename"));

static cl::opt<int>
DebugLevel("tap-tgen-dbg", cl::init(0),
               cl::desc("Specify TAP inst trace debug flag"));

static cl::opt<std::string>
TargetExeName("tap-tgen-target", cl::init(""),
               cl::desc("Specify TAP inst generated exe name"));






namespace {

struct TAP_InstrumentInstTraceGen : public ModulePass {

  static char ID; 

  static int havoc_v_cnt;

  //mapping from inst.clap_id to Instruction*
  std::map<int, Instruction*> id_to_inst_table;
  //
  std::vector<int> tid_Trace;
  std::vector<int> id_Trace;
  std::vector<int> stat_Trace;
  std::vector<int> retval_Trace;         // the return values;
  //
  std::vector<Instruction*> inst_Trace;

  std::vector<bState> branch_list;
  std::vector<int> branch_index;                                  //save the index of each branch statement match branch_list;
  tableWP wptbl;                                  //table of weakest precondition;

  bool flag;
  bool rflag;       // the flag indicate whether the current trace is a copy of last run trace;
  int tc_rank;      // the index of the generated test case file;

  int Depth;
  std::map<std::string, int> function_retval;  

  // Precondition: 
  //map<std::string, int> wpmap;

  typedef pair<int,int>   uniqueInstId;
  std::map<uniqueInstId, BLiuValue*>  WP_TABLE;
  //std::vector<int> count_Trace;                         // record the appearance times; Can be updated every execution time; Should be global;
  std::map<int, int> count_Trace;       // Record branch point and appearance times;

  /////////////////////////////////////////////////// END OF VARIABLE AND DATA STRUCTURE DEFINITION ///////////////////////////////////////




  TAP_InstrumentInstTraceGen() : ModulePass(ID) {}

  virtual bool runOnModule(Module &M) {
    ++ModuleCounter;
    errs() << "TAP_InstrumentInstTraceGen : ";
    errs().write_escaped(M.getModuleIdentifier()) << '\n';

      TAP_declareAssumeFunction(M);
      TAP_createIdToInstructionMap(M);

      // Depth; this varible finally should get from a file, not assigned Here.
      Depth = 20;                           // Here set to 20 just in order to make sure the ordinary operation will not be affect;

      //For each work, they just check whether the traversed the complete sub tree;
      for(int k = 0; k<= Depth; k++){
        bState init_bState;
        init_bState.index = k;
        init_bState.bEnable.clear();
        branch_list.push_back(init_bState);
      }

      tc_rank = 0;                   // the generated test case folder will be test case1, test case2 ...
      string buffer;

      
      while(!branch_list.empty()){                          
        for(int k = 0; k <= Depth; k++){
          if(branch_list.back().bEnable.empty()){
            branch_list.pop_back();
          }
        }
        if(branch_list.empty()){
          errs()<<" Cleared the fake bStates!!!\n";
        }
        
	      // make a copy for trace.txt;
        ostringstream trn;
        trn << tc_rank + 1;
        string outstr = trn.str();
        string tra_cmd = "cp trace.txt trace_" + outstr +".txt";
        system(tra_cmd.c_str());


        TAP_readIdTraceFromFile(M);
        TAP_convertIdTraceToInstructionTrace(M);
        TAP_outputInstructionTrace(M);
        TAP_traceSymbolicExecution(M);

        //restore the generated test case file;
        system("cp out.txt tap.input.txt");

        // make different test case folder;
        ostringstream convert;
        convert << ++tc_rank;
        buffer = convert.str();

        string dir_cmd = "mkdir test_case_" + buffer;
        system(dir_cmd.c_str());


        string des_dir = "cp tap.input.txt ./test_case_" + buffer;
        system(des_dir.c_str());                              // miss the first havoc value;
        

	      TAP_calculateWeakestPreCondition();  
        TAP_deleteInstructionTrace(M);
        
        if(rflag)
          break;            // if the trace is redundant, jump out the loop;

        //clear all the record for previous execution;
        rflag = false;
        inst_Trace.clear();
        tid_Trace.clear();
        id_Trace.clear();
        stat_Trace.clear();
        retval_Trace.clear();
        function_retval.clear();          //save function return value with the related instruction name;

        havoc_v_cnt = 0;
        //for bit vector:
        
        string cmd = "./" + TargetExeName + ".exe; cp trace.txt in.txt";
        system(cmd.c_str());

      errs()<<" The size of branch_list at last: "<<branch_list.size()<<"\n";
      
      
    }
    
    string del_file = "rm test_case_" + buffer + "/tap.input.txt";       //left the last folder for the default test case;
    system(del_file.c_str());  
     
    return false;
  }

  bool TAP_mayEscape(Instruction *I);
  virtual void getAnalysisUsage(AnalysisUsage &AU) const {
    AU.addRequiredTransitive<AliasAnalysis>();
  }


  int TAP_getMetadataValue(Instruction *I, std::string kind) {
    //Bing: what's this for?
    if (MDNode *N = I->getMetadata(kind.c_str())) {
      Value *vid = N->getOperand(0);
      if (ConstantInt* cid = dyn_cast<ConstantInt>(vid)) {
        int id = cid->getLimitedValue();
        return id;
      }
    }
    return -1; // illegal value
  }

  void TAP_createIdToInstructionMap(Module &M) {
    // building the map from inst ID to Instruction*
    for (Module::iterator F = M.begin(); F != M.end(); F++) {
      for (Function::iterator B = F->begin(); B != F->end(); B++) {
        for (BasicBlock::iterator I = B->begin(); I != B->end(); I++) {
          int id = TAP_getMetadataValue(I,"clap");

          if (id >= 0) {
            id_to_inst_table[id] = I;
            
            if (DebugLevel > 0) {
              errs() << "inst[" << id << "] = ";
              I->print(errs());  
              errs() << "\n";
            }
          }
        }
      }
    }
  }

  void TAP_readIdTraceFromFile(Module &M) {
    
    // reading the ID trace from the input file
    std::ifstream Input(InputTraceFile.c_str());

    if (Input.good()) {
      
      while (!Input.eof()) {
        std::string s_tid, s_inst_id, s_stat, s_retval;
        Input >> s_tid >> s_inst_id >> s_stat >> s_retval;
        if (s_tid != "" && s_inst_id != "" && s_stat != "" && s_retval != "") {
          int tid  = atoi(s_tid.c_str());
          int inst_id = atoi(s_inst_id.c_str());
          int stat = atoi(s_stat.c_str());
          int retval = atoi(s_retval.c_str());
          tid_Trace.push_back(tid);
          id_Trace.push_back(inst_id);
          stat_Trace.push_back(stat);
          retval_Trace.push_back(retval);

          if (DebugLevel > 0) {
            //errs() << s_tid << " " << s_inst_id << " " << s_stat << "\n";
            errs() << s_tid << " " << s_inst_id << " " << s_stat << " " << s_retval << "\n";
          }
        }
      }
    }
  }

  std::map<int,std::vector<std::string> > thread_2_call_stack;
  std::map<int,std::vector<Value*> > thread_2_retv_stack;
  std::map<int,std::vector<std::map<Value*,Value*> > > thread_2_vmap_stack;

  void TAP_thread_2_call_stack_init() {

    thread_2_call_stack.clear();
    thread_2_retv_stack.clear();
    thread_2_vmap_stack.clear();

    for (unsigned int i=0; i<tid_Trace.size(); i++) {
      int tid = tid_Trace[i];

      std::vector<std::string> call_stack;
      call_stack.push_back("T" + itostr(tid) + ((tid==1)?"_main":""));
      thread_2_call_stack[tid] = call_stack;

      std::vector<Value*> retv_stack;
      retv_stack.push_back(NULL);
      thread_2_retv_stack[tid] = retv_stack;

      std::vector<std::map<Value*,Value*> > vmap_stack;
      vmap_stack.push_back( std::map<Value*,Value*>() );
      thread_2_vmap_stack[tid] = vmap_stack;
    }
  }

  void TAP_thread_2_call_stack_update(int tid, Instruction* I, Instruction* newI, int stat, int n_index) {

    std::vector<std::string>& call_stack = thread_2_call_stack[tid];
    std::vector<Value*>& retv_stack = thread_2_retv_stack[tid];
    std::vector<std::map<Value*,Value*> >& vmap_stack = thread_2_vmap_stack[tid];
    
    
    if (CallInst* callI = dyn_cast<CallInst>(I)) {
      
      // skip the "clap_...()" and "tap_...()" functions
      if (callI->getCalledFunction() != NULL) { // chao: added on 10/25/2012

      const char* fname = callI->getCalledFunction()->getName().data();
      if ( strncmp(fname,"clap_",5) != 0 && strncmp(fname,"tap_",4) != 0 ) {

        if (stat == 1) {
          //This is the beginning of the call 
          if (DebugLevel > 1)     errs() << "\n PUSH call stack\n";

          call_stack.push_back(callI->getCalledFunction()->getName());
          //thread_2_call_stack[tid] = call_stack;
          retv_stack.push_back( callI->hasName()? callI:NULL );
          //thread_2_retv_stack[tid] = retv_stack;
          
          // after entering the function, replace formal args with actual args
          std::map<Value*,Value*> vmap;
          CallInst* callNewI = dyn_cast<CallInst>(newI);
          Function* func = callNewI->getCalledFunction();
          for (Function::arg_iterator it = func->arg_begin(); it != func->arg_end(); it++) {
            Argument* farg = it;
            Value* aarg = callNewI->getOperand(farg->getArgNo());
            vmap[farg] = aarg;
            
            if (DebugLevel > 1) {
              errs() << "\n callI: "; callNewI->dump();
              errs() << "\n farg: "; farg->dump(); 
              errs() << "\n aarg: "; aarg->dump(); 
            }
          }
          vmap_stack.push_back( vmap );

          //debug: Find out the item whose next stat is not 1;
          // For invisible call function, because there is no function instruction of the called function;
          // there will be two call @ calledfucntionname appear one next to another;

          if(stat_Trace[n_index] != 1){
            call_stack.pop_back();
          }

        }     
        else {

          if (DebugLevel > 1) errs() << "\n POP call stack\n";

          //debug:
          Instruction* tmp_I = inst_Trace[n_index-2];     // find out the instruction before current instruction, because we didn't pass current index;
          if(CallInst* callI2 = dyn_cast<CallInst>(tmp_I)){
            // do nothing;
          }
          else
            call_stack.pop_back();

          //call_stack.pop_back();
          //thread_2_call_stack[tid] = call_stack;
          retv_stack.pop_back();
          //thread_2_retv_stack[tid] = retv_stack;
          vmap_stack.pop_back();
          //thread_2_vmap_stack[tid] = vmap_stack;
        }
      }
      } // chao: added on 10/25/2012
    }      
    else if (ReturnInst* retI = dyn_cast<ReturnInst>(I)) {
      assert(retI);
      // after returning from the function, replace %call with the %retval
      ReturnInst* retNewI = dyn_cast<ReturnInst>(newI);
      Value* callval = TAP_thread_2_retv_stack_retv(tid);
      Value* retval  = retNewI->getReturnValue();
      if (callval) {
        assert(retval);

        //add the same return record to the former stack also;
        std::map<Value*,Value*>& tmap = vmap_stack[vmap_stack.size()-2];     //should be size()-2;
        std::map<Value*,Value*>& vmap = vmap_stack.back();                   //actually, back direct to the size()-1 stack;
        vmap[callval] = retval;
        tmap[callval] = retval;
        //vmap[callval] = retI->getReturnValue();
      }
    }
  }
  
  std::map<Value*,Value*>& TAP_thread_2_call_stack_vmap(int tid) {

    std::vector<std::map<Value*,Value*> >& vmap_stack = thread_2_vmap_stack[tid];
    return vmap_stack.back();
  }

  Value* TAP_thread_2_retv_stack_retv(int tid) {

    std::vector<Value*>& retv_stack = thread_2_retv_stack[tid];
    return retv_stack.back();
  }

  std::string TAP_thread_2_call_stack_prefix(int tid) {

    std::vector<std::string>& call_stack = thread_2_call_stack[tid];
    std::string call_stack_str = call_stack[0];
    for (unsigned int j=1; j<call_stack.size();j++) {
      call_stack_str =  (call_stack_str + "_" + call_stack[j]);
    }
    return call_stack_str;
  }


  void TAP_declareAssumeFunction(Module &M) {
    LLVMContext &C = M.getContext();
    FunctionType *FT = NULL;
    {
      Type *Result = Type::getVoidTy(C);
      std::vector<Type*> Params;
      Type *Cond = IntegerType::getInt1Ty(C);
      Type *Stat = IntegerType::getInt1Ty(C);
      Params.push_back(Cond);
      Params.push_back(Stat);
      FT = FunctionType::get(Result, Params, false);
    }
    M.getOrInsertFunction("clap_assume"  , FT);

  }


  CallInst* TAP_createAssumeCallInst(Module &M, Value* cond0, int stat0) {

    LLVMContext &C = M.getContext();
    Value *preFunc  = M.getFunction("clap_assume");

    Value* cond = (cond0 ? cond0: ConstantInt::get(C,APInt(1,1)));
    Value* stat = ConstantInt::get(C,APInt(1,stat0));

    std::vector<Value*> Args;
    Args.push_back( cond );
    Args.push_back( stat );
    CallInst* I  = CallInst::Create(preFunc, Args);

    return I;
  }



  Instruction* TAP_createInstInstance(Module &M, int tid, Instruction* I, int stat) {

    Instruction* newI = NULL;
    

    if (BranchInst* brI = dyn_cast<BranchInst>(I)) {
      //call @clap_assume(%br_cond)
      Value *cond = (brI->isConditional()? brI->getCondition(): NULL) ;
      newI = TAP_createAssumeCallInst(M, cond, stat); 
    }
    else {
      newI = I->clone();
    }

    std::map<Value*,Value*>& vmap = TAP_thread_2_call_stack_vmap(tid);

    for (std::map<Value*,Value*>::iterator it=vmap.begin();it!=vmap.end();it++) {
      Value* From = it->first;
      Value* To   = it->second;
      newI->replaceUsesOfWith(From, To);
    }

    if (I->hasName()) {
      std::string v_prefix = TAP_thread_2_call_stack_prefix(tid);
      newI->setName( v_prefix + "_" + I->getName());
      vmap[I] = newI;
    }

    if (DebugLevel > 1) {
      errs() << "\n chao print I    : "; I->print(errs()); errs() << "";
      errs() << "\n chao print newI : "; newI->print(errs()); errs() << "\n";
    }

    return newI;
  }

    
  void TAP_convertIdTraceToInstructionTrace(Module &M) {

    TAP_thread_2_call_stack_init();

    for (unsigned int i = 0; i<id_Trace.size(); i++) {

      int tid = tid_Trace[i];
      int id  = id_Trace[i];
      int stat  = stat_Trace[i];
      int retval  = retval_Trace[i];

      std::string insv;

      if(stat == 1)
        insv = "true";
      else
        insv = "false";

      Instruction* I = id_to_inst_table[id];

      if(BranchInst* brI = dyn_cast<BranchInst>(I)){
        if(brI->isConditional()){
          if(branch_list.empty()){

            bState brs;
            brs.index = id;
            brs.bEnable.insert("true");
            brs.bEnable.insert("false");
            brs.bDone.insert(insv);
            branch_list.push_back(brs);

            // errs()<<"the branch statement id number is: "<<id<<"\n";

            rflag = false;    //initialize the redundancy flag;
          }

          else{
            vector<bState>::iterator it;

            for(it = branch_list.begin(); it < branch_list.end(); it++){
              // errs()<<"^^^ id to be checked: "<<id<<"\n";
              // errs()<<"the items in the list: "<<(*it).index<<"\n";
              if((*it).index == id){
                if(((*it).bDone.size() == 1) && ((*it).bDone.find(insv) != (*it).bDone.end())){
                  // errs()<<"Covered\n";
                  rflag = true;
                }
                else if((*it).bDone.size() == 2){
                  // errs()<<"Both covered!\n";
                }
                else{
                  // errs()<<"New Branch!\n";
                  (*it).bDone.insert(insv);
                  rflag = false;
                }
                flag = true;
                break;
              
              }
              else{
                rflag = false;
                flag = false;
              } 
            }   

            if(!flag){
              bState nbrs;
              nbrs.index = id;
              nbrs.bEnable.insert("true");
              nbrs.bEnable.insert("false");
              nbrs.bDone.insert(insv);
              // For vector operation
              branch_list.push_back(nbrs);
              // errs()<<"new added branch point is: "<<nbrs.index<<"\n";
            }

          }   // end of else
        }   // end of if(brI->)
      }   // end of if(BranchInst)
      //debug:
      int p_index = i+1;    // find the close next instruction index;

      Instruction* newI = TAP_createInstInstance(M, tid, I, stat);
      TAP_thread_2_call_stack_update(tid, I, newI, stat, p_index);       //modified;

      inst_Trace.push_back(newI);
    }

    //build up the look up table for the return value is not 1 of call statement;
    for(unsigned int k = 0; k < stat_Trace.size(); k++){
      if(stat_Trace[k] != 1){
        Instruction* I = inst_Trace[k];
        if(I->hasName()){
          std::string cname = I->getName();

          std::map<std::string, int>::iterator itr;
          itr = function_retval.find(cname);
          if(itr == function_retval.end()){
            function_retval[cname] = retval_Trace[k];
          }

        }
      }
    }

    std::map<std::string, int>::iterator it;
    for(it = function_retval.begin(); it != function_retval.end(); it++){
      errs()<<"~~~ Name is: "<<(*it).first<<" Value is: "<<(*it).second<<"\n";
    }

    //F->dump();

  }



  void TAP_outputInstructionTrace(Module &M) {
      if (DebugLevel > 0) {
      for (unsigned int i = 0; i<inst_Trace.size(); i++) {
        Instruction* I = inst_Trace[i];
        errs() << "trace[" << i << "] = ";
        errs() << "t" << tid_Trace[i] << "   ";
        errs() << id_Trace[i] << "    ";
        I->print(errs());  
        errs() << "\n";
        }
      }
  }

  void TAP_deleteInstructionTrace(Module &M) {
    
    //if we don't, OPT will complain and won't exit properly!
    
    for (unsigned int i=inst_Trace.size(); i>0; i--) {
      Instruction* I = inst_Trace[i-1];
      if (I) {
        errs()<<"The deleting inst index is: "<<i<<" Here???\n";
        delete I;
      }
    }
  }

  int TAP_bvToInteger(int bv_array[]){
    // Translate the saved bitvector to a integer;
    int ret_int = 0;
    int tmp_ret = 0;

    int len = 32;

    if(bv_array[len-1] == 0){
      //for the case of a positive number;
      for(int i = 0; i< len-1; i++){
        if(bv_array[i] == 1){
          ret_int  += (int)pow(2, i);
        }
      }
    }
    else{
      //for the case of a negetive number;
      for(int k = 0; k < len-1; k++){
        if(bv_array[k] == 0){
          tmp_ret += (int)pow(2, k);
        }
      }
      ret_int = -1 - tmp_ret;
    }

    return ret_int;

  }

  void TAP_writeSatResultToFile(YicesDP* yices) {
    
    std::string ErrMsg;
    raw_fd_ostream Output(OutputTraceFile.c_str(), ErrMsg, 0);

    //OutputTraceFile is the destination file: out.txt;
    //write the havoc value into the out.txt;

    if (!ErrMsg.empty()) {
      errs() << "\n warning: '" << OutputTraceFile << "' already exists!\n";
    }
    else {
      //errs()<<" ********************************The yices model generated Here!!!\n";
      yices_model m = yices_get_model(yices->get_context());
      assert(m);
      
      for (int i=1; i<= havoc_v_cnt; i++) {

        //char name[64];
        //printf(name, "havoc_v%d", i);

        stdstring name = ("havoc_v" + itostr(i));
        //need extend to support bitvector;

        yices_var_decl yvd = yices_get_var_decl_from_name(yices->get_context(), name.c_str());
        long c; 
        double dc;

        //For bitvector:
        int len = 32;
        int bv [32];
        int bv2int;

        if (yices_get_int_value(m, yvd, &c)) 
          Output << name << " = " << (int)c << "\n";
        else if (yices_get_double_value(m, yvd, &dc)) 
          Output << name << "  =  " << (double)c << "\n";
        else if (yices_get_bitvector_value(m, yvd, len, bv)){
          bv2int = TAP_bvToInteger(bv);
          Output << name << "  =  " << bv2int <<"\n";
        }
        else {
          lbool val = yices_get_value(m, yvd);
          if (val==l_false)
            Output << name << "  =  " << "0"<< "\n";
          else if (val==l_true)
            Output << name << "  =  " << "1"<< "\n";
          else 
            Output << name << "  =  " << "undef"<< "\n";
        }
      }
    }
  }

  void TAP_traceSymbolicExecution(Module &M) {

    //initialize the SMT solver
    YicesDP* yices = new YicesDP();
    //yices->set_default_var_type(YicesDP::INTty);
    yices->set_default_var_type(YicesDP::BVty);

    //build the SMT formula
    vector<assertion_id> assert_ids;
    for (unsigned i = 0; i<inst_Trace.size(); i++) {
      Instruction* I = inst_Trace[i];
      YicesDP::expr E = TAP_constructSMTExprForInstruction(yices, I);

      // we can control the use of weakest precondition;
      /////////////////////////////// WP guide pruning ///////////////////////////////////////
      // if(BranchInst* brInst = dyn_cast<BranchInst>(I)){                        // This is modified;
      //   if(brInst->isConditional()){
      //     uniqueInstId uid = make_pair( id_Trace[i], count_Trace[i] );
      //     BLiuValue* WP = WP_TABLE[uid];
      //     YicesDP::expr notWP = yices->mk_not( TAP_constructSMTExpr(yices, WP) ); 
      //     E = yices->mk_and(E, notWP);                                         // Do we still need consider OR???
      //   }
      // }


      // if (1) {                                      // the condition is not decided yet;
      //          // uniqueInstId uid = make_pair( id_Trace[count], count_Trace[count] ); 
	    //          BLiuValue* WP = WP_TABLE[uid];        // uid = uniqueid;
	    //          YicesDP::expr notWP = yices->mk_not( TAP_constructSMTExpr(yices, WP) );           
	    //          E = yices->mk_and(E, notWP);         // will add more instruction into the formula sequence, will the last negate strategy be affected?
      // }
      /////////////////////////////// WP guide pruning ///////////////////////////////////////
      
      assertion_id assert_id = yices->assert_retract_dp(E);

      assert_ids.push_back(assert_id);
    }

    //Debug:
    yices->get_sat_result();
    yices->show_sat();

    //find the last assume cond that can be negated
    for (unsigned i=inst_Trace.size(); i>0; i--) {

      Instruction* I = inst_Trace[i-1];
      assertion_id assert_id = assert_ids[i-1];
      yices->retract(assert_id);      

      if (TAP_isClapFunction(I,(const char*)"clap_assume")) {
        //negate the assume cond
        YicesDP::expr cond = TAP_constructSMTExprForValue(yices, I->getOperand(0));
        YicesDP::expr flag = TAP_constructSMTExprForValue(yices, I->getOperand(1));
        YicesDP::expr E = yices->mk_diseq(cond, flag);
        assertion_id assert_id2 = yices->assert_retract_dp(E);

        if (yices->get_sat_result()) {
          errs() << "\n found input to negate assume: E(" << i << ")\n";
          I->dump();
          errs() << "\n";

          if(branch_list.back().bDone.size() == 2 || branch_list.size() > Depth){

            branch_list.pop_back();

            if(branch_list.empty())
              break;
          }
          else{
            if(stat_Trace[i-1] == 1){                       // The index of the related item is i-1;
              branch_list.back().bDone.insert("false");
            }
            else{
              branch_list.back().bDone.insert("true");
            }            

            TAP_writeSatResultToFile(yices);

            if (DebugLevel > 0) {
              yices->show_sat();
            }
            break;
          } 

        }
        else{
          // if find out a negatable point, but the final SMT formula set cannot be satisfied, pop it out;

          if(branch_list.back().index == id_Trace[i-1] ){
            branch_list.pop_back();
          }
        }

        yices->retract(assert_id2);
      }

    }
    //free up the SMT solver
    delete yices;
  }


  YicesDP::Typ TAP_getVarType(Type* typ) {

    //debug:
    YicesDP::Typ ty = YicesDP::BVty;
    //YicesDP::Typ ty = YicesDP::INTty;

    switch (typ->getTypeID()) {

    case Type::VoidTyID:  assert(0); break;
      //case Type::HalfTyID:  assert(0); break;
    case Type::FloatTyID:  {
      //Bing;
      ty = YicesDP::REALty;
      break;
    }
    case Type::DoubleTyID: {
      //Bing;
      ty = YicesDP::REALty;
      break;
    }
    case Type::X86_FP80TyID: assert(0); break;
    case Type::FP128TyID: assert(0); break;
    case Type::PPC_FP128TyID: assert(0); break;
    case Type::LabelTyID: assert(0); break;
    case Type::MetadataTyID: assert(0); break;
    case Type::X86_MMXTyID: assert(0); break;

    case Type::IntegerTyID: {
      unsigned num_bit = ((IntegerType*)typ)->getBitWidth();

      //for debug:
      if (num_bit == 1)
        ty = YicesDP::BOOLty;
      else{
        ty = YicesDP::BVty; 
      }                          // Do the bit vector rewrite here!
      break;
    }
    case Type::FunctionTyID: assert(0); break;
    case Type::StructTyID: assert(0); break;
    case Type::ArrayTyID: assert(0); break;

    case Type::PointerTyID: 
      ty = YicesDP::BVty;          // In the test, by now I am not sure whether there will be some bugs lead by this????
      //ty = YicesDP::INTty; 
      break;

    case Type::VectorTyID: assert(0); break;
    case Type::NumTypeIDs: assert(0); break;
      //case Type::LastPrimitiveTyID: assert(0); break;
      //case Type::FirstDerivedTyID: assert(0); break;
    default: assert(0); break;
    }

    return ty;
  }

  YicesDP::expr TAP_constructSMTExprForValue(YicesDP* yices, Value* V) {

    YicesDP::expr res;
    assert( V );
    //V->dump();

    YicesDP::Typ ty = TAP_getVarType( V->getType() );

    if (V->hasName()) {
      stdstring nam = V->getName();

      res = yices->mk_var(nam, ty);
    }
    else if (GlobalValue* gv = dyn_cast<GlobalValue>(V)) {
      //check @Num here!!!
      assert(gv);
      assert(0);
    }
    else if (ConstantInt* ci = dyn_cast<ConstantInt>(V)) {

      uint64_t val = ci->getValue().getLimitedValue();

      if (ty == YicesDP::BOOLty) 
        res = (val == 0)? yices->mk_false(): yices->mk_true();
      else{
        res = yices->mk_num_int(val);
      }        
    }
    else if (ConstantFP* cf = dyn_cast<ConstantFP>(V)) {

      double val = cf->getValueAPF().convertToDouble();
      res = yices->mk_num_real(val,0);
    }
    else {
      assert(0 && "unknown type of Value");
      //res = TAP_constructSMTExprForConstant(C);
    }

    return res;
  }

  uint64_t TAP_getConstantIntValue(Value *V) {
    
    if (ConstantInt* ci = dyn_cast<ConstantInt>(V)) {
      uint64_t val = ci->getValue().getLimitedValue();
      return val;
    }
    else {
      assert(0 && "should be a constantInt");
    }
  }
      
  bool TAP_isClapFunction(Instruction* I, const char*clapFuncName) {
    bool res = false;
    if (CallInst* callI = dyn_cast<CallInst>(I)) {
      Function* func = callI->getCalledFunction();
      res = (!strcmp(clapFuncName,func->getName().data()));
    }
    return res;
  }

  void TAP_calculateWeakestPreCondition(){

    // Step 1: update count_Trace[];    // the rkey is the instruction id ranking;
    for(int i = 0; i < inst_Trace.size(); i++){

      int rkey = id_Trace[i];

      Instruction* I = id_to_inst_table[rkey];
      if(BranchInst* brIst = dyn_cast<BranchInst>(I)){
        if(brIst->isConditional()){
          if(count_Trace.find(rkey) != count_Trace.end()){
            count_Trace[rkey] = count_Trace[rkey]+1;
          }
          else
            count_Trace[rkey] = 1;
        }
      }
    }


    // Step 2: call buildWPInstruction_NEW();
    for(int i = id_Trace.size()-1; i>=0; i--){
      int id_num = id_Trace[i];

      Instruction* I = id_to_inst_table[id_num];                     // seems to be the pre-modified instruction,
      if(BranchInst* brInst = dyn_cast<BranchInst>(I)){
        if(brInst->isConditional()){
          // debug:
          Instruction* brI = inst_Trace[i];                          // here change to the post-modified instruction;
          TAP_buildWPInstruction_NEW(brI, i);

          // Once calculated from buttom to top, jump out;
          break;
        }
      }
    }
  }


/////////////////////////////////////////////  WEAKEST PRE-CONDITION //////////////////////////////////////////////////////


  //input:  I is coming from an if(c), for which we want to compute WP
  //output:  insert the weakest precondition of I to the WP_TABLE

  YicesDP::expr  TAP_constructSMTExpr(YicesDP* yices, BLiuValue* blwp) {
    YicesDP::expr res;

    if (blwp->op == BLV_TERMINAL) {
      res = TAP_constructSMTExpr_ForCV(yices, blwp->data);                          // reported no match function, misuse Value and BLiuValue;
    }
    else {
      YicesDP::expr l = TAP_constructSMTExpr(yices, blwp->left);
      YicesDP::expr r = TAP_constructSMTExpr(yices, blwp->right);
      switch( blwp->op ) {
      case BLV_AND:   res = yices->mk_and(l,r); break;
      case BLV_OR:    res = yices->mk_or(l,r); break;
      case BLV_XOR:   res = yices->mk_xor(l,r); break;
      case BLV_EQ:    res = yices->mk_eq(l,r); break;
      default:  assert( 0 && "wrong BLV type\n" );
      }
    }

    return res;
  }


  BLiuValue* TAP_computeWP_inBLiuValue(Instruction* I, BLiuValue* oldVal) {

    BLiuValue* locVal = NULL;

    locVal = oldVal->getCopy();

    // travese the current instruction to institute the same name part in the oldVal;
    switch( I->getOpcode() ) {
    case Instruction::Store: {
      //  store %op0 %op1    (op1 := op0)
      locVal->replace(locVal, I->getOperand(1)->getName(), I->getOperand(0));
      break;
    }

    case Instruction::Load: {
      // %tmp = load %op0    (tmp := op0)
      locVal->replace(locVal, I->getName(), I->getOperand(0));
      break;
    }

    default:
      // assert( I->hasName() );
      if(I->hasName()){
        // errs()<<"comes into Default, Instruction name is: "<<I->getName()<<"\n";
      }
      // %cmp = icmp eq i32 %tmp, 0,
      //locVal->replace(locVal, I->getName(), I);
      break;
    }

    return locVal;
  }
  
  
  void TAP_buildWPInstruction_NEW(Instruction* I, int idx){
    // idx is the post-modified trace index;
    BLiuValue* wpVal = NULL;
    BLiuValue* tmpVal = NULL;

    assert( I->getOpcode() == Instruction::Call );
    assert( TAP_isClapFunction(I,(const char*)"clap_assume") );

    // There is no getcopy() for LLVM Value, we use an indirect method;
    // In this way, we will not affect the real instruction which we want to operate;
    Instruction* newInst = NULL;
    newInst = I->clone();                          // for LLVM Value getCopy();

    // step-1,  retrieve the branching condition (c)
    Value* left = newInst->getOperand(0);
    Value* right = newInst->getOperand(1);

    // step 1.1 build the sub BLiuValue node the left and right;
    BLiuValue* lsub = new BLiuValue(left, BLV_TERMINAL, NULL, NULL);
    BLiuValue* rsub = new BLiuValue(right, BLV_TERMINAL, NULL, NULL);
    // step 1.2 build the BLiuValue node with left and right two sub BLiuValue nodes; 
    tmpVal = new BLiuValue(left, BLV_EQ, lsub,rsub);                                    // Here the name of root randomly named with left;

    // update the current WP_TABLE related item;
    // if there is a related item exist, Update it!
    // if there is no related item before, Add it!

    uniqueInstId cuid = make_pair(id_Trace[idx], count_Trace[id_Trace[idx]]);

    if(WP_TABLE.find(cuid) != WP_TABLE.end()){
      wpVal = new BLiuValue(WP_TABLE[cuid]->data, BLV_OR, WP_TABLE[cuid], tmpVal);
    }
    else{
      wpVal = tmpVal->getCopy();
    }

    WP_TABLE[cuid] = wpVal->getCopy();

    // step-2, compute the weakest precondition, and store it at every
    // preceding branching point
    int count = idx;

    while (count-- >= 0) {

      Instruction* curr_I = inst_Trace[count];

      int ori_num = id_Trace[count];                                   // find the pre-modified instruction;
      Instruction* ori_Inst = id_to_inst_table[ori_num];

      if(BranchInst* brInst = dyn_cast<BranchInst>(ori_Inst)){             // if meet another branch point;
        if (brInst->isConditional()) {
          // if (c)
          // wpVal = wpVal && (c)
          assert( curr_I->getOpcode() == Instruction::Call );
          assert( TAP_isClapFunction(curr_I,(const char*)"clap_assume") );

          // indirect copy LLVM Value;
          Instruction* tmp_curInst = NULL;
          tmp_curInst = curr_I->clone();
          Value* curr_left = tmp_curInst->getOperand(0);                      //???
          Value* curr_right = tmp_curInst->getOperand(1);                     //???

          BLiuValue* clsub = new BLiuValue(curr_left, BLV_TERMINAL, NULL, NULL);
          BLiuValue* crsub = new BLiuValue(curr_right, BLV_TERMINAL, NULL, NULL);

          BLiuValue* condVal = NULL;
          condVal = new BLiuValue(curr_left, BLV_EQ, clsub, crsub);                     // reported no match function, misuse Value and BLiuValue;
          wpVal = new BLiuValue(wpVal->data, BLV_AND, wpVal, condVal);

          // 1. OR with current saved wp; 2. save into the WP_TABLE[];
          uniqueInstId uid = make_pair( id_Trace[count], count_Trace[count] );
          wpVal = new BLiuValue(WP_TABLE[uid]->data, BLV_OR, WP_TABLE[uid], wpVal);
          WP_TABLE[uid] = wpVal->getCopy();
        }
      }
      else{                                           // if meet just ordinary instruction, % cmp = gt % tmp   5; then update the part of cmp with gt %tmp 5; just for upper c;
          wpVal = TAP_computeWP_inBLiuValue(curr_I, wpVal);          
      }

      if(count == 0){
        break;
      }
    }

    if (wpVal == NULL) {
      delete wpVal;
    }
}


//////////////////////////////////////////For compositeValue expression ////////////////////////////////

  YicesDP::expr TAP_constructSMTExpr_ForCV(YicesDP* yices, Value *myvalue) {                 //for compositeValue, the content need further fill up;

    Instruction* I = dyn_cast<Instruction>(myvalue);

    if (I == NULL) {
      return TAP_constructSMTExprForValue(yices, myvalue);
    }
    
    YicesDP::expr res = yices->mk_true();

    switch (I->getOpcode()) {
      // Control flow
    case Instruction::Ret:         {
      //chao, we need to do something here!
      //Bing: what is the expected behavior here?
      DBG_MSG("may need to handle RetInst!\n");
      break;
    }
    case Instruction::Br:  {        
      // br is translated into Call clap_assume();
      // Done!
      assert(0 && "shouldn't occur in trace"); 
      break;
    }
    case Instruction::Switch:      assert(0 && "shouldn't occur in trace"); break;
      // we hope we can find out a pass to translate switch to nested if strcuture;

    case Instruction::Unreachable: assert(0 && "shouldn't occur in trace"); break;
    case Instruction::Invoke:      assert(0 && "shouldn't occur in trace"); break;
    case Instruction::Call: {
      if (TAP_isClapFunction(I,(const char*)"clap_assume")) {
        YicesDP::expr cond = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
        YicesDP::expr flag = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
        res = yices->mk_eq(cond, flag);
      }
      else if (TAP_isClapFunction(I,(const char*)"tap_input_int")) {
        //1. find the name of the program variable 
        YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
        YicesDP::Typ ty = TAP_getVarType( I->getOperand(0)->getType() );
        //2. create a new variable named 'havoc_v#' variable
        char havoc_v[64];

        sprintf(havoc_v,"havoc_v%d", ++havoc_v_cnt);        //havoc_v_cnt is the havoc index;
        YicesDP::expr rhs = yices->mk_var(havoc_v, ty);
        res = yices->mk_eq(lhs, rhs);
      }
      else {
        // Call function under approximation;
        std::string key = I->getName();
        //errs()<<"^^^^ The searching key name is: "<<key<<"\n";
        std::map<std::string, int>::iterator ita;
        ita = function_retval.find(key);

        if(ita != function_retval.end()){
          YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);

          YicesDP::Typ ty = TAP_getVarType( I->getType() );
          
          if(ty == YicesDP::REALty){
            double retv;      //although currently the program return value we just stored integer.
            retv = function_retval.find(key)->second;
            function_retval.erase(key);                        //avoid multi times assign value;
            //errs()<<" The return value is: "<< retv <<"\n";
            YicesDP::expr rhs = yices->mk_num_real(retv, 1);

            res = yices->mk_eq(lhs, rhs);
          }
          else{
            int retv;
            retv = function_retval.find(key)->second;
            function_retval.erase(key);
            YicesDP::expr rhs = yices->mk_num_int(retv);
            res = yices->mk_eq(lhs, rhs);
          }
          
        }
      }
      break;
    }       
    case Instruction::PHI:         assert(0 && "shouldn't occur in trace"); break;
    case Instruction::Select:      assert(0 && "shouldn't occur in trace"); break;
    case Instruction::VAArg:       assert(0 && "shouldn't occur in trace"); break;
    case Instruction::Add: {
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_sum(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices,I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::Sub: {
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_sub(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices,I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::Mul: {
      //the function modified by Bing;
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_mul(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::UDiv: {
      //Bing;
      //check the right != 0 
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_div(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::SDiv: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_div(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices,I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::URem: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_mod(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::SRem: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_mod(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::And: {
      //Bing;
      //treat bitvector and int separately;
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_and(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::Or: {
      //Bing;
      //further add bitvector operation;
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_or(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::Xor: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_xor(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::Shl: {
      //Bing:need further test;
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_bv_ls(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::LShr: {
      //Bing: the function mk_bv_shift_right0/1 and mk_bv_shift_left0/1 are not listed separately;
      assert(0); break;
    }
    case Instruction::AShr: {
      //Bing: cannot find out a exactly function match this function;
      assert(0); break;
    }
    case Instruction::ICmp: {
      CmpInst *ci = cast<CmpInst>(I);
      ICmpInst *ii = cast<ICmpInst>(ci);
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr lhs =  TAP_constructSMTExpr_ForCV(yices, I);
      YicesDP::expr rhs = NULL;
      switch(ii->getPredicate()) {
      case ICmpInst::ICMP_EQ:   rhs = yices->mk_eq(left,right); break;
      case ICmpInst::ICMP_NE:   rhs = yices->mk_diseq(left,right); break;
      case ICmpInst::ICMP_UGT:  rhs = yices->mk_gt(left,right); break;
      case ICmpInst::ICMP_UGE:  rhs = yices->mk_ge(left,right); break;
      case ICmpInst::ICMP_ULT:  rhs = yices->mk_lt(left,right); break;
      case ICmpInst::ICMP_ULE:  rhs = yices->mk_le(left,right); break;
      case ICmpInst::ICMP_SGT:  rhs = yices->mk_gt(left,right); break;
      case ICmpInst::ICMP_SGE:  rhs = yices->mk_ge(left,right); break;
      case ICmpInst::ICMP_SLT:  rhs = yices->mk_lt(left,right); break;
      case ICmpInst::ICMP_SLE:  rhs = yices->mk_le(left,right); break;
      default: assert(0); break;
      }
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::Alloca: {
      //chao, ignore instructions such as " %tmp = alloc i32 "
      break;
    }
    case Instruction::Load: {
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices,I);
      YicesDP::expr rhs = TAP_constructSMTExpr_ForCV(yices,I->getOperand(0));
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::Store: {
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices,I->getOperand(1));
      YicesDP::expr rhs = TAP_constructSMTExpr_ForCV(yices,I->getOperand(0));
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::GetElementPtr: {
      //Bing: no match yices function;
      assert(0); break;
    }
    case Instruction::Trunc: {
      //Bing: no match yices function; however, mk_bv_mul might be used to trucate;
      assert(0); break;
    }
    case Instruction::ZExt: {
      //Bing: zero extension maybe achieved by or with all zero ty2;
      assert(0); break;
    }
    case Instruction::SExt: {
      //Bing: if value.ty != i1
      //sext can be treated as OR with some vector;
      assert(0); break;
    }
    case Instruction::IntToPtr: {
      assert(0); break;
    } 
    case Instruction::PtrToInt: {
      assert(0); break;
    }
    case Instruction::BitCast: {
      //Bing; this is just a rough operation;
      //Here the method we used is simalar like FPExt and other kyewords;
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      YicesDP::expr rhs = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::FAdd: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_sum(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::FSub: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_sub(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::FMul: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_mul(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::FDiv: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_div(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::FRem: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_mod(left, right);
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::FPTrunc: {
      //Bing; for this case, we treated the same as FPExt;             Buggy!!!
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      YicesDP::expr rhs = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::FPExt: {
      //Bing; tested in ep5, however, more details need to be defined.  Buggy!!!
      //Here the acceptable case is ignoring the type just remain the name of variable;
      //There are some bugs in type;
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      //CastInst *cit = cast<CastInst>(I);
      //YicesDP::Typ ty = TAP_getVarType(cit->getDestTy());
      //make REALty as an example;
      //YicesDP::expr rhs = dyn_cast<&ty>(I->getOperand(0));
      //existing Question: How to express cast operation here????????
      YicesDP::expr rhs = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::FPToUI: {
      //Bing; maybe buggy;
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      YicesDP::expr rhs = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::FPToSI: {
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);

      stdstring func_name = "fptosi";
      YicesDP::Typ tyre = TAP_getVarType( I->getType() );
      YicesDP::Typ typa = TAP_getVarType( I->getOperand(0)->getType() );
      YicesDP::expr rs = yices->mk_func2(func_name, typa, tyre);

      YicesDP::expr fpa = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr para[1];
      para[0] = fpa;
      YicesDP::expr rhs = yices->mk_app(rs, para, 1);

      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::UIToFP: {
      //Bing; maybe buggy;
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);
      YicesDP::expr rhs = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::SIToFP: {
      YicesDP::expr lhs = TAP_constructSMTExpr_ForCV(yices, I);

      stdstring func_name = "sitofp";
      YicesDP::Typ tyre = TAP_getVarType( I->getType() );
      YicesDP::Typ typa = TAP_getVarType( I->getOperand(0)->getType() );
      YicesDP::expr rs = yices->mk_func2(func_name, typa, tyre); // Build the defination of the function;

      YicesDP::expr fpa = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));    // Function Parameter;
      YicesDP::expr para[1];
      para[0] = fpa;
      YicesDP::expr rhs = yices->mk_app(rs, para, 1);

      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::FCmp: {
      //Bing: similar as ICmp;
      //assert(0); break;
      CmpInst *ci = cast<CmpInst>(I);
      FCmpInst *fi = cast<FCmpInst>(ci);
      YicesDP::expr left  = TAP_constructSMTExpr_ForCV(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExpr_ForCV(yices, I->getOperand(1));
      YicesDP::expr lhs =  TAP_constructSMTExpr_ForCV(yices, I);
      YicesDP::expr rhs = NULL;
      switch(fi->getPredicate()) {
      case FCmpInst::FCMP_ORD:
	    //Bing: how to express QNAN?
        break;
      case FCmpInst::FCMP_UNO:
        break;
      case FCmpInst::FCMP_UEQ:
	      rhs = yices->mk_eq(left, right); break;
      case FCmpInst::FCMP_OEQ:
	      rhs = yices->mk_eq(left, right); break;
      case FCmpInst::FCMP_UGT:
	      rhs = yices->mk_gt(left, right); break;
      case FCmpInst::FCMP_OGT:
	      rhs = yices->mk_gt(left, right); break;
      case FCmpInst::FCMP_UGE:
	      rhs = yices->mk_ge(left, right); break;
      case FCmpInst::FCMP_OGE:
	      rhs = yices->mk_ge(left, right); break;
      case FCmpInst::FCMP_ULT:
	      rhs = yices->mk_lt(left, right); break;
      case FCmpInst::FCMP_OLT:
	      rhs = yices->mk_lt(left, right); break;
      case FCmpInst::FCMP_ULE:
	      rhs = yices->mk_le(left, right); break;
      case FCmpInst::FCMP_OLE:
	      rhs = yices->mk_le(left, right); break;
      case FCmpInst::FCMP_UNE:
	      rhs = yices->mk_diseq(left, right); break;
      case FCmpInst::FCMP_ONE:
	      rhs = yices->mk_diseq(left, right); break;
      case FCmpInst::FCMP_FALSE:
        break;
      case FCmpInst::FCMP_TRUE:
        break;
      default:
	      assert(0 && "Invalid FCMP predicate!");	break;
      }
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::InsertValue: {
      assert(0); break;
    }
    case Instruction::ExtractValue: {
      assert(0); break;
    }
      // Other instructions...
      // Unhandled
    case Instruction::ExtractElement:
    case Instruction::InsertElement:
    case Instruction::ShuffleVector:
    default:
      assert(0 && "shouldn't occur in trace"); break;
      break;
    }
  
    //errs()<<" The current yices formulae is: "<< res <<"\n";
    return res;

  }

/////////////////////////////////// translation for ordinary Instruction ////////////////////////////////////////////

 YicesDP::expr TAP_constructSMTExprForInstruction(YicesDP* yices, Instruction* I) {
    
    YicesDP::expr res = yices->mk_true();

    switch (I->getOpcode()) {
      // Control flow
    case Instruction::Ret:         {
      //chao, we need to do something here!
      //Bing: what is the expected behavior here?
      DBG_MSG("may need to handle RetInst!\n");
      break;
    }
    case Instruction::Br:  {        
      // br is translated into Call clap_assume();
      // Done!
      assert(0 && "shouldn't occur in trace"); 
      break;
    }
    case Instruction::Switch:      assert(0 && "shouldn't occur in trace"); break;
      // we hope we can find out a pass to translate switch to nested if strcuture;

    case Instruction::Unreachable: assert(0 && "shouldn't occur in trace"); break;
    case Instruction::Invoke:      assert(0 && "shouldn't occur in trace"); break;
    case Instruction::Call: {
      if (TAP_isClapFunction(I,(const char*)"clap_assume")) {
        YicesDP::expr cond = TAP_constructSMTExprForValue(yices, I->getOperand(0));
        YicesDP::expr flag = TAP_constructSMTExprForValue(yices, I->getOperand(1));
        res = yices->mk_eq(cond, flag);
      }
      else if (TAP_isClapFunction(I,(const char*)"tap_input_int")) {
        //1. find the name of the program variable 
        YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I->getOperand(0));
        YicesDP::Typ ty = TAP_getVarType( I->getOperand(0)->getType() );
        //2. create a new variable named 'havoc_v#' variable
        char havoc_v[64];

        sprintf(havoc_v,"havoc_v%d", ++havoc_v_cnt);        //havoc_v_cnt is the havoc index;
        YicesDP::expr rhs = yices->mk_var(havoc_v, ty);
        res = yices->mk_eq(lhs, rhs);
      }
      else {
        // Call function under approximation;
        std::string key = I->getName();
        //errs()<<"^^^^ The searching key name is: "<<key<<"\n";
        std::map<std::string, int>::iterator ita;
        ita = function_retval.find(key);

        if(ita != function_retval.end()){
          YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);

          YicesDP::Typ ty = TAP_getVarType( I->getType() );

          /*
          if(ty == YicesDP::INTty || YicesDP::BVty){
          //if(ty == YicesDP::BVty){
            int retv;
            retv = function_retval.find(key)->second;
            YicesDP::expr rhs = yices->mk_num_int(retv);
            res = yices->mk_eq(lhs, rhs);
          }
          else{
            double retv;      //although currently the program return value we just stored integer.
            retv = function_retval.find(key)->second;
            //errs()<<" The return value is: "<< retv <<"\n";
            YicesDP::expr rhs = yices->mk_num_real(retv, 1);

            res = yices->mk_eq(lhs, rhs);
          }
          */
          
          if(ty == YicesDP::REALty){
            double retv;      //although currently the program return value we just stored integer.
            retv = function_retval.find(key)->second;
            function_retval.erase(key);                        //avoid multi times assign value;
            //errs()<<" The return value is: "<< retv <<"\n";
            YicesDP::expr rhs = yices->mk_num_real(retv, 1);

            res = yices->mk_eq(lhs, rhs);
          }
          else{
            int retv;
            retv = function_retval.find(key)->second;
            function_retval.erase(key);
            YicesDP::expr rhs = yices->mk_num_int(retv);
            res = yices->mk_eq(lhs, rhs);
          }
          
        }
      }
      break;
    }       
    case Instruction::PHI:         assert(0 && "shouldn't occur in trace"); break;
    case Instruction::Select:      assert(0 && "shouldn't occur in trace"); break;
    case Instruction::VAArg:       assert(0 && "shouldn't occur in trace"); break;
    case Instruction::Add: {
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_sum(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices,I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::Sub: {
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_sub(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices,I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::Mul: {
      //the function modified by Bing;
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_mul(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::UDiv: {
      //Bing;
      //check the right != 0 
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_div(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::SDiv: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_div(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices,I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::URem: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_mod(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::SRem: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_mod(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::And: {
      //Bing;
      //treat bitvector and int separately;
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_and(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::Or: {
      //Bing;
      //further add bitvector operation;
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_or(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::Xor: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_xor(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::Shl: {
      //Bing:need further test;
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_bv_ls(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::LShr: {
      //Bing: the function mk_bv_shift_right0/1 and mk_bv_shift_left0/1 are not listed separately;
      assert(0); break;
    }
    case Instruction::AShr: {
      //Bing: cannot find out a exactly function match this function;
      assert(0); break;
    }
    case Instruction::ICmp: {
      CmpInst *ci = cast<CmpInst>(I);
      ICmpInst *ii = cast<ICmpInst>(ci);
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr lhs =  TAP_constructSMTExprForValue(yices, I);
      YicesDP::expr rhs = NULL;
      switch(ii->getPredicate()) {
      case ICmpInst::ICMP_EQ:   rhs = yices->mk_eq(left,right); break;
      case ICmpInst::ICMP_NE:   rhs = yices->mk_diseq(left,right); break;
      case ICmpInst::ICMP_UGT:  rhs = yices->mk_gt(left,right); break;
      case ICmpInst::ICMP_UGE:  rhs = yices->mk_ge(left,right); break;
      case ICmpInst::ICMP_ULT:  rhs = yices->mk_lt(left,right); break;
      case ICmpInst::ICMP_ULE:  rhs = yices->mk_le(left,right); break;
      case ICmpInst::ICMP_SGT:  rhs = yices->mk_gt(left,right); break;
      case ICmpInst::ICMP_SGE:  rhs = yices->mk_ge(left,right); break;
      case ICmpInst::ICMP_SLT:  rhs = yices->mk_lt(left,right); break;
      case ICmpInst::ICMP_SLE:  rhs = yices->mk_le(left,right); break;
      default: assert(0); break;
      }
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::Alloca: {
      //chao, ignore instructions such as " %tmp = alloc i32 "
      break;
    }
    case Instruction::Load: {
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices,I);
      YicesDP::expr rhs = TAP_constructSMTExprForValue(yices,I->getOperand(0));
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::Store: {
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices,I->getOperand(1));
      YicesDP::expr rhs = TAP_constructSMTExprForValue(yices,I->getOperand(0));
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::GetElementPtr: {
      //Bing: no match yices function;
      assert(0); break;
    }
    case Instruction::Trunc: {
      //Bing: no match yices function; however, mk_bv_mul might be used to trucate;
      assert(0); break;
    }
    case Instruction::ZExt: {
      //Bing: zero extension maybe achieved by or with all zero ty2;
      assert(0); break;
    }
    case Instruction::SExt: {
      //Bing: if value.ty != i1
      //sext can be treated as OR with some vector;
      assert(0); break;
    }
    case Instruction::IntToPtr: {
      assert(0); break;
    } 
    case Instruction::PtrToInt: {
      assert(0); break;
    }
    case Instruction::BitCast: {
      //Bing; this is just a rough operation;
      //Here the method we used is simalar like FPExt and other kyewords;
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      YicesDP::expr rhs = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::FAdd: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_sum(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::FSub: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_sub(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::FMul: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_mul(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::FDiv: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_div(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::FRem: {
      //Bing;
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr rhs = yices->mk_mod(left, right);
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::FPTrunc: {
      //Bing; for this case, we treated the same as FPExt;             Buggy!!!
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      YicesDP::expr rhs = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      res = yices->mk_eq(lhs,rhs);
      break;
    }
    case Instruction::FPExt: {
      //Bing; tested in ep5, however, more details need to be defined.  Buggy!!!
      //Here the acceptable case is ignoring the type just remain the name of variable;
      //There are some bugs in type;
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      //CastInst *cit = cast<CastInst>(I);
      //YicesDP::Typ ty = TAP_getVarType(cit->getDestTy());
      //make REALty as an example;
      //YicesDP::expr rhs = dyn_cast<&ty>(I->getOperand(0));
      //existing Question: How to express cast operation here????????
      YicesDP::expr rhs = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::FPToUI: {
      //Bing; maybe buggy;
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      YicesDP::expr rhs = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::FPToSI: {
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);

      stdstring func_name = "fptosi";
      YicesDP::Typ tyre = TAP_getVarType( I->getType() );
      YicesDP::Typ typa = TAP_getVarType( I->getOperand(0)->getType() );
      YicesDP::expr rs = yices->mk_func2(func_name, typa, tyre);

      YicesDP::expr fpa = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr para[1];
      para[0] = fpa;
      YicesDP::expr rhs = yices->mk_app(rs, para, 1);

      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::UIToFP: {
      //Bing; maybe buggy;
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);
      YicesDP::expr rhs = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::SIToFP: {
      YicesDP::expr lhs = TAP_constructSMTExprForValue(yices, I);

      stdstring func_name = "sitofp";
      YicesDP::Typ tyre = TAP_getVarType( I->getType() );
      YicesDP::Typ typa = TAP_getVarType( I->getOperand(0)->getType() );
      YicesDP::expr rs = yices->mk_func2(func_name, typa, tyre); // Build the defination of the function;

      YicesDP::expr fpa = TAP_constructSMTExprForValue(yices, I->getOperand(0));    // Function Parameter;
      YicesDP::expr para[1];
      para[0] = fpa;
      YicesDP::expr rhs = yices->mk_app(rs, para, 1);

      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::FCmp: {
      //Bing: similar as ICmp;
      //assert(0); break;
      CmpInst *ci = cast<CmpInst>(I);
      FCmpInst *fi = cast<FCmpInst>(ci);
      YicesDP::expr left  = TAP_constructSMTExprForValue(yices, I->getOperand(0));
      YicesDP::expr right = TAP_constructSMTExprForValue(yices, I->getOperand(1));
      YicesDP::expr lhs =  TAP_constructSMTExprForValue(yices, I);
      YicesDP::expr rhs = NULL;
      switch(fi->getPredicate()) {
      case FCmpInst::FCMP_ORD:
	    //Bing: how to express QNAN?
        break;
      case FCmpInst::FCMP_UNO:
        break;
      case FCmpInst::FCMP_UEQ:
	      rhs = yices->mk_eq(left, right); break;
      case FCmpInst::FCMP_OEQ:
	      rhs = yices->mk_eq(left, right); break;
      case FCmpInst::FCMP_UGT:
	      rhs = yices->mk_gt(left, right); break;
      case FCmpInst::FCMP_OGT:
	      rhs = yices->mk_gt(left, right); break;
      case FCmpInst::FCMP_UGE:
	      rhs = yices->mk_ge(left, right); break;
      case FCmpInst::FCMP_OGE:
	      rhs = yices->mk_ge(left, right); break;
      case FCmpInst::FCMP_ULT:
	      rhs = yices->mk_lt(left, right); break;
      case FCmpInst::FCMP_OLT:
	      rhs = yices->mk_lt(left, right); break;
      case FCmpInst::FCMP_ULE:
	      rhs = yices->mk_le(left, right); break;
      case FCmpInst::FCMP_OLE:
	      rhs = yices->mk_le(left, right); break;
      case FCmpInst::FCMP_UNE:
	      rhs = yices->mk_diseq(left, right); break;
      case FCmpInst::FCMP_ONE:
	      rhs = yices->mk_diseq(left, right); break;
      case FCmpInst::FCMP_FALSE:
        break;
      case FCmpInst::FCMP_TRUE:
        break;
      default:
	      assert(0 && "Invalid FCMP predicate!");	break;
      }
      res = yices->mk_eq(lhs, rhs);
      break;
    }
    case Instruction::InsertValue: {
      assert(0); break;
    }
    case Instruction::ExtractValue: {
      assert(0); break;
    }
      // Other instructions...
      // Unhandled
    case Instruction::ExtractElement:
    case Instruction::InsertElement:
    case Instruction::ShuffleVector:
    default:
      assert(0 && "shouldn't occur in trace"); break;
      break;
    }
  
    //errs()<<" The current yices formulae is: "<< res <<"\n";
    return res;

  }
  
};


}//namespace 


char TAP_InstrumentInstTraceGen::ID = 0;
int TAP_InstrumentInstTraceGen::havoc_v_cnt = 0;
static RegisterPass<TAP_InstrumentInstTraceGen> X("tap_inst_trace_gen", 
                                                 "TAP Instruction Trace Gen Pass");
