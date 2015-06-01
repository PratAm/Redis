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

		std::map<std::string,std::string> data;
		bool add(std::string &key, std::string &value);
		std::string get(std::string &key);
		void persistData();
		void loadDataFromStorage();
		void registerStorage(Storage *store);
		void close();
		void flush();

	 private:
		Storage *store;
};

#endif
