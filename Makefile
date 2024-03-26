# Define the compiler
CXX = g++

# -g -pg 
CXXFLAGS =  -g -std=c++20


# Define the target executable name
TARGET = test

SRCS := $(wildcard *.cpp)
# Append .cpp files from subdirectories
SRCS += $(wildcard MemoryManager/*.cpp)
SRCS += $(wildcard MemoryManager/BitmapMemoryManager/*.cpp)
SRCS += $(wildcard tests/*.cpp)

# Define the object files (automatically generated from source files)
OBJS = $(SRCS:.cpp=.o)

ifeq ($(OS),Windows_NT)
    RM = rm -f $(OBJS) $(TARGET)
else
    RM = rm -f $(OBJS) $(TARGET)
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