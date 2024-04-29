CXX = g++

INCDIR = include

# -g for debugging, -pg for profiling
CXXFLAGS = -g -std=c++20 -I$(INCDIR)


TARGET = test

SRCS += $(wildcard src/*.cpp)
SRCS += $(wildcard src/BitmapAllocator/*.cpp)
SRCS += $(wildcard tests/*.cpp)
SRCS += $(wildcard *.cpp) 


OBJS = $(SRCS:.cpp=.o)


RM = rm -f $(OBJS) $(TARGET)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM)