#include "llvm/Instructions.h"
#include "llvm/Value.h"
#include "llvm/Pass.h"
#include "llvm/Instructions.h"
#include "llvm/Value.h"

#include "../../../../smt_dp/yices_dp.hh"



#ifndef __BLIUVALUE_H
#define __BLIUVALUE_H


typedef enum { 
    BLV_AND,  BLV_OR, BLV_XOR, BLV_EQ, BLV_TERMINAL
  } BLiuValue_Op;

void TAP_Value_replace(Value *wpVal, std::string from, Value *to) {

    assert( dyn_cast<Instruction>(wpVal) );

    Instruction* I = dyn_cast<Instruction>(wpVal);

    for (unsigned int i = 0; i < I->getNumOperands(); i++) {
      Value *oprd = I->getOperand(i);

      // check each level;
      if(oprd->hasName()){
        if(oprd->getName() == from){
          // substitute this part;
          I->setOperand(i, to);
        }
        else{
          if(Instruction* oprdI = dyn_cast<Instruction>(oprd)){
            TAP_Value_replace(oprd, from, to);
          }
        }
      }


      // if ( Instruction* oprdI = dyn_cast<Instruction>(oprd) ) {
      //   errs()<<"The operand is also an Instruction: "<<oprdI->getName()<<"\n";
      //       TAP_Value_replace(oprd, from, to);                      // Do we need to update here from and to?
      // }
      // else {
      //   if(oprd->hasName()){
      //     errs()<<"the substituted Value name is: "<<oprd->getName()<<"\n";
      //     // because sometimes the operand is an constant without a name;
      //     if(oprd->getName() ==  from){
      //       oprd = to;                        // Here should be something like getCopy();
      //     }
      //   }
      // }
    }
}


  class BLiuValue {
  public:
    Value*         data;
    BLiuValue_Op   op;
    BLiuValue*     left;
    BLiuValue*     right;
    
    BLiuValue();
    BLiuValue(Value* dat, BLiuValue_Op o, BLiuValue* l, BLiuValue* r) {
      data = dat;
      op = o;
      left = l;
      right = r;
    }

    ~BLiuValue();

    BLiuValue* getCopy();
    void replace(BLiuValue* wpVal, std::string from, Value* to); 
    //YicesDP::expr constructSMTExpr(YicesDP* yices);
  };


  BLiuValue* BLiuValue::getCopy() {
    BLiuValue * res = NULL;
    if (op == BLV_TERMINAL) {
      //res = left->getCopy();                           // LLVM Value duplication function
      res = new BLiuValue(data, op, NULL, NULL);
    }
    else {
      BLiuValue *l = left->getCopy();
      BLiuValue *r = right->getCopy();
      res = new BLiuValue(data, op, l, r);
    }
    return res;
  }

  void BLiuValue::replace( BLiuValue* wpVal, std::string from, Value *to ) {                          // Problematic!!!
    // from is the source name; to is the target entity; wpVal is the target BLiuValue, which is the searching space;
    assert(wpVal != NULL);

    // Step 1: Whether it is leaf node in the Tree Structure?
    if (wpVal->op == BLV_TERMINAL) {                            // leaf node in BliuValue Tree;
      assert( wpVal->left == NULL );
      assert( wpVal->right == NULL );
      //left:   ((x + y) * z - 5)
      //from:     x                    %x = add %a %b
      //to  :     a+b
      //result:  (( (a+b) + y) * z - 5)

      // Step 1-1: Whether the data is an Instruction, we want to substitute any operand if necessary;
      if ( Instruction* wpValI = dyn_cast<Instruction>(wpVal->data) ) {      
        TAP_Value_replace(wpVal->data, from , to);                         // only institute the part with same name;
      }
      else {
           if (wpVal->data->getName() == from) {                        
              wpVal->data = to;                                      // substitute; Should not be "=", but something like getCopy();
            }
         }
    }
    else {
      replace(wpVal->left , from, to);
      replace(wpVal->right, from, to);
    }
  }


#endif