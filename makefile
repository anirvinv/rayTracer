all: src/main.cpp
	g++ -o build/main src/main.cpp -std=gnu++17 -Wall -Wextra -pedantic -O2