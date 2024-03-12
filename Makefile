# Define the compiler
CXX = g++

# Define C++ flags (feel free to customize)
CXXFLAGS = -g -Wall -std=c++17

# Define the target executable name
TARGET = test

# Define all source files
SRCS = test.cpp MemoryManager/BitmapMemoryManager/BitmapMemoryManager.cpp tests/test_out_of_bounds.cpp

# Define the object files (automatically generated from source files)
OBJS = $(SRCS:.cpp=.o)

ifeq ($(OS),Windows_NT)
    RM = del /Q /S *.o *.exe
else
    RM = $(OBJS) $(TARGET)
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each source file into an object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM)