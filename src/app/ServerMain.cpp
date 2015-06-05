
/*
	 File Name : ServerMain.cpp
   Author    : Amar Pratap Singh
   Email    : amarpratap.knit@gmail.com
   Description:
	 Main class implementing the logic of parsing the input recieved from telent 
	 and calling appropriate handler for handling GET/SET/SAVE inline commands
*/

#include "ServerSocket.h"
#include "SocketException.h"
#include "SignalHandler.h"
#include "FileStorage.h"
#include "MemoryDS.h"
#include <iostream>
#include <sstream>
#include <string>
#include <csignal>
#include <vector>

enum string_code {
	SET,
	GET,
	SAVE,
	INVALID
};

// convert inline command first token to enum value of GET/SET/SAVE
string_code hashit (std::string const& inString) {
	if (inString == "GET") return GET;
	if (inString == "SET") return SET;
	if (inString == "SAVE") return SAVE;
	return INVALID;
}

// Inmemory datastorage object
MemoryDS database;

int main ( int argc, char** argv )
{
	if(argc !=2)
		std::cout <<"Usage ./server <DbFilename>\n";

	FileStorage Db(static_cast<std::string>(argv[1]));

	// register the storage system
	database.registerStorage(&Db);

	// load the data from storage if any
	database.loadDataFromStorage();

	// register for signal handler
	registerSignal();

	try
	{
		std::cout << "Server starting on port 15000....\n";
		ServerSocket server ( 15000 );

		while ( true )
		{
			ServerSocket server_sock;
			server.accept ( server_sock );
			try
			{
				while ( true )
				{
					std::string input;
					server_sock >> input;

					std::string key,value;
					std::string result;

					// remove the last \r\n from input string
					input.erase(input.size()-2);

					// space for storing the tokens from input string
					std::vector<std::string> token;
					std::fill(token.begin(), token.end(), "");

					// Parse the input and tokenize it and store in vector for further use
					std::stringstream ss(input);
					std::string s;

					while (getline(ss, s, ' ')) {
						token.push_back(s);
					}

					// Parese rest of input based on first token {SET,GET,SAVE}  
					switch(hashit(token[0]))
					{
						case GET:
							if (2 != token.size())
								goto INVALID;

							key = token[1];
							result = database.get(key);

							// Return the result of GET query
							server_sock <<"$3\n";
							server_sock << result <<"\n";
							break;

						case SET:
							if (3 != token.size())
								goto INVALID;

							key = token[1];
							value = token[2];

							// Store the SET query in memory
							database.add(key,value);
							server_sock <<"+OK\n";

							break;

						case SAVE:
							if (1 != token.size())
								goto INVALID;
							database.persistData();
							server_sock <<"+OK\n";
							break;
INVALID:
						default:
							server_sock << "-INVALID\n";
							break;

					}
				}

			}
			catch ( SocketException& ) {}
		}
	}
	catch ( SocketException& e )
	{
		std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}


	return 0;
}
