# Makefile for SnowRemovalSim

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -I/opt/homebrew/Cellar/sfml/2.6.1/include

# SFML library flags
SFML_LIB_PATH = /opt/homebrew/Cellar/sfml/2.6.1/lib
SFML_FLAGS = -L$(SFML_LIB_PATH) -lsfml-graphics -lsfml-window -lsfml-system

# Source and output directories
SRC_DIR = src
BIN_DIR = bin

# Target executable
TARGET = $(BIN_DIR)/SnowRemovalSim

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_FLAGS)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BIN_DIR) $(OBJS)

.PHONY: all clean
