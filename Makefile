# CXX		  := g++
# CXX_FLAGS := -Wall -Wextra -std=c++17 -g

# BIN		:= bin
# SRC		:= src
# INCLUDE	:= include
# LIB		:= lib

# LIBRARIES	:= -lraylib
# EXECUTABLE	:= main


# all: $(BIN)/$(EXECUTABLE)

# run: clean all
# 	./$(BIN)/$(EXECUTABLE)

# $(BIN)/$(EXECUTABLE): $(SRC)/main.cpp $(SRC)/levels/Environment.cpp
# 	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

# clean:
# 	-rm $(BIN)/*
CXX = g++
# CXX_FLAGS = -Wall -Wextra -std=c++17 -g
CXX_FLAGS = -std=c++17 -g

BIN = bin
SRC = src
INCLUDE = include
LIB = lib

LIBRARIES = -lraylib
EXECUTABLE = main

# Find all .cpp files in the src directory and its subdirectories
SOURCES = $(shell find $(SRC) -name '*.cpp')

# Generate object files for each source file
OBJECTS = $(patsubst $(SRC)/%.cpp, $(BIN)/%.o, $(SOURCES))


all: $(BIN)/$(EXECUTABLE)

run: clean all
	./$(BIN)/$(EXECUTABLE)

# Link the object files to create the final executable
$(BIN)/$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

# Compile each source file into an object file
$(BIN)/%.o: $(SRC)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	-rm -rf $(BIN)/*