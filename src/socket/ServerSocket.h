/*
	 File Name : ServerSocket.h
   Author    : Amar Pratap Singh
   Email    : amarpratap.knit@gmail.com
   Description:
	 Class giving interface for creation of server socket
*/

#ifndef ServerSocket_class
#define ServerSocket_class

#include "Socket.h"


class ServerSocket : private Socket
{
 public:

  ServerSocket ( int port );
  ServerSocket (){};
  virtual ~ServerSocket();

  const ServerSocket& operator << ( const std::string& ) const;
  const ServerSocket& operator >> ( std::string& ) const;

  void accept ( ServerSocket& );

};


#endif
