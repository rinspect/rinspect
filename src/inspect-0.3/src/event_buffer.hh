#ifndef __EVENT_BUFFER_H__
#define __EVENT_BUFFER_H__

#include "naling.def"
#ifdef NLZ_FLAG
class Scheduler;
//#include "scheduler.hh"
#endif

#ifdef NLZ_COMM
#include <queue>
#endif

#ifdef __GNUC__
#include <ext/hash_map>
using __gnu_cxx::hash_map;
using __gnu_cxx::hash;
#else
#include <hash_map>
#endif

#include <utility>
#include <string>
//#include <iostream>
//#include <iomanip>
//#include <sstream>
#include <fstream>

#include "inspect_util.hh"
#include "inspect_event.hh"
#include "program_state.hh"
#include "lin_checker.hh"

using namespace std;
using std::pair;
using std::string;


/**
 *  the socket index at the scheduler's side
 */
class SchedulerSocketIndex {
public:
	SchedulerSocketIndex();
	~SchedulerSocketIndex();

	typedef hash_map<int, Socket*, hash<int> >::iterator iterator;

	inline iterator begin() {
		return sockets.begin();
	}
	inline iterator end() {
		return sockets.end();
	}

	Socket * get_socket(int fd);
	Socket * get_socket_by_thread_id(int tid);
	Socket * get_socket(InspectEvent &);

	void add(Socket * socket);
	void update(int thread_id, Socket*);

	void remove(int fd);
	void remove_sc_fd(int fd);
	void remove(Socket * socket);
	void clear();

	bool has_fd(int fd);
public:
	hash_map<int, Socket*, hash<int> > sockets;
	hash_map<int, Socket*, hash<int> > tid2socket;
};

class EventBuffer {
public:
#ifdef NLZ_COMM
    typedef hash_map<int, std::vector<InspectEvent> >::iterator iterator;
#else
    typedef hash_map<int, InspectEvent>::iterator iterator;
#endif
    
public:
	EventBuffer();
	~EventBuffer();

	void update_output_folders();
	void output_serial();
	void output_concur();
	void output_normal();
	bool init(string socket_file, int time_out, int backlog);

	void reset();
	void close() {
		server_socket.close();
	}

	void collect_events();
	inline bool has_event(int tid);

	InspectEvent get_the_first_event();
	InspectEvent get_event(int tid);
	InspectEvent receive_event(Socket * socket);
	pair<int, int> set_read_fds();
	lin_checker* linChecker;

#ifdef NLZ_COMM
public:
    std::vector<InspectEvent> get_events(int tid);
#endif
    
    void approve(InspectEvent & event);

    inline bool is_listening_socket(int fd);

    string toString();

    bool filter_constructor(string event);
    vector<string> split_string(string input, string split_by);

public:
    ServerSocket server_socket;
    SchedulerSocketIndex socket_index;
    Socket * sc_socket; // the socket to connect with the state-capturing thread
    fd_set readfds;
#ifdef NLZ_COMM
    hash_map<int, std::vector<InspectEvent> > buffer;    
#else
    hash_map<int, InspectEvent> buffer;
#endif    
#ifdef RSS_EXTENSION
	//------------------chao, 4/7/2012-----------------
public:
	std::ofstream toEventLog;
	std::ofstream toEventLogXml;
	std::ofstream toEventLogJet;
	std::string logFileName;
	std::string logXmlFileName;
	std::string logJetFileName;
	void write_event_log(std::string str, InspectEvent &event);
	void write_event_log_xml(InspectEvent &event);
	void write_event_log_jet(InspectEvent &event);

	//------------------chao, 4/7/2012-----------------
#endif //RSS_EXTENSION



#ifdef NLZ_COMM
    hash_map<int, std::queue<InspectEvent> > permitted;
#endif
    
};

extern void set_config_echo_approved_event(bool val);
extern void set_config_log_approved_color(bool val);
extern void set_config_log_approved_event(bool val);
extern void set_config_target_trace_flag(bool val);
extern void set_config_lin_check_flag(bool val);
extern void set_config_lin_serial_flag(bool val);
extern void set_config_lin_quasi_flag(bool val);
extern bool get_config_lin_quasi_flag();
extern bool get_config_lin_serial_flag();
#endif

