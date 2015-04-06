#include "clap_typest_check.hh"

map<string, map<int, map<string, int> > > state_potential_events;

map<string, map<int, map<string, int> > >* clap_automaton; //map<object(class) name, map<from_state, map<event, to_state> > >
//map<object(class) name, map<from_state, map<event, to state> > >

map<string, map<string, bool> > valid_functions;

map<string, map<int, int> >* exist_states; //states occured
map<int, int>* flaged_states;

//map<int, int> object_map; //map<map <object id, current state>
//map<int, int> return_object_map() {
//	return object_map;
//}

const int all_initial_state = 0;
char * pch;
pair<string, string> get_class_and_function(string event, char* fname) {
	pair<string, string> ret;

	if (!strncmp("zl", fname, 2)) { //start with "zl", specially defined white list
		ret.first = "zl";
		ret.second = event;
		return ret;
	}

	vector<string> split_event;
	vector<string>::iterator splited_event;
	int found = 0;
	string temp;

	pch = strchr(fname, '(');

	if (pch != NULL) { //remove every thing after the first '('
		int index_lf = pch - fname + 1;
		char subbuff[index_lf];
		memcpy(subbuff, &fname[0], index_lf - 1);

		subbuff[index_lf - 1] = '\0';

		temp = string(subbuff);

		found = temp.rfind("::");

	}

	if (found <= 0) { //find the last '::', left=class name, right= function name
		ret.first = "zl_skip_function";
		ret.second = "zl_skip_function";
		return ret;
	}

	string class_name = temp.substr(0, found);

	event = temp.substr(found + 2, temp.length() - found - 2);

	//remove ~ for deconstruct function
//	split_event = split_string(event, "~");
//	event = split_event[split_event.size() - 1];

	//remove the constructor and destructor
//	if (class_name.find(event) != std::string::npos) { //
//		ret.first = "zl_skip_function";
//		ret.second = "zl_skip_function";
//		return ret;
//	}


//	cout << "Class: " << class_name << "           Function: " << event << endl;

	//consider only the classes we have the automaton
	if (valid_functions.find(class_name) == valid_functions.end()) {
		ret.first = "zl_skip_function";
		ret.second = "zl_skip_function";
		return ret;
	}


//	cout << "----Class: " << class_name << "           Function: " << event << endl;
	if (valid_functions[class_name].find(event)
			== valid_functions[class_name].end()) {
		ret.first = "zl_skip_function";
		ret.second = "zl_skip_function";
		return ret;
	}

	ret.first = class_name;
	ret.second = event;

//	cout << "Class: " << class_name << "           Function: " << event << endl;
	return ret;

}

bool typest_check_handle_call(char* fname, int object_id) {

//	if (typ == OBJ_CALL) {
	//		bool skip_call = true;
	//		if (!strncmp("zl", fname, 2)) {
	////		TYPEST_PRINTs(fname, ptr);
	////		etrace.add_event(OBJ_CALL, UOID(ptr), fname);
	//			skip_call = false;
	//		}
	//
	//		char * pch;
	////		printf("Looking for the '(' character in \"%s\"...\n", fname);
	//		pch = strchr(fname, '(');
	////		while (pch != NULL) {
	////			printf("found at %d\n", pch - fname + 1);
	////			pch = strchr(pch + 1, '(');
	////		}
	//
	//		if (pch != NULL) { //find the first ( in the function name
	//			int index_lf = pch - fname + 1;
	//			char subbuff[index_lf];
	//			memcpy(subbuff, &fname[0], index_lf - 1);
	//			subbuff[index_lf-1] = '\0';
	//
	//			cout << subbuff << endl;
	//
	//		}
	//
	//		if (skip_call)
	//			return;
	//	}

//	increase_test();
//	print_test();
//
//	cout << "tid:" << UTID_self() << "   type:" << fname << "    id:"
//			<< object_id << endl;
//	 printf("\ntid= %-3d       obj= %d         method= %s\n", UTID_self(), object_id, fname);

	if (!strncmp("zl", fname, 2)) {	//self defined functions
		return true;
	}

	bool ret = false;

	string class_name = "class";

	string event = (string) fname;
	pair<string, string> class_function = get_class_and_function(event, fname);
	class_name = class_function.first;
	event = class_function.second;

	if (class_name.compare(event) == 0) //filter the construct and deconstruct functions
			{
		return false;
	}
//	else return true;

	map<string, map<int, map<string, int> > >::iterator it_class =
			(*clap_automaton).find(class_name); //exist the automaton of the class
	if (it_class != (*clap_automaton).end()) {
//		cout << "class: " << class_name << endl;
//		cout << "event: " << event << endl;
		return true;
		ret = true;
//		cout << "found:" << class_name << "->" << event << endl;
//
//		printf("\ntid= %-3d       obj= %d         method= %s\n", UTID_self(),
//				object_id, fname);
//
//		cout << "automaton found for class:" << class_name;

		map<int, int>::iterator it_object = object_map.find(object_id);

		int check_automaton;

		if (it_object != object_map.end()) { //already exist a state of the object

			check_automaton = check(class_name, object_map[object_id], event);

		} else //doesn't exist a state of the object
		{
			check_automaton = check(class_name, all_initial_state, event); //use initial state of all objects:0 as the current state

		}

//		cout << "         the current state of object:   " << object_id
//				<< "  is   " << object_map[object_id];
//
//		cout << "         the next event is: " << event << endl;
		if (check_automaton != -1) { //satisfy the automaton
//			cout << "event approved: the next state of object:   " << object_id
//					<< " is:  " << object_map[object_id] << "->"
//					<< check_automaton << endl << endl;
			object_map[object_id] = check_automaton;
		} else {
//			cout << "event rejected: reached an misuse of class:" << class_name
//					<< "     object:" << object_id << endl << endl;
		}

	} else {
		//cout << "couldn't find the automaton for class: " << class_name << endl;
	}
	return ret;
}

