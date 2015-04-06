#ifndef _CODEBASE_INCLUDE_SOCKET_H_
#define _CODEBASE_INCLUDE_SOCKET_H_

#include <string>

#ifdef __GNUC__
  #include <sys/socket.h>
#else
  #include <winsock2.h>
#endif

#include <pthread.h>
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::ostream;


struct InternetAddress
{
  unsigned long address;
  unsigned short port;
};


enum SocketType{
  SOCK_UNIX = 0, 
  SOCK_INET,
  SOCK_UNKNOWN
};

/**
 *  the momain could be: 
 *    AF_UNIX
 *    AF_INET
 *    AF_INET6
 */
class Socket
{
public:
  Socket(enum SocketType type);
  Socket(enum SocketType type, int fd);
  virtual ~Socket();

  int get_fd() { return sock_fd; }

  int connect(const char* file_name);
  int connect(const char* hostname, const int port);
  
  int close();

  void attach();
  void detach();
  
  int send_int(const int val);
  int recv_int(int* val);

  int send_string(string str);
  int recv_string(string& str);
  
  int send_double(const double val);
  int recv_double(double *val);  

  int send_binary(const void* data, const int len);
  int recv_binary(void *data);

  void flush();

  Socket& operator <<(const int val);
  Socket& operator >>(int &val);
  
  Socket& operator <<(const double val) { send_double(val);  return *this; }
  Socket& operator >>(double &val)      { recv_double(&val); return *this; }
  
  Socket& operator <<(string str)       { send_string(str); return *this; } 
  Socket& operator >>(string &str)      { recv_string(str); return *this; } 

  bool is_unix_socket() { return SOCK_UNIX == sock_type; } 
  bool is_inet_socket() { return SOCK_INET == sock_type; } 

  void set_ip_addr(const char * str) { ip_addr = str; } 
  void set_port(const int num) { port = num; } 
  void set_host_name(const char *nm) { host_name = nm; } 
  void set_host_name(string nm) { host_name = nm; } 

  string get_ip_addr()   { return ip_addr;   }   
  int    get_port()      { return port;      }
  string get_host_name() { return host_name; } 

private:
  void init_af_inet();
  void init_af_unix();

public:
  enum SocketType sock_type;
  int sock_fd;
  string host_name;
  string ip_addr;
  int port; 
};


class ServerSocket : public Socket
{
public:
//   ServerSocket();
  ServerSocket(enum SocketType type);
  ServerSocket(int port);
//   ServerSocket(const char * file_name);
  virtual ~ServerSocket();
  int bind(string & file_name) { return this->bind(file_name.c_str()); }
  int bind(const char * file_name);
  int bind(const unsigned int port);
  int listen(int backlog);
  Socket* accept();
  Socket* blocking_accept();
  void set_timeout_val(const unsigned int val);

private:
  unsigned int timeout_val; //in seconds
};




class Mutex
{
public:
  Mutex();
  ~Mutex();

  int lock();
  int unlock();
  
  int trylock();

private:
  pthread_mutex_t  mutex;
};



string trim_whitespace(string& str);

vector<string> break_string_by_whitespace(string& str);

void print_string_vector(ostream& os, vector<string>& strvec);

string get_ip_addr_in_string(unsigned int val);


struct Runnable 
{
  virtual void  run() = 0;
  virtual ~Runnable() {}
};


class ThreadException 
{
public:
  ThreadException(const std::string &msg) { message = msg; }
  std::string message;
};


class Thread: public Runnable
{
public:
  Thread();
  ~Thread();

  void start();  
  void join();
  void exit();
  void exit(void* retval);

  bool isAlive();

protected:
  bool started;
  pthread_t thread_id;

};



string  get_absolute_path(char * relative_path);

bool is_absolute_path(const char * path);

char digit_to_char(int v);

#endif


