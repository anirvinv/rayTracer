CXX := g++
CXXFLAGS := -Werror -Wall -Wextra -pedantic -std=gnu++17

all: src/$(wildcard *.cpp)
	$(CXX) $(CXXFLAGS) -o build/clock src/clock.cpp
	$(CXX) $(CXXFLAGS) -o build/main src/main.cpp

test: tests/$(wildcard *.cpp)
	$(CXX) $(CXXFLAGS) -o build/test tests/test.cpp
	./build/test