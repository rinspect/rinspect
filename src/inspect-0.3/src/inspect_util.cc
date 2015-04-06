#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <arpa/inet.h>


#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "inspect_util.hh"
#include "inspect_exception.hh"

using namespace std;


////////////////////////////////////////////////////////////////////////
//
//  the implementation of Socket
//
//  current the supproted domains are:  AF_UNIX, AF_INET 
//
////////////////////////////////////////////////////////////////////////


Socket::Socket(enum SocketType type)
  : sock_type(type), 
    sock_fd(-1)
{
  switch( sock_type ){
  case SOCK_UNIX: init_af_unix(); break;
  case SOCK_INET: init_af_inet(); break;
  default: break;
  }
}


Socket::Socket(enum SocketType type, int fd)
  : sock_type(type), 
    sock_fd(fd)
{ }


Socket::~Socket()
{
  ::close(sock_fd);
}


void Socket::init_af_inet()
{
  int buflen = 0;

  sock_fd = socket(AF_INET, SOCK_STREAM, 0); 
  setsockopt(sock_fd, SOL_SOCKET, SO_SNDBUF, (const char*)&buflen, sizeof(buflen));
  setsockopt(sock_fd, SOL_SOCKET, SO_RCVBUF, (const char*)&buflen, sizeof(buflen));
  assert(sock_fd > 0);
}


void Socket::init_af_unix()
{
  int buflen = 0;

  sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  setsockopt(sock_fd, SOL_SOCKET, SO_SNDBUF, (const char*)&buflen, sizeof(buflen));
  setsockopt(sock_fd, SOL_SOCKET, SO_RCVBUF, (const char*)&buflen, sizeof(buflen));
  assert( sock_fd > 0 );
}


int Socket::connect(const char * file_name )
{
  struct sockaddr_un address;
  int retval;

  address.sun_family = AF_UNIX;
  strcpy(address.sun_path, file_name);  
 
  retval = ::connect(sock_fd, (struct sockaddr *)&address, sizeof(address));
  //if (retval == -1) throw SocketException("fail to connect");
  return retval;
}


int Socket::connect(const char* hostname, const int port)
{
  struct sockaddr_in pin;
  struct hostent * host;

  assert( sock_fd > 0 );
  host = gethostbyname(hostname);
  pin.sin_family = AF_INET;
  pin.sin_addr.s_addr = htonl(INADDR_ANY);
  pin.sin_addr.s_addr = ((struct in_addr*)(host->h_addr))->s_addr;
  pin.sin_port = htons(port);

  int retval ;
  retval = ::connect(sock_fd, (struct sockaddr*)&pin, sizeof(pin));
  if (retval == -1) throw SocketException("fail to connect");
  return retval; 
}


int Socket::send_int(const int val)
{
  unsigned int sval = htonl(val);
  int retval = ::send(sock_fd, (const char*)&sval, sizeof(sval), 0);

  if (retval == -1)  throw  SocketException("fail to send an integer");
  return retval;	
}


int Socket::recv_int(int * val)
{
  unsigned int buf;
  int retval = ::recv(sock_fd, (char*)&buf, sizeof(buf),0);  
  
  if (retval == -1) throw SocketException("fail to receive an interger");
  *val = ntohl(buf);
  return retval;
}


int Socket::send_double(const double val)
{
  int retval = ::send(sock_fd, (const char*)&val, sizeof(val), 0);
  if (retval == -1) throw SocketException("fail to send a double");
  return retval;
}

int Socket::recv_double(double* val)
{
  int retval = ::recv(sock_fd, (char*)val, sizeof(double), 0);
  if (retval == -1) throw SocketException("fail to receive a double");
  return retval;
}

void Socket::flush()
{
  fsync(sock_fd);
}


int Socket::send_string(string str)
{
  size_t len = str.length();
  int retval;
  retval = send_int(len);
  fsync(sock_fd);

  if (len > 0){
    retval = ::send(sock_fd, (const char*)str.c_str(), len, 0);
    if(retval == -1) throw SocketException("fail to send a string");
  }
  return retval;
}


int Socket::recv_string(string& str)
{
  char buf[10240];
  int len, retval;

  memset(buf, 0, sizeof(buf));

  retval = recv_int(&len);
  assert(retval != -1);
  
  if (len > 0){
    retval = ::recv(sock_fd, (char*)buf, len, 0);  
    if (retval == -1) throw SocketException("fail to receive a string");
    str = buf;
  }

  return retval;
}


