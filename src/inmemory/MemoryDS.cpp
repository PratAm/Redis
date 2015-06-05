
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

void MemoryDS::registerStorage(Storage *storage)
{
	store = storage;
}

void MemoryDS::persistData()
{
	store->f_open();
  
	std::map<std::string,std::string>::iterator it;
  
	for(it = data.begin();it != data.end();++it)
	{
		std::string a,b;
		a = it->first;
		b = it->second;
		store->f_write(a,b);
	}
	
	store->f_close();
}

void MemoryDS::loadDataFromStorage()
{
	store->f_open();
	
	std::string a, b;
  while(store->f_read(a,b))
	{
		    data[a] = b;
	}
	
	store->f_close();
}

void MemoryDS::flush()
{
	store->f_flush();
}

void MemoryDS::close()
{
	store->f_close();
}
