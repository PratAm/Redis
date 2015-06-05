
#FLAGS= -g -Wall -Wextra -pedantic -Werror
#GCC=g++ ${D} ${FLAGS}
#
#TARGET = server
#server_objects = ServerSocket.o Socket.o SignalHandler.o FileStorage.o MemoryDS.o ServerMain.o 
#
#all : $(TARGET)
#
#$(TARGET): $(server_objects)
#	${GCC} -o $@ $^
#
#%.o : %.cpp
#	 ${GCC} -o $@ -c $<
#
#
## dependency for all .cpp files
#ServerMain.o:FileStorage.h MemoryDS.h
#Socket.o: Socket.h
#ServerSocket.o: ServerSocket.h
#SignalHandler.o: SignalHandler.h MemoryDS.h
#FileStorage.o: FileStorage.h Storage.h
#SocketException.o:SocketException.h
#MemoryDS.o:MemoryDS.h Storage.h
#
#
#clean:
#	rm -f $(server_objects) $(TARGET)

FLAGS= -g -Wall -Wextra -pedantic -Werror
CC        := g++
LD        := g++

MODULES   := storage signals socket inmemory app
SRC_DIR   := $(addprefix src/,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst src/%.cpp,build/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(CC) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all checkdirs clean

all: checkdirs build/server

build/server: $(OBJ)
	echo building server
	$(LD) $^ -o $@


checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	echo cleaning files
	@rm -rf $(BUILD_DIR)
	@rm -rf build

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))
