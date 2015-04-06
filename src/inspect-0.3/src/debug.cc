#include "debug.hpp"

void mypause(){
    /**/  static bool is_go=false;
    if (is_go==false){
	cout<<"                  ----a to absort, r to run without stop:"<<std::flush;
	char cmd=cin.get();
	switch(cmd){
	case 'a':
	    abort();
	case 'r':
	    is_go=true;
	}
	}
}
