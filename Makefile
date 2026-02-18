# Makefile for the Uncertainty Calculator

CXX = g++

CXXFLAGS = -std=c++17 -Wall -I include

TARGET = uncertainty_calculator

SRCS = $(wildcard src/*.cpp)

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) -mconsole

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)