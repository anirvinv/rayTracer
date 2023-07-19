CC=g++
OUTDIR = ./build

all: src/main.cpp src/clock.cpp
	$(CC) -o $(OUTDIR)/main src/main.cpp -std=gnu++17 -Wall -Wextra -pedantic -O2
	$(CC) -o $(OUTDIR)/clock src/clock.cpp -std=gnu++17 -Wall -Wextra -pedantic -O2

test: tests/test.cpp
	g++ -o build/test tests/test.cpp -std=gnu++17 -Wall -Wextra -pedantic -O2
	./build/test
clean:
	rm -rf build/*
