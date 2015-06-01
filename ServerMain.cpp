#include "ServerSocket.h"
#include "SocketException.h"
#include "SignalHandler.h"
#include "FileStorage.h"
#include "MemoryDS.h"
#include <iostream>
#include <string>
#include <csignal>
#include <vector>

enum string_code {
	SET,
	GET,
	SAVE,
	INVALID
};

string_code hashit (std::string const& inString) {
	if (inString == "GET") return GET;
	if (inString == "SET") return SET;
  if (inString == "SAVE") return SAVE;
	return INVALID;
}
	
MemoryDS database;

int main ( int argc, char** argv )
{
	if(argc !=2)
		std::cout <<"Usage ./server <DbFilename>\n";

	FileStorage *Db = new FileStorage(static_cast<std::string>(argv[1]));
	
	// register the storage system
	database.registerStorage(Db);

	// load the data from storage if any
	database.loadDataFromStorage();

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
					std::string input, input1;
					server_sock >> input;
					server_sock << input;

					std::string delimiter = " ";
					size_t pos = 0;
					std::string key,value;
					std::string token,result;
					std::vector<std::string> inp;

					if ((pos = input.find(delimiter)) != std::string::npos) 
					{
						token = input.substr(0, pos);
						inp.push_back(token);
						std::cout << token << std::endl;
					  input.erase(0,pos+1);

						int i =0;
						switch(hashit(token))
						{
							case GET:
								while(input[i] != '\r') i++;
								
								key = input.substr(0,i);
								std::cout << key <<std::endl;
								result = database.get(key);
								server_sock <<"$3\n";
								server_sock << result <<"\n";
                break;
							 
							case SET:
								if ((pos = input.find(delimiter)) != std::string::npos)
								{
									key = input.substr(0,pos);
									std::cout << key <<std::endl;
									input.erase(0, pos + 1);
								}
								i =0;
								while(input[i] != '\r') i++;

								value = input.substr(0,i);
								std::cout << value <<std::endl;
								database.add(key,value);
								server_sock <<"+OK\n";
								break;
								
							case SAVE:
								database.persistData();
								break;

							default:
								server_sock << "-INVALID\n";
								break;
								
						}
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
