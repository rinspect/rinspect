#include "naling.def"
#ifdef NLZ_FLAG
#include "memory_model_enum.hh"
#include <ctime>  // srand(time(0))
#include <cstdlib>  // rand
#endif

#include <cassert>
#include <cstring>

#include <utility>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <signal.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <unistd.h>

#include "scheduler.hh"
#include "next_state.hh"

#include "yices_path_computer_singleton.hh"

using namespace std;

extern Scheduler* g_scheduler;
extern int verboseLevel;

extern bool config_lin_check_flag;
extern bool config_lin_serial_flag;
extern bool config_lin_quasi_flag;
extern bool quasi_flag;

extern int total_check;
extern int total_lin;
extern int total_not_lin;

#ifdef NLZ_FLAG
#define MAX_BOUND 1
#endif
void verbose(int level, string str) {
	if (verboseLevel >= level)
		cout << str << endl;
}

using std::vector;
inline void check_target_status(int sut_pid) {
	if (sut_pid != -1) {
		int stat_loc;
		int res = waitpid(sut_pid, &stat_loc, WNOHANG);
		if (WIFSIGNALED(stat_loc)) {
			cout << "target failure (e.g., segfault)" << endl;
		}
		if (WIFEXITED(stat_loc)) {
			cout << "target exit with (" << WEXITSTATUS(stat_loc) << ")"
					<< endl;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//
// some signal handlers for cleaning up
// 
/////////////////////////////////////////////////////////////////////////////

void sig_alarm(int signo) {
	//g_scheduler->resetReplayStatus();
}

void sig_int(int signo) {
	cout << "===================================" << endl;
	cout << "(SIG_INT) Interrupted!  " << endl;
	cout << "sig_int is fired .... !\n";
	g_scheduler->stop();

	cout << "Total number of runs:  " << g_scheduler->run_counter << endl;
	if (setting.stateful_flag) {
		cout << "Total number of states: " << g_scheduler->num_of_states
				<< endl;
		cout << "Truncated Branches: " << g_scheduler->num_of_truncated_branches
				<< endl;
	}

	cout << "Transitions explored: " << g_scheduler->num_of_transitions << endl;
	cout << "===================================" << endl;

	//cout << g_scheduler->state_stack.toString() << endl;
	exit(-1);
}

void sig_abort(int signo) {
	cout << "===================================" << endl;
	cout << "sig_abort is fired .... !\n";
	check_target_status(g_scheduler->sut_pid);

	g_scheduler->stop();

	cout << "Total number of runs:  " << g_scheduler->run_counter << endl;
	if (setting.stateful_flag) {
		cout << "Total number of states: " << g_scheduler->num_of_states
				<< endl;
		cout << "Truncated Branches: " << g_scheduler->num_of_truncated_branches
				<< endl;
	}

	cout << "Transitions explored: " << g_scheduler->num_of_transitions << endl;
	cout << "===================================" << endl;
	//cout << g_scheduler->state_stack.toString() << endl;
	exit(-1);
}

void sig_pipe(int signo) {
	throw SocketException("unknown");
}

//////////////////////////////////////////////////////////////////////////////
//
//     The implementation of Scheduler
// 
//////////////////////////////////////////////////////////////////////////////

Scheduler::Scheduler() :
		max_errors(1000000), num_of_errors_detected(0), num_of_transitions(0), num_of_states(
				0), num_of_truncated_branches(0), num_killed(0), sut_pid(-1), run_counter(
				1) {
	sigset_t sst;
	int retval;

	sigemptyset(&sst);
	sigaddset(&sst, SIGPIPE);
	retval = sigprocmask(SIG_BLOCK, &sst, NULL);
	assert(retval != -1);

	retval = pthread_sigmask(SIG_BLOCK, &sst, NULL);
	assert(retval != -1);

	signal(SIGINT, sig_int);
	signal(SIGABRT, sig_abort);

}

Scheduler::~Scheduler() {
}

/**
 *  set up the server socket for listening 
 * 
 */
bool Scheduler::init() {
	int retval;
	char buf[64];

	setenv("INSPECT_SOCKET_FILE", setting.socket_file.c_str(), 1);

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%d", setting.timeout_val);
	setenv("INSPECT_TMEOUT_VAL", buf, 1);

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%d", setting.max_threads);
	setenv("INSPECT_BACKLOG_NUM", buf, 1);

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%d", (int) setting.stateful_flag);
	setenv("INSPECT_STATEFUL_FLAG", buf, 1);

	max_errors = setting.max_errors;

	retval = event_buffer.init(setting.socket_file, setting.timeout_val,
			setting.max_threads);

	assert(retval);

	if (setting.replay_file != "") {
		read_replay_file();
	}

	return true;
}

void Scheduler::stop() {
	event_buffer.close();
}

/** 
 *  Restart the system under test
 */
void Scheduler::exec_test_target(const char* path) {
	int retval;
	int pid = fork();
	if (pid == 0) {
		int sub_pid = fork();
		if (sub_pid == 0) {
			//retval = ::execl(path, path, NULL);
			retval = ::execvp(setting.target_argv[0], setting.target_argv);
			assert(retval != -1);
		} else {
			ofstream os(".subpid");
			os << sub_pid << endl;
			os.close();
			exit(0);
		}
	} else {
		waitpid(pid, NULL, 0);
		ifstream is(".subpid");
		int sub_pid;
		is >> sub_pid;
		//cout << " sub_pid = " << sub_pid <<endl;
		system("rm -f .subpid");
		is.close();

		sut_pid = sub_pid;
	}
}

void Scheduler::run() {
	struct timeval start_time, end_time;
	gettimeofday(&start_time, NULL);

	try {

		if (yices_path_computer_singleton::getInstance()->game_mode) {

			this->free_run();
		} else {
			//RUN # 1
			this->monitor_first_run();

#ifdef NLZ_EVEC
#else
			//check argument --yices
			if (yices_path_computer_singleton::getInstance()->run_yices_replay) {

				yices_path_computer_singleton::getInstance()->compute_new_trace();

				if (yices_path_computer_singleton::getInstance()->run_yices_replay) {
					this->yices_run();
				}

			}
#endif
			if (config_lin_check_flag
					&& (!config_lin_serial_flag || quasi_flag)) {
				event_buffer.linChecker->print_check_trace();
				event_buffer.linChecker->clear();
			}
			while (state_stack.has_backtrack_points()
					&& yices_path_computer_singleton::getInstance()->run_yices_replay
							== false) {
				verbose(3, "has backtrack points");
				run_counter++;

				if (setting.replay_file != "") {
					cout << "Replayed the trace '" << setting.replay_file << "'"
							<< endl;
					break;
				}
				if (setting.max_runs != -1 && run_counter >= setting.max_runs) {
					cout << "@@@CLAP: Reached MaxRuns (" << run_counter << ")" << endl;
					break;
				}
				if (setting.max_seconds != -1) {
					gettimeofday(&end_time, NULL);
					int sec;
					int usec;
					sec = end_time.tv_sec - start_time.tv_sec;
					usec = end_time.tv_usec - start_time.tv_usec;
					if (usec < 0) {
						usec += 1000000;
						sec--;
					}
					if (sec >= setting.max_seconds) {
						cout << "@@@CLAP: Reached MaxSeconds (" << sec << "." << usec
								<< ")" << endl;
						break;
					}
				}
				/*
				 if (num_of_errors_detected >= max_errors) {
				 cout << "Reached MaxError (" << max_errors << ")" << endl;
				 break;
				 }
				 */

				this->backtrack_checking(); //RUN # 2,3,4,...
				if (config_lin_check_flag
						&& (!config_lin_serial_flag || quasi_flag)) {
					event_buffer.linChecker->print_check_trace();
					event_buffer.linChecker->clear();
				}

				//cout << state_stack.toString();
			}
		}

	} catch (AssertException & e) {
		cout << endl;
		cout << "=================================" << endl;
		cout << "@@@CLAP: Caught AssertException" << endl;
		if (verboseLevel >= 1) {
			cout << state_stack.top()->toString() << endl;
		}
		kill(sut_pid, SIGTERM);
		sut_pid = -1;
		exit_status = -1;
	} catch (DeadlockException & e) {
		cout << endl;
		cout << "========== ========================" << endl;
		cout << "@@@CLAP: Caught DeadlockException" << endl;
		if (verboseLevel >= 1) {
			cout << state_stack.top()->toString() << endl;
		}
		kill(sut_pid, SIGTERM);
		sut_pid = -1;
		exit_status = -1;
	} catch (DataraceException & e) {
		cout << endl;
		cout << "===================================" << endl;
		cout << "@@@CLAP: Caught DataraceException (" << e.detail << ")" << endl;
		if (verboseLevel >= 1) {
			cout << state_stack.top()->toString() << endl;
		}
		kill(sut_pid, SIGTERM);
		sut_pid = -1;
		exit_status = -1;
	} catch (IllegalLockException & e) {
		cout << endl;
		cout << "===================================" << endl;
		cout << "@@@CLAP: Caught IllegalLockException (" << e.detail << ")" << endl;
		if (verboseLevel >= 1) {
			cout << state_stack.top()->toString() << endl;
		}
		kill(sut_pid, SIGTERM);
		sut_pid = -1;
		exit_status = -1;
	} catch (SocketException & e) {
		cout << endl;
		cout << "===================================" << endl;
		cout << "@@@CLAP: Caught SocketException (" << e.detail << ")" << endl;
		cout << "could be a target failure (e.g., segfault)" << endl;
		if (verboseLevel >= 1) {
			cout << state_stack.top()->toString() << endl;
		}
		kill(sut_pid, SIGTERM);
		sut_pid = -1;
		exit_status = -1;
	} catch (ThreadException & e) {
		cout << endl;
		cout << "===================================" << endl;
		cout << "Caught ThreadException" << endl;
		if (verboseLevel >= 1) {
			cout << state_stack.top()->toString() << endl;
		}
		kill(sut_pid, SIGTERM);
		sut_pid = -1;
		exit_status = -1;
	} catch (NullObjectException & e) {
		cout << endl;
		cout << "===================================" << endl;
		cout << "@@@CLAP: Caught NullObjectException" << endl;
		if (verboseLevel >= 1) {
			cout << state_stack.top()->toString() << endl;
		}
		kill(sut_pid, SIGTERM);
		sut_pid = -1;
		exit_status = -1;
	}

	if (verboseLevel >= -1) {
		cout << endl;
		cout << "===================================" << endl;
		cout << "Total number of runs:  " << run_counter
				<< ",   sleepset killed runs: " << num_killed << endl;
		cout << "Transitions explored: " << num_of_transitions << endl;

		if (config_lin_check_flag) {

			cout << "total_check  : " << total_check << endl;
			cout << "total_lin    : " << total_lin << endl;
			cout << "total_not_lin: " << total_not_lin << endl;

		}

	}

}

void Scheduler::exec_transition(InspectEvent & event) {
	event_buffer.approve(event);

	if (event.type == THREAD_END || event.type == MISC_EXIT
			|| event.type == PROPERTY_ASSERT)
		return;

#if 1
	//chao: 1/7/2013 -- this wait is necessary; othewise, when replay a
	//trace, events from different threads may race

	// wait for the event to complete before approving another thread
	while (!event_buffer.has_event(event.thread_id)) {
		event_buffer.collect_events();
	}
#endif

}

State * Scheduler::get_initial_state() {
	State * init_state;

	InspectEvent event;

	init_state = new State();
	event = event_buffer.get_the_first_event();
	assert(event.type == THREAD_START);
	assert(event.thread_id == 0);

	init_state->add_to_enabled(event);
	init_state->clock_vectors.add_the_first_thread();

	return init_state;
}

InspectEvent Scheduler::get_latest_executed_event_of_thread(State * state,
		int thread_id) {
	State * ptr;
	InspectEvent dummy;

	ptr = state;
	while (ptr != NULL) {
		if (ptr->sel_event.thread_id == thread_id)
			return ptr->sel_event;
		ptr = ptr->prev;
	}

	return dummy;
}

void Scheduler::check_property(State * state) {
	if (setting.report_race_flag && state->check_race()) {
		bool report_it = true;
		if (setting.race_only_flag) {
			num_of_errors_detected++;
			if (num_of_errors_detected <= setting.max_errors) {
				report_it = false;
			}
		}
		if (report_it == true) {
			throw DataraceException("Found a data race");
		}
	} else if (state->sel_event.type == PROPERTY_ASSERT) {
		throw AssertException();
	}
}
#ifdef NLZ_EVEC
#else
void Scheduler::yices_run() {

	map<int, map<int, InspectEvent> >::iterator it;
	for (it = yices_path_computer_singleton::getInstance()->result_trace.begin();
			it
					!= yices_path_computer_singleton::getInstance()->result_trace.end();
			it++) {

		cout << "replay trace: " << it->first << endl;

		InspectEvent event;
		State * init_state, *new_state, *current_state;
		TransitionSet::iterator tit;

		event_buffer.reset();
		thread_table.reset();
		state_stack.stack.clear();
		yices_path_computer_singleton::getInstance()->event_map.clear();

		run_counter++;

		cout << " === run  " << run_counter
				<< ": the new trace from SMT solver ===\n";

		this->exec_test_target(setting.target.c_str());

		init_state = this->get_initial_state();

		state_stack.push(init_state);

//		cout << "replay size:  "
//				<< yices_path_computer_singleton::getInstance()->event_map.size()
//				<< endl;
		map<int, InspectEvent> replay_trace = it->second;

		//chao: 7/12/2012, do not catch deadlock exception here, throw
		//it up to the caller

		// try {
		current_state = state_stack.top();
		for (unsigned int i = 1; i <= replay_trace.size(); i++) {
			InspectEvent& anticipated_ev = replay_trace[i];

			event = current_state->prog_state->enabled.get_transition(
					anticipated_ev.thread_id);
			if (event == InspectEvent::dummyEvent || event.type == UNKNOWN)
				event = event_buffer.get_event(anticipated_ev.thread_id);
//			else break;

			//replay failed?
			assert(event != InspectEvent::dummyEvent && event.type != UNKNOWN);
			assert(event.type == anticipated_ev.type);

			//update_backtrack_info(current_state);
			assert(current_state->clock_vectors.size() > 0);

			new_state = next_state(current_state, event, event_buffer);
			this->check_property(current_state);
			num_of_transitions++;
			if (event.type == THREAD_PRE_CREATE)
				i += 2;

			state_stack.push(new_state);
			assert(new_state->prev == current_state);
			current_state = new_state;
			//cout <<"aa"<< current_state->toString()<< endl;
		}

		/*
		 } catch (DeadlockException & e) {
		 kill(sut_pid, SIGTERM);
		 sut_pid = -1;
		 }
		 */
	}

}
#endif
void Scheduler::free_run() {
#ifdef NLZ_EVEC
#else
	InspectEvent event;
	State * init_state, *new_state, *current_state;
	TransitionSet::iterator tit;

	this->exec_test_target(setting.target.c_str());

	init_state = this->get_initial_state();

	state_stack.push(init_state);

	current_state = state_stack.top();
	while (!current_state->is_enabled_empty()) {

		int choice = -1;
		if (current_state->prog_state->enabled.size() > 1) {
			InspectEventMapIterator it;

			map<int, int> available_events;
			for (it = current_state->prog_state->enabled.begin();
					it != current_state->prog_state->enabled.end(); it++) {

				if (it->second.type == 23) {		//thread create first
					choice = it->second.thread_id;
				} else if (it->second.type == 25) {		//thread join first
					choice = it->second.thread_id;
				}
				if (it->second.type != 21) {		//thread end last
					available_events[available_events.size()] =
							it->second.thread_id;
					//cout << "automatically ignored:  " << event.toString() << endl;

				}

				cout << it->second.thread_id << ": ----[enabled]: "
						<< it->second.toString() << endl;

			}
			if (available_events.size() == 1) {
				choice = available_events[0];
			}

			if (choice != -1) {
				event = current_state->prog_state->enabled.get_transition(
						choice);
				cout << "automatically chose:  " << event.toString() << endl;

			} else {
				while (available_events.size() > 1) {
					cout << "Please choose by thread id:   ";
					cin >> choice;

					event = current_state->prog_state->enabled.get_transition(
							choice);
					if (event.valid()) {
						cout << "              chose:  " << event.toString()
								<< endl;
						break;
					}

				}
			}

		}

		if (choice == -1)
			event = current_state->prog_state->enabled.get_transition();
		assert(current_state->clock_vectors.size() > 0);

		new_state = next_state(current_state, event, event_buffer);

		this->check_property(current_state);
		num_of_transitions++;

		state_stack.push(new_state);
		assert(new_state->prev == current_state);
		current_state = new_state;
		choice = -1;
	}

	verbose(2, state_stack.toString2());

	if (!current_state->prog_state->disabled.empty()
			& current_state->sleepset.empty()) {
		//chao: 6/12/2012, do not handle exceptions here -- leave to the caller
		throw DeadlockException();
	}
#endif
}

void Scheduler::monitor_first_run() {
	int thread_counter = 0;

	int step_counter = 0;
	InspectEvent event;
	State * init_state, *new_state, *current_state;
	TransitionSet::iterator tit;
	//int replay_depth = 0; // used only for replay trace

	cout << " === run " << run_counter << " ===\n";

	this->exec_test_target(setting.target.c_str());

	init_state = this->get_initial_state();

	state_stack.push(init_state);
#ifdef NLZ_EVEC
#else
	//chao: 6/12/2012, do not catch exceptions here -- leave them to the caller

	//-------------------------------------------------------------
	//Replay the given trace (prefix) if it is available
	//-------------------------------------------------------------
	current_state = state_stack.top();
	for (unsigned int i = 0; i < error_trace.size(); i++) {
		InspectEvent& anticipated_ev = error_trace[i];

		event = current_state->prog_state->enabled.get_transition(
				anticipated_ev.thread_id);
		if (event == InspectEvent::dummyEvent || event.type == UNKNOWN)
			event = event_buffer.get_event(anticipated_ev.thread_id);

		//replay failed?
		assert(event != InspectEvent::dummyEvent && event.type != UNKNOWN);
		assert(event.type == anticipated_ev.type);

		update_backtrack_info(current_state);
		assert(current_state->clock_vectors.size() > 0);

		new_state = next_state(current_state, event, event_buffer);

		this->check_property(current_state);
		num_of_transitions++;
		if (event.type == THREAD_PRE_CREATE)
			i += 2;

		state_stack.push(new_state);
		assert(new_state->prev == current_state);
		current_state = new_state;
	}
#endif
	//-------------------------------------------------------------
	//Start the free run (with arbitrary schedule)
	//-------------------------------------------------------------
	current_state = state_stack.top();
	while (!current_state->is_enabled_empty()) {
		update_backtrack_info(current_state);

		if (setting.max_spins != -1)
			event = current_state->get_transition_no_spin();
		else
			event = current_state->get_transition();

		assert(current_state->clock_vectors.size() > 0);

		new_state = next_state(current_state, event, event_buffer);
		//verbose(2, state_stack.toString());//
#ifdef NLZ_EVEC
#else
		if (0
				&& yices_path_computer_singleton::getInstance()->verbose
						>= yices_path_computer_singleton::getInstance()->v_2) {
			InspectEventMapIterator it;

			for (it = new_state->prog_state->enabled.begin();
					it != new_state->prog_state->enabled.end(); it++) {
				cout
						<< "--------------------------------------------[enabled]: "
						<< it->second.toString() << endl;

			}

		}
#endif
		this->check_property(current_state);
		num_of_transitions++;

		state_stack.push(new_state);
		assert(new_state->prev == current_state);
		current_state = new_state;

		if (setting.max_events != -1
				&& setting.max_events < state_stack.depth()) {
			// when the max number of events is reached
			return;
		}
	}

	verbose(2, state_stack.toString2());

	if (!current_state->prog_state->disabled.empty()
			& current_state->sleepset.empty()) {
		//chao: 6/12/2012, do not handle exceptions here -- leave to the caller
		throw DeadlockException();
	}
	verbose(4,state_stack.toString());

}

bool Scheduler::examine_state(State * old_state, State * new_state) {
	return false;
}

void Scheduler::backtrack_checking() {
	State * state = NULL, *current_state = NULL, *new_state = NULL;
	InspectEvent event, event2;
	int depth, i;

	cout << " === run " << run_counter << " ===\n";

	event_buffer.reset();

	thread_table.reset();

	state = state_stack.top();
	while (state != NULL && state->backtrack.empty()) {
		state_stack.pop();
		delete state;
		state = state_stack.top();
	}
	depth = state_stack.depth();

	this->exec_test_target(setting.target.c_str());
	event = event_buffer.get_the_first_event();
	event_buffer.update_output_folders();
	exec_transition(event);

	for (i = 1; i < depth - 1; i++) {
		state = state_stack[i];
		if (state->sel_event.type == THREAD_CREATE) {
			event = state->sel_event;

			InspectEvent pre, post, first;
			pre = event_buffer.get_event(event.thread_id);
			exec_transition(pre);
			post = event_buffer.get_event(event.thread_id);
			exec_transition(post);
			first = event_buffer.get_event(event.child_id);
			exec_transition(first);

			string thread_nm;
			thread_table.add_thread(post.child_id, thread_nm, post.thread_arg);
		} else {
#ifdef NLZ_COMM
		    std::vector<InspectEvent> ev_vec = event_buffer.get_events(state->sel_event.thread_id);
		    for(std::vector<InspectEvent>::iterator vit = ev_vec.begin(); vit != ev_vec.end(); vit++){ 
			if (state->sel_event == *vit){
			    break;
			}
		    }
		    if (vit == ev_vec.end()) {
			assert(state->sel_event.future == 1);
		    }else{
			assert (state->sel_event.future == 0 || state->sel_event.future == -1);//atomic
		    }
		    exec_transition(state->sel_event);
#else
		    event = event_buffer.get_event(state->sel_event.thread_id);
		    assert(event.valid());
		    if (event != state->sel_event) {
			cout << "event:      " << event.toString() << endl;
			cout << "sel_event:  " << state->sel_event.toString() << endl;
			assert(event == state->sel_event);
		    }
		    exec_transition(event);
#endif
		}
	}

	cout<<"---------arrive at backtrack point--------, depth= "<<depth - 1<<endl;
	assert(state_stack[depth - 1] == state_stack.top());
	state = state_stack.top();


#ifdef NLZ_EVEC
	TransitionSet::iterator it;
	for (it = state->prog_state->enabled.begin();
			it != state->prog_state->enabled.end(); it++) {
	    assert (! (it->second.empty()) );
	    std::vector<InspectEvent>& enabled_vec = it->second;
	    std::vector<InspectEvent> ev_vec_got = event_buffer.get_events(enabled_vec.front().thread_id);
	    for(std::vector<InspectEvent>::iterator vit=ev_vec_got.begin(); vit!=ev_vec_got.end(); ++vit){ // for each event received
		std::vector<InspectEvent>::iterator vit2;
		for(vit2=enabled_vec.begin(); vit2!=enabled_vec.end(); ++vit2){ // determine if it is in enabled
		    if (*vit2 == *vit) break;
		}
		if(vit2==enabled_vec.end()){
		    cout<<"==============debug info:\n";
		    assert(vit2!=enabled_vec.end() && "!!!!!!!! events got is not in enabled!");
		}
	    }
	}

	for (it = state->prog_state->disabled.begin();
			it != state->prog_state->disabled.end(); it++) {
	    assert (! (it->second.empty()) );
	    std::vector<InspectEvent>& disabled_vec = it->second;
	    std::vector<InspectEvent> ev_vec_got = event_buffer.get_events(disabled_vec.front().thread_id);
	    for(std::vector<InspectEvent>::iterator vit=ev_vec_got.begin(); vit!=ev_vec_got.end(); ++vit){ // for each event received
		std::vector<InspectEvent>::iterator vit2;
		for(vit2=disabled_vec.begin(); vit2!=disabled_vec.end(); ++vit2){ // determine if it is in disabled
		    if (*vit2 == *vit) break;
		}
		if(vit2==disabled_vec.end()){
		    cout<<"!!!!!!!! events got is not in disabled!"<<endl;
		    abort();
		}
	    }
	}
#else
	TransitionSet::iterator it;
	for (it = state->prog_state->enabled.begin();
			it != state->prog_state->enabled.end(); it++) {
		event = it->second;
		event2 = event_buffer.get_event(event.thread_id);
		assert(event == event2);
	}

	for (it = state->prog_state->disabled.begin();
			it != state->prog_state->disabled.end(); it++) {
		event = it->second;
		event2 = event_buffer.get_event(event.thread_id);
		assert(event == event2);
	}
#endif

#ifdef NLZ_EVEC
	event = state->backtrack.get_front_transition(); 
	
#else
	event = state->backtrack.get_transition();//6.5 here it cause a bug when sel-ev is write and buffer is full, permit event is read, then it reply the same thing and not stop.
#endif

	if (!event.valid()) {
		cout << event.toString() << endl;
		assert(event.valid());
	}
	state->backtrack.remove(event);

	current_state = next_state(state, event, event_buffer);
	this->check_property(state);


	num_of_transitions++;
	//state->sleepset.remove(event);  // TODO: why remove? Maybe: because we are doing backtrack checking, if we found new backtrack point in follow, next run we should choose the same transition here. So doneset doesn't mean we cannot do it again, it only indicates we ever did it.
	state_stack.push(current_state);

	while (current_state->has_executable_transition()) {

		update_backtrack_info(current_state);

		if (setting.max_spins != -1)
			event = current_state->get_transition_no_spin();
		else
			event = current_state->get_transition();
	
		new_state = next_state(current_state, event, event_buffer);
		this->check_property(current_state);

		num_of_transitions++;

		state_stack.push(new_state);
		current_state = new_state;

		if (setting.max_events != -1
				&& setting.max_events < state_stack.depth()) {
			// when the max number of events is reached
			return;
		}

	}

	verbose(4, state_stack.toString());
	
	if (!current_state->prog_state->disabled.empty()
			& current_state->sleepset.empty()) {
		//chao: 6/12/2012, do not handle exceptions here -- leave to the caller
		throw DeadlockException();
	}

	if (!current_state->has_been_end()) {
		kill(sut_pid, SIGTERM);
		//cout << "Kill  " << sut_pid << flush << endl;
		num_killed++;
	}

}

void Scheduler::get_mutex_protected_events(State * state1, State * state2,
		int tid, vector<InspectEvent> & events) {
	State * state = NULL;

	assert(state1 != NULL);
	assert(state2 != NULL);

	events.clear();
	state = state1->next;
	while (state != state2) {
		if (state->sel_event.thread_id == tid)
			events.push_back(state->sel_event);
		state = state->next;
	}

	assert(state == state2);
}

bool Scheduler::is_mutex_exclusive_locksets(Lockset * lockset1,
		Lockset * lockset2) {
	if (lockset1 == NULL || lockset2 == NULL)
		return false;
	return lockset1->mutual_exclusive(*lockset2);
}

void Scheduler::update_backtrack_info(State * state) {
#ifdef NLZ_EVEC
#else
	if (setting.max_pcb != -1)
		PCB_update_backtrack_info(state);
	else if (setting.max_pset != -1)
		PSET_update_backtrack_info(state);
	else
#endif
	    DPOR_update_backtrack_info(state);
}

#ifdef NLZ_EVEC
#else
void Scheduler::PCB_update_backtrack_info(State * s) {
	if (s == NULL || s->prev == NULL)
		return;
	if (setting.max_pcb != -1 && s->prev->pcb_count >= setting.max_pcb)
		return;

	State *state = s->prev;

	EventCategory ec = get_event_category(state->sel_event.type);
	if (ec == EC_THREAD || ec == EC_SYMMETRY || ec == EC_LOCAL
			|| ec == EC_PROPERTY) {
		return;
	}

	TransitionSet::iterator it;
	for (it = state->prog_state->enabled.begin();
			it != state->prog_state->enabled.end(); it++) {
		InspectEvent ev = it->second;
		if (ev.invalid())
			continue;
		if (state->done.has_member(ev))
			continue;
		if (state->sleepset.has_member(ev))
			continue;

		state->backtrack.insert(ev);
	}
}
#endif

void Scheduler::DPOR_update_backtrack_info(State * state) {
 	ProgramState *ps = state->prog_state;
	TransitionSet::iterator it;
#ifdef NLZ_EVEC
	InspectEvent tmp_ev;
	if(setting.memory_model == SC_MODEL){
	    for (it = ps->enabled.begin(); it != ps->enabled.end(); it++) {
		InspectEvent event = *(it->second.begin());	
		DPOR_update_backtrack_info(state, event);
	    }
	}
	else{
	for (it = ps->enabled.begin(); it != ps->enabled.end(); it++) {
	    for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); vit++){
		if ((vit->type == OBJ_READ && setting.memory_model == TSO_MODEL ) 
		    || ((vit->type == OBJ_READ || vit->type == OBJ_WRITE) && setting.memory_model == PSO_MODEL ) ) {
		    int i = state_stack.depth()-2;
                    #ifdef NLZ_BBOUND
		    int n_write = 0;
                    #endif
		    while( (state_stack[i]->sel_event.type != OBJ_READ && state_stack[i]->sel_event.type != OBJ_WRITE)
			   || (state_stack[i]->enabled_due.find(vit->thread_id) != state_stack[i]->enabled_due.end()
			       && state_stack[i]->enabled_due.find(vit->thread_id)->second == true)
			){
		
			if (vit->type == OBJ_WRITE && state_stack[i]->sel_event.obj_id == vit->obj_id){i--;break;} // for pso, i--,due to the following i++ and i+1;
			if (i>0){
#ifdef NLZ_BBOUND 
			    if(setting.max_bound > 0 && (state_stack[i]->sel_event.type == OBJ_WRITE)){
				cout<<"-----------boudning info is n_write "<<n_write<<endl;
				//	if(setting.max_bound>1 && vit->thread_id == state_stack[i]->sel_event.thread_id)
				//  n_write++;
				 n_write++;
				if (n_write >= setting.max_bound ){
				    if(state_stack[i]->sel_event.future ==-1 ) {i--;   break;}
				    i--;
				    break;
				}
			    }
#endif			    
			    i--; // jump back
			 }
			else { break; }
		    }  // when exit, i at the point that enabled_due is false

		    i++; // to the point that enabled_due is true
		    for(i=i+1; i<state_stack.depth()-1; ++i){
	
#ifdef NLZ_ATOMIC
			if(state_stack[i]->sel_event.future ==-1 || vit->future == -1 ){//for atomic
			    break;
			}
#endif
			if (state_stack[i]->prog_state->enabled.has_write_but_read(vit->thread_id)==false)  continue;
			if (state_stack[i]->prog_state->enabled.has_member(*vit)) continue;// the same could not be changed
			tmp_ev = *vit;
		
			tmp_ev.future = 1;  // TODO: may also need to modify tmp_ve's clock vector here
#ifdef NLZ_SAFER
			if(state_stack[i]->prog_state->enabled.has_write_but_read(tmp_ev.thread_id)==false){
			    cout<<"============debug info=====\n";
			    if (verboseLevel >=4)
				cout<<state_stack.toString()<<endl;
			    else
				cout<<state->toString()<<endl;
			    assert(state_stack[i]->prog_state->enabled.has_write_but_read(tmp_ev.thread_id));
			}
#endif
		       
			state_stack[i]->add_transition(tmp_ev);
			if(vit->type ==OBJ_READ) 
			    state_stack[i]->enabled_due[tmp_ev.thread_id] = false;
			
			NLZ_DPOR_update_backtrack_info(state_stack[i], tmp_ev);
		    }		    
		}
		NLZ_DPOR_update_backtrack_info(state, *vit);
	    }
	}
	}

#else
	for (it = ps->enabled.begin(); it != ps->enabled.end(); it++) {
		InspectEvent event = it->second;
		DPOR_update_backtrack_info(state, event);
	}
#endif
}

#ifdef NLZ_COMM
void Scheduler::NLZ_DPOR_update_backtrack_info(State * state, InspectEvent &event) {
	State * old_state = last_conflicting_state(state, event);
	if (old_state == NULL)
		return;

	Lockset * lockset1, *lockset2;
	lockset1 = old_state->get_lockset(old_state->sel_event.thread_id);
	lockset2 = state->get_lockset(event.thread_id);
	if (is_mutex_exclusive_locksets(lockset1, lockset2))
	{
	    //for mutex
	    old_state->remove_from_enabled(old_state->sel_event);
	    return;
	}
	ClockVector * vec1, *vec2;
	
	if(!(old_state->clock_vectors.vecs.size() > (old_state->sel_event.thread_id)) ||
	   !(state->clock_vectors.vecs.size() > (event.thread_id) ))
	{
	    return; //at this time, it should not be concurrent, due to clock vector is just created.
	}
	vec1 = old_state->get_clock_vector(old_state->sel_event.thread_id);
	vec2 = state->get_clock_vector(event.thread_id);
	if(setting.disable_dpor_flag==false ){
	    if (vec1->is_concurrent_with(*vec2) == false)
		return;
	}

	int tids[2];
	tids[0] = old_state->sel_event.thread_id;
	tids[1] = event.thread_id;

       	for (int i=0; i<2; ++i){  //just update backtrack which has different thread // TODO: decide whether to add sel_event.thread_id
	    if (old_state->prog_state->enabled.has_member(tids[i]) == false){

		TransitionSet::iterator tit;
		for (tit = old_state->prog_state->enabled.begin();
				tit != old_state->prog_state->enabled.end(); tit++) {
		    for(std::vector<InspectEvent>::iterator vit = tit->second.begin(); vit != tit->second.end(); vit++){
			InspectEvent tmp_ev = *vit;

			if (tmp_ev.invalid())
				continue;
			if (old_state->done.has_member(tmp_ev))
				continue;
			if(tmp_ev.future != 1 ){
			if (old_state->sleepset.has_member(tmp_ev))
				continue;
			}
#ifdef NLZ_NO_DPOR
			if( old_state->sel_event.type== OBJ_READ || old_state->sel_event.type== OBJ_WRITE || old_state->sel_event.type == MUTEX_LOCK){
			    old_state->backtrack.insert(tmp_ev);
			}
#else	  
			old_state->backtrack.insert(tmp_ev);
#endif
		
		    }
		}

		return;
		
	    }else{
	
		std::vector<InspectEvent>& ev_vec =  old_state->prog_state->enabled.get_transition_vec(tids[i]);

		for (std::vector<InspectEvent>::iterator vit = ev_vec.begin(); vit != ev_vec.end(); vit++){
		    InspectEvent& alt_event = *vit;
		    if(old_state->prog_state->is_enabled(event)){if(alt_event!=event) continue;} 
		    
		    if (old_state->done.has_member(alt_event))
			continue;
		    if(alt_event.future != 1 ){
			if (old_state->sleepset.has_member(alt_event))
			    continue;
		    }
		    if (old_state->backtrack.has_member(alt_event))
			continue;

#ifdef NLZ_COMM_TODO  
		    if (setting.symmetry_flag) {
			if (thread_table.is_symmetric_threads(alt_event.thread_id,
							      old_state->sel_event.thread_id)) {
			    InspectEvent symm1, symm2;
			    symm1 = old_state->symmetry.get_front_transition(alt_event.thread_id);  
			    symm2 = old_state->symmetry.get_front_transition(
				old_state->sel_event.thread_id);
			    if (symm1.valid() && symm2.valid() && symm1.obj_id == symm2.obj_id)
				return;
			}
		    }
#endif

		    if (setting.max_spins != -1) {  // TODO: figure out how to modify the following code
			if (old_state->prev != NULL) {
			    InspectEvent& prior_ev = old_state->prev->sel_event;
			    if (prior_ev.type == OBJ_READ && alt_event.type == OBJ_READ) {
				if (prior_ev.thread_id == alt_event.thread_id) {
				    if (prior_ev.inst_id == alt_event.inst_id) {
					// alt_event and prior_ev come from the same INSTRUCTION
					// (!!!busy waiting!!!)
					continue;
				    }
				}
			    }
			}
		    }

#ifdef NLZ_NO_DPOR
		    if( old_state->sel_event.type== OBJ_READ || old_state->sel_event.type== OBJ_WRITE || old_state->sel_event.type == MUTEX_LOCK){
			old_state->backtrack.insert(alt_event);
		    }
		 		    
#else	 
		    old_state->backtrack.insert(alt_event);
#endif
		}
	    }
	}
}
#endif
void Scheduler::DPOR_update_backtrack_info(State * state, InspectEvent &event) {
	State * old_state = last_conflicting_state(state, event);
	if (old_state == NULL)
		return;

	Lockset * lockset1, *lockset2;
	lockset1 = old_state->get_lockset(old_state->sel_event.thread_id);
	lockset2 = state->get_lockset(event.thread_id);
	if (is_mutex_exclusive_locksets(lockset1, lockset2))
		return;

	ClockVector * vec1, *vec2;
	vec1 = old_state->get_clock_vector(old_state->sel_event.thread_id);
	vec2 = state->get_clock_vector(event.thread_id);
	if (vec1->is_concurrent_with(*vec2) == false)
		return;

	InspectEvent alt_event;
#ifdef NLZ_EVEC
	alt_event = old_state->prog_state->enabled.get_front_transition(event.thread_id);  
#else
	alt_event = old_state->prog_state->enabled.get_transition(event.thread_id);
#endif
	if (alt_event.invalid() == true) {
		// chao: 1/7/2013 -- this is when POR fails (couldn't reduce)
		//  , and we make "backtrack == enabled"
		TransitionSet::iterator tit;
#ifdef NLZ_EVEC
		for (tit = old_state->prog_state->enabled.begin();
				tit != old_state->prog_state->enabled.end(); tit++) {
		    for(std::vector<InspectEvent>::iterator vit = tit->second.begin(); vit != tit->second.end(); vit++){
			InspectEvent tmp_ev = *vit;
			if (tmp_ev.invalid())
				continue;
			if (old_state->done.has_member(tmp_ev))
				continue;
			if (old_state->sleepset.has_member(tmp_ev))
				continue;
			old_state->backtrack.insert(tmp_ev);
			//cout << endl << "DBG chao1: adding to backtrack: " << tmp_ev.toString() << endl;
		    }
		}
#else
		for (tit = old_state->prog_state->enabled.begin();
				tit != old_state->prog_state->enabled.end(); tit++) {
			InspectEvent tmp_ev = tit->second;
			if (tmp_ev.invalid())
				continue;
			if (old_state->done.has_member(tmp_ev))
				continue;
			if (old_state->sleepset.has_member(tmp_ev))
				continue;

#ifdef NLZ_NO_DPOR
			if( old_state->sel_event.type== OBJ_READ || old_state->sel_event.type== OBJ_WRITE || old_state->sel_event.type == MUTEX_LOCK){
			    old_state->backtrack.insert(tmp_ev);// the old state would be no need to backtrack?
			}
#else	  
			old_state->backtrack.insert(tmp_ev);
#endif
			
		}
#endif
		// chao: 1/7/2013  -- I think a return should be added here
		return;
	}

	//chao, for debugging purpose only
	if (verboseLevel >= 3) {
		cout << __FUNCTION__ << "() reduction: " << "e"
				<< old_state->sel_event.eid << " -->-  e" << event.eid << endl;
	}

	//Reduction -- adding "alt_event" to "old_state->backtrack"
	if (old_state->done.has_member(alt_event))
		return;
	if (old_state->sleepset.has_member(alt_event))
		return;
	if (old_state->backtrack.has_member(alt_event))
		return;

	if (setting.symmetry_flag) {
		if (thread_table.is_symmetric_threads(alt_event.thread_id,
				old_state->sel_event.thread_id)) {
			InspectEvent symm1, symm2;
#ifdef NLZ_EVEC
			symm1 = old_state->symmetry.get_front_transition(alt_event.thread_id);  // TODO: understand symmetry
			symm2 = old_state->symmetry.get_front_transition(
					old_state->sel_event.thread_id);
#else
			symm1 = old_state->symmetry.get_transition(alt_event.thread_id);
			symm2 = old_state->symmetry.get_transition(
					old_state->sel_event.thread_id);
#endif
			if (symm1.valid() && symm2.valid() && symm1.obj_id == symm2.obj_id)
				return;
		}
	}

	if (setting.max_spins != -1) {
		if (old_state->prev != NULL) {
			InspectEvent& prior_ev = old_state->prev->sel_event;
			if (prior_ev.type == OBJ_READ && alt_event.type == OBJ_READ) {
				if (prior_ev.thread_id == alt_event.thread_id) {
					if (prior_ev.inst_id == alt_event.inst_id) {
						// alt_event and prior_ev come from the same INSTRUCTION
						// (!!!busy waiting!!!)
						return;
					}
				}
			}
		}
	}
#ifdef NLZ_NO_DPOR
	if( old_state->sel_event.type== OBJ_READ || old_state->sel_event.type== OBJ_WRITE || old_state->sel_event.type == MUTEX_LOCK){
	    old_state->backtrack.insert(alt_event);
	}
#else 
	old_state->backtrack.insert(alt_event);
#endif
	//cout << endl << "DBG chao2: adding to backtrack: " << alt_event.toString() << endl;
	assert(alt_event.valid());

}
//#endif

State* Scheduler::last_conflicting_state(State *state, InspectEvent &event) {
	State * old_state = state->prev;
	while (old_state != NULL) {
		if (dependent(old_state->sel_event, event)) {
			break;
		}
		old_state = old_state->prev;
	}
	return old_state;
}

bool Scheduler::dependent(InspectEvent &e1, InspectEvent &e2) {
	bool retval = false;
//for no-dpor
#ifdef NLZ_NO_DPOR
	if(setting.disable_dpor_flag==true && (e2.type==OBJ_READ || e2.type==OBJ_WRITE)) return true;
#endif
	retval = e1.dependent(e2);

	return retval;
}

#ifdef NLZ_EVEC
#else
void Scheduler::PSET_update_backtrack_info(State * state) {
	ProgramState *ps = state->prog_state;
	TransitionSet::iterator it;
	for (it = ps->enabled.begin(); it != ps->enabled.end(); it++) {
		InspectEvent event = it->second;
		DPOR_update_backtrack_info(state, event);
	}
}
#endif


#ifdef NLZ_BBOUND
int Scheduler::get_distance_between_states(State* state1, State* state2){
    int num=0;
    State * old_state = state1->prev;
    while (old_state != NULL) {
	if (state2 == old_state) { //cout<<"*************the distance is "<<num<<endl;
	    return num;
	}
	if (old_state->sel_event.type == OBJ_WRITE) {
	    num++;
	}
	old_state = old_state->prev;
    }
    return num;
}
#endif