int Socket::send_binary(const void* data, const int len)
{
  int retval; 
 
  retval = this->send_int(len);
  assert( retval != -1);

  retval = ::send(sock_fd, (const char*)data, len, 0);
  if (retval == -1) throw SocketException("fail to send binary");
  return retval;
}


int Socket::recv_binary(void * data)
{
  int retval, msglen;
  this->recv_int(&msglen);

  retval = ::recv(sock_fd, (char*)data, msglen, 0);
  if (retval == -1)  throw SocketException("fail to receive binary");
  return retval;
}


int Socket::close()
{
  return ::close(sock_fd);
}



Socket& Socket::operator <<(const int val)
{ 
  int retval; 
  retval = send_int(val);  
  return *this; 
} 


Socket& Socket::operator >>(int &val)
{ 
  int retval; 
  retval = recv_int(&val);
  return *this; 
} 



////////////////////////////////////////////////////////////////////////////
//
//     The implementation of ServerSocket
// 
////////////////////////////////////////////////////////////////////////////

ServerSocket::ServerSocket(enum SocketType type)
  : Socket(type), 
    timeout_val(0)
{ }


ServerSocket::~ServerSocket()
{
  this->close();
}


int ServerSocket::bind(const char * file_name)
{
  struct sockaddr_un server_address;
  int server_len, retval;

  unlink(file_name);

  assert( file_name != NULL );
  assert( strlen( file_name ) > 0 );
 
  server_address.sun_family = AF_UNIX;
  strcpy(server_address.sun_path, file_name);
  server_len = sizeof(server_address);
  retval = ::bind(sock_fd, (struct sockaddr *)&server_address, server_len);

  return retval;
}


int ServerSocket::bind(const unsigned int port)
{
  struct sockaddr_in  srvAddr;
  srvAddr.sin_family = AF_INET;
  srvAddr.sin_port = htons(port);
  srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  memset(&(srvAddr.sin_zero), 0, 8);
  
  int retval;
  retval = ::bind(sock_fd, (struct sockaddr*)&srvAddr, 
		  sizeof(struct sockaddr));
  return retval;
}

void ServerSocket::set_timeout_val(const unsigned int val)
{
  timeout_val = val;
}

int ServerSocket::listen(int backlog)
{
  return ::listen(sock_fd, backlog);
}


string  get_hostname_by_ip(string ip_addr)
{
  struct hostent * hent = NULL;
  long naddr = inet_addr(ip_addr.c_str());
  hent = gethostbyaddr((char*)&naddr, 4, AF_INET);
  return string(hent->h_name);
}


Socket* ServerSocket::accept()
{
  struct sockaddr_in clientAddr;
  socklen_t addrLen = sizeof(clientAddr);

  fd_set rfds;
  struct timeval tv;
  
  assert( sock_fd > 0 );

  FD_ZERO(&rfds);
  FD_SET(sock_fd, &rfds);

  tv.tv_sec = timeout_val;
  tv.tv_usec = 0;

  int retval = select(sock_fd + 1, &rfds, NULL, NULL, &tv);
  int newfd;
  Socket * newSock = NULL;
  
  if (retval == -1)
    perror("select()");
  else if (retval > 0){
    newfd = ::accept(sock_fd,(struct sockaddr*)&clientAddr, &addrLen);  
    newSock = new Socket(sock_type, newfd);

    if ( newSock->is_inet_socket() ){
      newSock->set_ip_addr( inet_ntoa(clientAddr.sin_addr) );
      newSock->set_port( ntohs(clientAddr.sin_port) );
      newSock->set_host_name( get_hostname_by_ip( newSock->get_ip_addr() ) );
    }
  }
  else{
    assert( retval == 0); 
    newSock = NULL;
  }
  return newSock;
}



Socket * ServerSocket::blocking_accept()
{
  struct sockaddr_in clientAddr;
  socklen_t addrLen = sizeof(clientAddr);
  int newfd;
  Socket * newSock  = NULL;

  newfd = ::accept(sock_fd,(struct sockaddr*)&clientAddr, &addrLen);  
  newSock = new Socket(sock_type, newfd);
  return newSock;  
}

////////////////////////////////////////////////////////////////////////////
//
//  the implementation of Mutex
//
////////////////////////////////////////////////////////////////////////////

