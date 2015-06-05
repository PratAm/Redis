
#ifndef MEMORYDS__H
#define MEMORYDS__H

#include <string>
#include <map>
#include "Storage.h"
#include "FileStorage.h"

// In Memory Storage to storage non persistant data
class MemoryDS{
	public:
		
		MemoryDS(){
			store = NULL;
		}

		// add new entry to map data structure
		bool add(std::string &key, std::string &value);
		
		// get vale for a key
		std::string get(std::string &key);
		
		// dump all data present in map to storage
		void persistData();
		
		// read all data present in storage medium to map data sturcutre
		void loadDataFromStorage();
		
		// register the storage type with MemoryDS
		void registerStorage(Storage *store);
		
		// wrapper for closing the storage connection
		void close();
		
		// wrapper for flushing the data to storage class
		void flush();

	 private:
		Storage *store;
		std::map<std::string,std::string> data;
};

#endif
