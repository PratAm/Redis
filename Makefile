
FLAGS     := -Wall -Wextra -pedantic -Werror
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
	$(CC) $(FLAGS) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all checkdirs clean

all: checkdirs build/server

build/server: $(OBJ)
	@echo building server
	$(LD) $^ -o $@


checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@echo cleaning files
	@rm -rf $(BUILD_DIR)
	@rm build/server

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))
