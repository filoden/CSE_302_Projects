# Makefile for Exam2ExCred

CXX := g++
CXXFLAGS := -std=c++11 -O2 -Wall -Wextra

SRCS := ASList.cpp AUList.cpp BST.cpp LLSList.cpp LLUList.cpp main.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := exam2excred

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
