#include <map>
#include <utility>
#include "llvm/Instructions.h"
#include "llvm/Value.h"
#include "llvm/Pass.h"
#include "llvm/Instructions.h"
#include "llvm/Value.h"


using namespace std;
using namespace llvm;
//using std::map;

class tableWP
{
	map<pair<int,int>, Instruction*> tbl;
public:
	Instruction* get(pair<int, int> key);
	void set(pair<int, int>, Instruction* wp);
	int getkey(int inst_index);    

};


Instruction* tableWP::get(pair<int, int> key){
	return tbl[key];
}

void tableWP::set(pair<int, int> key, Instruction* wp){
	// Assume this wp is the final calculated wp 
	// which can be save in the map directly;
	tbl[key] = wp;
}

int tableWP::getkey(int inst_index){
	// know the inst index, we want to know the counter;
	int times;

	map<pair<int,int>, Instruction*>::iterator it;
	for(it = tbl.begin(); it != tbl.end(); it++){
		pair<int, int> tmp = (*it).first;
		if(tmp.first == inst_index){
			times = tmp.second;
			break;
		}
		else{
			times = 0;
		}
	}
	return times;
}