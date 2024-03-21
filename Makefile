# Define the compiler
CXX = g++

# Define C++ flags (feel free to customize)
CXXFLAGS = -g -pg  -std=c++20

# Define the target executable name
TARGET = test

# Define all source files
SRCS = test.cpp MemoryManager/MemoryManager.cpp MemoryManager/BitmapMemoryManager/BitmapMemoryManager.cpp tests/test_out_of_bounds.cpp tests/test_malloc.cpp tests/test_ref.cpp tests/test_compaction.cpp tests/test.cpp

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