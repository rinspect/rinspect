#include <set>
#include <string>

using std::set;
using std::string;

class bState
{
public:
	int index;

	set <string> bEnable;
	set <string> bDone;

	void init();
	bool complete();
};

void bState::init(){
	//fill up the Enable (destination) set;
	bEnable.insert("true");
	bEnable.insert("false");
}

bool bState::complete(){
	init();
	if(bEnable.size()==bDone.size())
		return true;
	else
		return false;
}