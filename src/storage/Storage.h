
/*
	 File Name : Storage.h
   Author    : Amar Pratap Singh
   Email    : amarpratap.knit@gmail.com
   Description:
	 This is the abstract class which act as a contract for all the classes
	 which will support different types of storage medium.
*/

#ifndef STORAGE__H
#define STORAGE__H

#include <cstring>
#include <fstream>

/*
	 Inherit the class for different storage mechanism like
	 storing to file,database or any other persisitent system.
	 Impliment all the virtual funtion also as this interface is 
	 used at other class .
*/
class Storage
{
	public:
		
		Storage(){}
		
		// opening the connection to storage
		virtual int f_open() =0;
		
		// closing the connection to storage
		virtual void f_close()=0;
		
		// reading from the storage in memory
		virtual bool f_read(std::string &key,std::string &val)=0;
		
		// writing content to the storage
		virtual void f_write(std::string key,std::string val)=0;
		
		// flushing the contect on file
		virtual void f_flush()=0;
		
		// checking if the storage connection is open
		virtual bool f_isopen()=0;
};

#endif
