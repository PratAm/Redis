
/*
	 File Name : SignalHandler.cpp
   Author    : Amar Pratap Singh
   Email    : amarpratap.knit@gmail.com
   Description:
	 Class implemention for handling of signals in application
*/

#include <iostream>
#include <cstdlib>
#include <csignal>
#include "SignalHandler.h"
#include "MemoryDS.h"

using namespace std;

extern MemoryDS database;

void registerSignal()
{
	signal(SIGINT,signalHandler);
}

void signalHandler( int signum )
{
	cout << "Interrupt signal (" << signum << ") received.\n";

	database.persistData();
	database.close();

  cout <<"saved data to Storage\n";

	exit(signum);  
}
