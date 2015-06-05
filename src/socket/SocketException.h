
/*
	 File Name : SocketException.h
   Author    : Amar Pratap Singh
   Email    : amarpratap.knit@gmail.com
   Description:
	  interface for custom exception for socket
*/


#ifndef SocketException_class
#define SocketException_class

#include <string>

class SocketException
{
 public:
  SocketException ( std::string s ) : m_s ( s ) {};
  ~SocketException (){};

  std::string description() { return m_s; }

 private:

  std::string m_s;

};

#endif
