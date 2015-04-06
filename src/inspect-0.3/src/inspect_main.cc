#include "naling.def"
#include "inspect_ucg_graph.hh"
#include "scheduler.hh"
#include "scheduler_setting.hh"
#include <cstdlib>
#include <cstring> 
#include <iostream>
#include <sys/time.h>
#include "yices_c.h"
#include "yices_path_computer_singleton.hh"
#include "inspect_ucg_graph.hh"
#include "lin_checker.hh"

using namespace std;

Scheduler * g_scheduler = NULL;
int verboseLevel = -1;

/* functions below are defined in 'event_buffer.cc'  */
extern void set_config_echo_approved_event(bool val);
extern void set_config_log_approved_color(bool val);
extern void set_config_log_approved_event(bool val);
extern void set_config_target_trace_flag(bool val);
extern void set_config_lin_check_flag(bool val);
extern void set_config_lin_serial_flag(bool val);
extern void set_config_lin_quasi_flag(bool val);
extern bool quasi_flag;

extern void set_quasi(int number);

/* functions above are defined in 'event_buffer.cc'  */

/*****************************************************************************
 *
 *   main  function  for the scheduler
 *
 *****************************************************************************/

void print_usage() {
	cout
			<< "Inspect version 0.0.3 (c) University of Utah                                 \n"
			<< "                                                                             \n"
			<< "Usage:  inspect [options] test_target                                        \n"
			<< "                                                                             \n"
			<< "Options:                                                                     \n"
			<< "  --timeout            the maxium seconds that Inspect waits for a monitored \n"
			<< "                       thread to response                                    \n"
			<< "  --multi-errors(-me)  do not stop after revealing the first error           \n"
			<< "  --max-pcb            the maximum number of context switches allowed        \n"
			<< "  --max-pset           the maximum size of the Predecessor Set               \n"
			<< "  --max-runs           the maximum number of test runs                       \n"
			<< "  --max-events         the maximum number of events allowed in a run         \n"
			<< "  --max-spins          the maximum number of spins on the same event         \n"
			<< "  --tso-mode           let test_target run on simulated tso memory           \n"
			<< "  --pso-mode           let test_target run on simulated pso memory           \n"
			<< "  --bound (or -bo)     let test_target run under buffer bounded model        \n"	  	    	    
			<< "  --no-dpor(or -ndp)    let target run without dpor algorithm              \n"
			<< "  --no-sleepset(or -nss)   let target run without sleepset                    \n"	    
			<< "  --replay <xx>        replay a trace file (e.g. trace.log.xml)              \n"
			<< "  --verbose (or -v)    set the verbosity level                               \n"
			<< "  --standalone         running in a stand-alone mode                         \n"
			<< "  --targetTrace        force target (program under test) to print dbg info   \n"
			<< "  --linCheck <x>       linearizability check: -1(disabled) 0(serial) 1(chk)  \n"
			<< "  --race-only(-ro)     only focus on data race detection                     \n"
			<< "  --deadlock-only(-do) only focus on deadlock detection                      \n"
			<< "  --color              display colored event                                 \n"
			<< "  --help (or -h)       display the help option                               \n"
			<< "                                                                             \n"
			<< "Please send bugs to yuyang@cs.utah.edu.                                      \n";
}

enum InspectBehavior {
	IB_NOREPLAY = 0, IB_REPLAY_WITH_DPOR = 1, IB_SPECIFIC_REPLAY = 2, IB_UNKNOWN
};