Mutex::Mutex()
{
  int retval;

  retval = pthread_mutex_init(&mutex, NULL);
  assert(retval == 0);
}


Mutex::~Mutex()
{
  int retval;
  retval = pthread_mutex_destroy(&mutex);
}


int Mutex::lock()
{
  int retval;
  retval = pthread_mutex_lock(&mutex);
  return retval;
}


int Mutex::unlock()
{
  int retval;
  retval = pthread_mutex_unlock(&mutex);
  return retval;
}


int Mutex::trylock()
{
  return pthread_mutex_trylock(&mutex);
}


//////////////////////////////////////////////////////////////////////////

static void * thread_routine(void* arg) 
{
  Thread * thread_ptr = (Thread*)arg;
  thread_ptr->run();
  return NULL;
}



Thread::Thread() 
  : started(false), thread_id(0)
{ }


Thread::~Thread(){ }


void Thread::start() 
{
  int retval;
  if(started) throw ThreadException("Thread already started.");   

  retval = pthread_create(&thread_id, NULL, 
			  thread_routine, (void*)this);
  if( retval != 0) throw ThreadException( strerror(errno) );    
  started = true;
}
  

void Thread::join() 
{
  int retval;    
  retval = pthread_join(thread_id, NULL);
  if (retval != 0) throw ThreadException( strerror(errno) );    
}
  

void Thread::exit()
{
  pthread_exit(NULL);
}


void Thread::exit(void* retval)
{
  pthread_exit(retval);
}


bool Thread::isAlive() 
{ 
  return started; 
}
    

/////////////////////////////////////////////////////////////////////////////
//
//
//
/////////////////////////////////////////////////////////////////////////////

string  trim_whitespace(string & str)
{
    const char * cstr = str.c_str();
    int slen = str.length();
    int spos = 0, epos = slen - 1;
    
    while ( spos < slen && isblank(cstr[spos]) ) spos++;
    while ( epos > 0 && isblank(cstr[epos]) ) epos--;

    str.erase(epos+1, slen-1);
    str.erase(0, spos);
    
    return str;
}


vector<string> break_string_by_whitespace(string & str)
{
  string blank_char = " \t\b\v";

  vector<string> retval;
  unsigned long spos, epos, sbegin, send;
  string sub;
  
  spos = 0, epos = 0;

  trim_whitespace(str);
  sbegin = str.find_first_not_of(blank_char, spos);
  send = str.find_first_of(blank_char,sbegin);
  
  while (send != string::npos){
    sub = str.substr(sbegin, send  - sbegin);     
    retval.push_back(sub);

    sbegin = str.find_first_not_of(blank_char, send+1);
    send = str.find_first_of(blank_char, sbegin+1);
  }

  if (str.length() > 0){
    sub = str.substr(sbegin, str.length());
    retval.push_back(sub);  
  }
  return retval;
}


/**
 *   print the vector of a string line by line 
 * 
 */
void print_string_vector(ostream& os, vector<string>& strvec)
{
  copy(strvec.begin(), strvec.end(), ostream_iterator<string>(os, "\n"));
}

void print_int_vector(ostream& os, vector<int>& intvec)
{
  copy(intvec.begin(), intvec.end(), ostream_iterator<int>(os, " "));
}



/**  given an IP address in the unsigned integer form, 
 *   give out a string  in format xx.xx.xx.xx
 */

string  get_ip_addr_in_string(unsigned int val)
{
  char buf[32];
  memset(buf, 0, sizeof(buf));
  sprintf( buf, "%d.%d.%d.%d", val >>24,  (val & 0x00FF0000)>>16, 
	   (val & 0xFF00) >> 8, (val & 0xFF) );
  return string(buf);
}




bool is_absolute_path(const char * path)
{
  if (path == NULL) return false;
  return  path[0] == '/';
}


string  get_absolute_path(char * relative_path)
{
  string  abs_path;
  char buf[512];

  if ( relative_path[0] == '/') return string(relative_path);
  getcwd(buf, sizeof(buf));
  abs_path = buf + string("/");
  abs_path += string(relative_path);
  return abs_path;
}




char digit_to_char(int v)
{
  if (v >= 0 && v <= 9) return (char)(v + 0x30);
  switch(v){
  case 10: return 'A';
  case 11: return 'B';
  case 12: return 'C';
  case 13: return 'D';
  case 14: return 'E';
  case 15: return 'F';
  default: assert(false);
  }
  return ' ';
}
