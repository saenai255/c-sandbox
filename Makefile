CC = zig cc
CC_FLAGS = -O2 -Wall -Wextra -Wpedantic

bin/test: build/test.o
	mkdir -p bin
	$(CC) build/test.o $(CC_FLAGS) -o bin/test

build/test.o: test.c
	mkdir -p build
	$(CC) $(CC_FLAGS) -c test.c -o build/test.o

.PHONY: clean

clean:
	rm -r build bin