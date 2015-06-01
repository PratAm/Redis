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
//	database.flush();

  cout <<"saved data to file\n";

	exit(signum);  
}
