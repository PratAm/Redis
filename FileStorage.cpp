#include "FileStorage.h"
#include <iostream>

int FileStorage::f_open()
{
  file.open(filename.c_str(), std::ios::in | std::ios::out | std::ios::app);
	return 1;
}

void FileStorage::f_close()
{
	file.close();
}

bool FileStorage::f_read(std::string &a, std::string &b)
{
  if( file >>a >>b)
	{
	  return true;
	}
	return false;
}

void FileStorage::f_write(std::string a, std::string b)
{
  file <<a <<" " <<b <<std::endl ;
}

void FileStorage::f_flush()
{
  file.flush();
}

bool FileStorage::f_isopen()
{
  return file.is_open();
}
