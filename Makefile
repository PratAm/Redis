
FLAGS= -g -Wall -Wextra -pedantic -Werror
GCC=g++ ${D} ${FLAGS}

TARGET = server
server_objects = ServerSocket.o Socket.o SignalHandler.o FileStorage.o MemoryDS.o ServerMain.o 

all : $(TARGET)

$(TARGET): $(server_objects)
	${GCC} -o $@ $^

%.o : %.cpp
	 ${GCC} -o $@ -c $<


# dependency for all .cpp files
Socket.o: Socket.h
ServerSocket.o: ServerSocket.h
SignalHandler.o: SignalHandler.h MemoryDS.h
FileStorage.o: FileStorage.h Storage.h
SocketException.o:SocketException.h
MemoryDS.o:MemoryDS.h Storage.h


clean:
	rm -f $(server_objects) $(TARGET)