void add_transaction(string obj_name, int from_state, string event,
		int to_state) {
	(*clap_automaton)[obj_name][from_state][event] = to_state;
}

int check(string class_name, int from_state, string event) {

//	if ((*clap_automaton)[class_name][from_state][event]) {
	if ((*clap_automaton).find(class_name) != (*clap_automaton).end()) {

		if ((*clap_automaton)[class_name].find(from_state)
				!= (*clap_automaton)[class_name].end()) {

			if ((*clap_automaton)[class_name][from_state].find(event)
					!= (*clap_automaton)[class_name][from_state].end()) {
				return (*clap_automaton)[class_name][from_state][event];
			}
		}
	}
	return -1;

}

void input_automaton(string automaton_path) {
	if (exist_states == NULL) {
		exist_states = new map<string, map<int, int> >;
	}
	clap_automaton = new map<string, map<int, map<string, int> > >;

	string path;
	if (automaton_path == "") {
		path = current_path();
		path = path.append("/automaton");
	} else {
		path = automaton_path;

	}

	char *p = (char*) path.c_str();

//cout << path << endl;

	vector<string> files = searchDir(p);

	vector<string>::iterator it;
	for (it = files.begin(); it != files.end(); it++) { //each file in /automaton
		string file_name = (string) *it;
//		cout <<  file_name << endl;
		string FullPath = path;
		string file = FullPath.append("/");
		file = file.append(file_name);
//		 + file_name
//		cout<<file<<endl;

		vector<string> lines = read_file(file);
//		cout<<lines<<endl;
		vector<string>::iterator it_line_of_file;
		for (it_line_of_file = lines.begin(); it_line_of_file != lines.end();
				it_line_of_file++) { //each line in a file
			string line = (string) *it_line_of_file; //get the line
			//		cout << line << endl;
			if (line.size() <= 0)
				continue;

			vector<string> words = split_string(line);

			int from_state = atoi(words[0].c_str());
			int to_state = atoi(words[1].c_str());
			string file_pure_name = split_string(file_name, ".")[0];

			cout << "ADD TRANSACTION:  class name: " << file_pure_name
					<< "    from state:" << from_state << "    event:-"
					<< words[2] << "-    to state:" << to_state << endl;

			(*clap_automaton)[file_pure_name][from_state][words[2]] = to_state;
			(*exist_states)[file_pure_name][to_state] = 1;
			(*exist_states)[file_pure_name][from_state] = 1;

			valid_functions[file_pure_name][words[2]] = true;

			//	cout<<clap_automatons[file_pure_name][from_state][words[2]]<<endl;

		}

	}

	compute_PE();

}

