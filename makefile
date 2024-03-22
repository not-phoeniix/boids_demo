# compiler and flags
CXX := g++
PRE_FLAGS := -m64 -g -Wall
POST_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system

# directories
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := $(BIN_DIR)/obj
LIB_DIR := include

# files
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(subst .cpp,.o,$(SRC)))
BIN := $(BIN_DIR)/build

# build tasks
all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) $(POST_FLAGS) -o $(BIN)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR) $(OBJ_DIR)
	$(CXX) -c $< $(PRE_FLAGS) -I $(LIB_DIR) -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# other tasks
.PHONY: clean run setup
clean:
	rm -f $(BIN) $(OBJ)
	echo "project cleaned!"

run: $(BIN)
	exec $(BIN)

# make dirs and create main file
setup:
	mkdir -p $(SRC_DIR) $(BIN_DIR) $(OBJ_DIR) $(LIB_DIR)
	echo "#include <iostream>" >> $(SRC_DIR)/main.cpp
	echo "" >> $(SRC_DIR)/main.cpp
	echo "int main() {" >> $(SRC_DIR)/main.cpp
	echo "	std::cout << \"hello world!!\n\";">> $(SRC_DIR)/main.cpp
	echo "" >> $(SRC_DIR)/main.cpp
	echo "	return 0;" >> $(SRC_DIR)/main.cpp
	echo "}" >> $(SRC_DIR)/main.cpp

	echo "set up project!!"
