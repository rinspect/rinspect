#ifndef __INSPECT_EXCEPTION_H__
#define __INSPECT_EXCEPTION_H__


/**
 * 
 */
class BacktrackChoiceUnfoundException
{ };


/**
 *  will be thrown out by the scheduler when a deadlock is found!!
 */
class DeadlockException 
{ };

class DataraceException
{
public:
  DataraceException(char * reason) : detail(reason) { } 
public:
  string detail;
};

class IllegalLockException
{
public:
  IllegalLockException(char * reason) : detail(reason) { } 
public:
  string detail;
};

class AssertException 
{ };

class NullObjectException
{ };

class NullMutexException
{ };

class NullCondException
{ };


class SocketException
{
public:
  SocketException(const char * reason) : detail(reason) { } 

public:
  string detail;
};


#endif