void compute_PE() {
	cout << "Computing the Potential events of all the states" << endl;
//	map<string, map<int, map<string, int> > > clap_automaton; //<object(class) name, map<from_state, map<event, to_state> > >
//	map<string, map<int, map<string, int> > > state_potential_events;//map<object(class) name, map<from_state, map<event, frequency> > >
//	map<string, map<int, int> > exist_states;
//	map<int,int> flaged_states;
	map<string, map<int, map<string, int> > >::iterator it_class;
	map<int, int>::iterator it_state;
	map<string, int>::iterator it_result;
	string class_name;
	int state;
	for (it_class = (*clap_automaton).begin();
			it_class != (*clap_automaton).end(); it_class++) {	//for each class
		class_name = it_class->first;
		cout << "class name: " << class_name << endl;
		;
		for (it_state = (*exist_states)[class_name].begin();
				it_state != (*exist_states)[class_name].end(); it_state++) {//for each states
			state = it_state->first;
			cout << "state: " << state << " {";
			if (flaged_states == NULL)
				flaged_states = new map<int, int>;
			(*flaged_states).clear();
			state_potential_events[class_name][it_state->first] = DFS(
					class_name, it_state->first);

			for (it_result =
					state_potential_events[class_name][it_state->first].begin();
					it_result
							!= state_potential_events[class_name][it_state->first].end();
					it_result++) {
				cout << " " << it_result->first << " -> " << it_result->second
						<< " ;";

			}
			cout << " }" << endl;

		}

	}

//	cout << "state_potential_events.size(): " << state_potential_events.size()
//			<< endl;
//	cout << "state_potential_events[FileReader].size(): "
//			<< state_potential_events["FileReader"].size() << endl;
//	cout << "state_potential_events[other_classname][next_state].size(): "
//			<< state_potential_events["FileReader"][1].size() << endl;
//
//	map<string, int>::iterator it_function;
//	for (it_function = state_potential_events["FileReader"][1].begin();
//			it_function != state_potential_events["FileReader"][1].end();
//			it_function++) {
//
//		cout << "available functions: " << it_function->first << endl;
//	}

}

map<string, int> DFS(string class_name, int state) {
	map<string, int> result;
	map<string, int> child_result;
	if (flaged_states == NULL)
		flaged_states = new map<int, int>;
	(*flaged_states)[state] = 1;
	map<int, map<string, int> >::iterator it_state;
	map<string, int>::iterator it_transition;

	it_state = (*clap_automaton)[class_name].find(state);
	if (it_state != (*clap_automaton)[class_name].end()) {
		result = (*clap_automaton)[class_name][state];
		for (it_transition = it_state->second.begin();
				it_transition != it_state->second.end(); it_transition++) {
			if ((*flaged_states)[it_transition->second] != 1) {
				child_result = DFS(class_name, it_transition->second);
				result.insert(child_result.begin(), child_result.end());
			}

		}

	}
	return result;

}

string current_path() {
	char cwd[256];

	getcwd(cwd, sizeof(cwd));
	string path = cwd;

	return path;

}

vector<string> read_file(string file) {
	vector<string> lines;

	cout << "file:  " << file << endl;
	fstream fin(file.c_str());  //open automaton files
	string ReadLine;
	while (getline(fin, ReadLine))  //read file by line
	{
		lines.push_back(ReadLine);
	}
	fin.close();
	return lines;
}

vector<string> searchDir(char * dir) {
	vector<string> files;
	DIR *d;
	struct dirent * entry;

	unsigned char isFile = 0x8;
	d = opendir(dir);
	entry = readdir(d);

//	cout<<"dir:"<<path<<endl;
	while (entry != NULL) {
//		if (0 != strcmp(".", entry->d_name) && //Skip those directories
//				0 != strcmp("..", entry->d_name)) {
//			if (S_ISDIR(buf.st_mode))        //Check if sub directory
//			{
//				//searchDir(name);
//				continue;
//			}
//			char * name = entry->d_name;
//			stat(name, &buf);
//			files.push_back(string(name));
//			//cout << name<<endl;
//			//Formating
//
//			//New line for next file
//		}
		if (entry->d_type == isFile) {
			char * name = entry->d_name;
			//	cout<<name<<endl;
			files.push_back(name);
		}

		entry = readdir(d);             //Next file in directory
	}
	closedir(d);
	return files;
}

vector<string> split_string(string input) {
	vector<string> output;

	string sTmp;

	istringstream istr(input);
	while (!istr.eof()) {
		istr >> sTmp; //get a word
		//cout << "::" << sTmp << endl;
		output.push_back(sTmp);
	}
	return output;
//
//	 char name[256], title[256];
//
//	  cout << "Enter your name: ";
//	  cin.getline (name,256);

}

vector<string> split_string(string input, string split_by) {

	vector<string> str_list;
	if (input.size() < 1)
		return str_list;
	int comma_n = 0;
	do {
		std::string tmp_s = "";
		comma_n = input.find(split_by);
		if (-1 == comma_n) {
			tmp_s = input.substr(0, input.length());
			str_list.push_back(tmp_s);
			break;
		}
		tmp_s = input.substr(0, comma_n);
		input.erase(0, comma_n + split_by.size());
		str_list.push_back(tmp_s);
	} while (true);
	return str_list;
}

