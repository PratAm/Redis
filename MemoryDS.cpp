#include "MemoryDS.h"
#include<iostream>
#include "Storage.h"
#include "FileStorage.h"
#include <string>
#include <cassert>

bool MemoryDS::add(std::string &key, std::string &value)
{
	data[key] = value ;
	return true;
}

std::string MemoryDS::get(std::string &key)
{
	std::string result = "";

	if (data.count(key) > 0)
		result = data[key];

	return result;
}

void MemoryDS::registerStorage(FileStorage *storage)
{
	store = storage;
	store->f_write("testing ","memory");
}

void MemoryDS::persistData()
{
  std::map<std::string,std::string>::iterator it;
	assert(store->f_isopen() == true);
	if(store->f_isopen())
		std::cout << "file is open" <<std::endl;
	store->f_write("testing"," application");
  
	for(it = data.begin();it != data.end();++it)
	{
		std::string a,b;
		a = it->first;
		b = it->second;
		store->f_write(a,b);
	  MemoryDS::flush();
	}
}

void MemoryDS::loadDataFromStorage()
{
	std::string a, b;
  while(store->f_read(a,b))
	{
		    data[a] = b;
	}
}

void MemoryDS::flush()
{
	store->f_flush();
}