bool parsing_command_line(int argc, char* argv[]) {
	if (argc < 2) {
		print_usage();
		exit(0);
	}

	int pos = 1;
	char * arg, *arg1;
	while (pos < argc) {
		arg = argv[pos];

		if (strcmp(arg, "--standalone") == 0) {
			setting.standalone_flag = true;
			pos++;
		} else if (strcmp(arg, "--lazy") == 0) {
			setting.lazy_flag = true;
			pos++;
		} else if (strcmp(arg, "--color") == 0) {
                        set_config_log_approved_color(true);
			pos++;
		} else if (strcmp(arg, "--symm") == 0) {
			setting.symmetry_flag = true;
			pos++;
		} else if (strcmp(arg, "--race-only") == 0 || strcmp(arg, "-ro") == 0) {
			setting.race_only_flag = true;
			pos++;
		} else if (strcmp(arg, "--race") == 0) {
                        setting.report_race_flag = true;
			pos++;
		} else if (strcmp(arg, "--deadlock-only") == 0
				|| strcmp(arg, "-do") == 0) {
			setting.deadlock_only_flag = true;
			pos++;
		} else if (strcmp(arg, "--max-errors") == 0
				|| strcmp(arg, "-me") == 0) {
			pos++;
			if (pos == argc) {
				print_usage();
				exit(0);
			}
			if (isdigit(argv[pos][0])) {
				setting.max_errors = atoi(argv[pos]);
				pos++;
			}
		} else if (strcmp(arg, "--stateful") == 0 || strcmp(arg, "-s") == 0) {
			pos++;
			setting.stateful_flag = true;
		}
		
#ifdef NLZ_FLAG
		else if (strcmp(arg, "--no-dpor") == 0 || strcmp(arg, "-ndp") == 0) {
			pos++;
			setting.disable_dpor_flag = true;
		}

		else if (strcmp(arg, "--no-sleepset") == 0 || strcmp(arg, "-nss") == 0) {
			pos++;
			setting.disable_sleepset_flag = true;
		}

		else if (strcmp(arg, "--bound") == 0 || strcmp(arg,"-bo")==0) {
			pos++;
			arg1 = argv[pos];
			setting.max_bound = atoi(arg1);
			pos++;
                }
		//TSO and PSO command 
		else if (strcmp(arg, "--pso-mode") == 0 || strcmp(arg,"-pm")==0) {
			pos++;		
			setting.memory_model= PSO_MODEL;		
		}
		else if (strcmp(arg, "--tso-mode") == 0 || strcmp(arg,"-tm")==0) {
			pos++;		
			setting.memory_model= TSO_MODEL;		
		}
#endif
		
		else if (strcmp(arg, "--max-threads") == 0) {
			pos++;
			arg1 = argv[pos];
			setting.max_threads = atoi(arg1);
			pos++;
		}

		//-------------------------------- chao ----------------------------------
		else if (strcmp(arg, "--targetTrace") == 0) {
			setting.target_trace = true;
			set_config_target_trace_flag(true);
			pos++;
		} else if (strcmp(arg, "--linCheck") == 0) {
			pos++;
			setting.lin_check = atoi(argv[pos]);

			set_config_lin_check_flag(true);
			// when 'lin_check==0', it's serial execution
			set_config_lin_serial_flag(setting.lin_check == 0);

			if (setting.lin_check == 2) {
				pos++;

				set_quasi(atoi(argv[pos]));
				quasi_flag=true;  //used in everywhere else
                                set_config_lin_quasi_flag(quasi_flag);  //used in Schuler's copy of the "event_buffer.cc"
			}

			pos++;
		} else if (strcmp(arg, "--replay") == 0) {
			pos++;
			setting.replay_file = argv[pos];
			pos++;
		}

		else if (strcmp(arg, "--yices") == 0) {
			pos++;
			yices_path_computer_singleton::getInstance()->run_yices_replay =
					true;
			pos++;
		}

		else if (strcmp(arg, "--manual") == 0) {
			pos++;
			yices_path_computer_singleton::getInstance()->game_mode = true;
			pos++;
		}

		else if (strcmp(arg, "--max-runs") == 0) {
			pos++;
			arg1 = argv[pos];
			setting.max_runs = atoi(arg1);
			pos++;
                }
		else if (strcmp(arg, "--max-events") == 0) {
			pos++;
			arg1 = argv[pos];
			setting.max_events = atoi(arg1);
			pos++;
                }
		else if (strcmp(arg, "--max-spins") == 0) {
			pos++;
			arg1 = argv[pos];
			setting.max_spins = atoi(arg1);
			pos++;
		} else if (strcmp(arg, "--max-seconds") == 0) {
			pos++;
			arg1 = argv[pos];
			setting.max_seconds = atoi(arg1);
			pos++;
		} else if (strcmp(arg, "--max-pcb") == 0) {
			pos++;
			arg1 = argv[pos];
			setting.max_pcb = atoi(arg1);
			pos++;
		} else if (strcmp(arg, "--max-pset") == 0) {
			pos++;
			arg1 = argv[pos];
			setting.max_pset = atoi(arg1);
			pos++;
		}
		//-------------------------------- chao ----------------------------------

		else if (strcmp(arg, "--timeout") == 0) {
			pos++;
			arg1 = argv[pos];
			setting.timeout_val = atoi(arg1);
			pos++;
		} else if (strcmp(arg, "--help") == 0 || strcmp(arg, "-h") == 0) {
			print_usage();
			exit(0);
		} else if (strcmp(arg, "--verbose") == 0 || strcmp(arg, "-v") == 0) {
			pos++;
			if (pos == argc) {
				print_usage();
				exit(0);
			}
			if (isdigit(argv[pos][0])) {
				verboseLevel = atoi(argv[pos]);
				yices_path_computer_singleton::getInstance()->verbose =
						verboseLevel;

				pos++;
			}

		} else if (strncmp(arg, "-", 1) == 0) {
			cout << "Incorrect usage of Inspect: " << "argument: \'" << arg
					<< "\' is unknown.\n";
			print_usage();
			exit(0);
		} else
			break;
	}

	if (setting.standalone_flag)
		return true;

	setting.target_argc = argc - pos;
	setting.target_argv = &argv[pos];
	setting.target = argv[pos];
	return true;
}

void print_time(struct timeval * start_time, struct timeval * end_time) {
	int sec;
	int usec;

	sec = end_time->tv_sec - start_time->tv_sec;
	usec = end_time->tv_usec - start_time->tv_usec;

	if (usec < 0) {
		usec += 1000000;
		sec--;
	}

	cout << "Used time (seconds): " << sec << "." << usec << "\n";
}
SchedulerSetting setting1;
int main(int argc, char* argv[]) {
//
//  PolyGraph a;
//  a.test();

//	while(1){
//	int a;
//	cin >> a;
//	cout<<"a:" <<a<<endl;
//	}

	bool success_flag;
//	SchedulerSetting setting;
	struct timeval start_time, end_time;

	success_flag = parsing_command_line(argc, argv);
	if (!success_flag)
		return -1;

	if (yices_path_computer_singleton::getInstance()->game_mode) {
		cout << "game mode on! you can arrange the thread order as you like!"
				<< endl;
	}

	g_scheduler = new Scheduler();
	g_scheduler->init();

	gettimeofday(&start_time, NULL);
	g_scheduler->run();
	cout << "@@@CLAP: Done!" << endl; 
	gettimeofday(&end_time, NULL);

	print_time(&start_time, &end_time);

	delete g_scheduler;
	return 0;
}

/** \mainpage Inspect -- A Runtime Model Checker for Multithreaded C/C++ Programs
 *
 * \section intro_sec Introduction
 *
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Download the source 
 *  
 * 
 */

