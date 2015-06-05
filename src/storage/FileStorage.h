
/*
	 File Name : FileStorage.h
   Author    : Amar Pratap Singh
   Email    : amarpratap.knit@gmail.com
   Description:
	 Class giving interface for storage of data on file
*/

#ifndef FileAccess__H
#define FileAccess__H

#include <cstring>
#include <fstream>
#include "Storage.h"

class FileStorage:public Storage
{
	public:
		explicit FileStorage(std::string str):
			filename(str){}
	
		~FileStorage()
		{
			file.close();
		}
		
		int f_open();
		void f_close();
		bool f_read(std::string &a, std::string &b);
		void f_write(std::string a, std::string b);
		void f_flush();
		bool f_isopen();
	
	private:
    FileStorage(FileStorage& a);
		void operator=(FileStorage &a);

		std::string filename;
		std::fstream file;
};

#endif
