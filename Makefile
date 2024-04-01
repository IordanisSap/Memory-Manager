# Define the compiler
CXX = g++

INCDIR = include

# -g -pg 
CXXFLAGS =  -g -std=c++20 -I$(INCDIR)


# Define the target executable name
TARGET = test

# Append .cpp files from subdirectories
SRCS += $(wildcard src/*.cpp)
SRCS += $(wildcard src/BitmapMemoryManager/*.cpp)
SRCS += $(wildcard tests/*.cpp)
SRCS += $(wildcard *.cpp) 


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