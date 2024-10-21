.POSIX:

CC = cc
CFLAGS = -g -fsanitize=address,undefined
TESTS = $(wildcard test_*.c)

all: test

test: FORCE
	$(CC) -c tests.c -o tests.o $(CFLAGS)
	$(CC) driver.c tests.o ../src/extlib.c ../src/extstring.c ../src/constraint_handler.c ../src/memset_s.c $(CFLAGS) -o test
	./test
	rm tests.o

FORCE: ; # PHONY is a non standard extension
