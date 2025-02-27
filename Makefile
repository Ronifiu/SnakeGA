# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude  # Include header directory

# Raylib paths (modify if needed)
RAYLIB_DIR = /usr/local/lib
RAYLIB_INCLUDE = /usr/local/include
RAYLIB_FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Source and Object files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# Executable name
TARGET = $(BIN_DIR)/snake_game

# Create necessary directories
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Build rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) -L$(RAYLIB_DIR) $(RAYLIB_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/*.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(RAYLIB_INCLUDE)

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the game
run: all
	./$(TARGET)
