.POSIX:

CC = cc
CFLAGS = -g -fsanitize=address,undefined

test: FORCE
	$(CC) test.c ../src/extlib.c ../src/extstring.c $(CFLAGS) -o test
	./test

FORCE: ; # PHONY is a non standard extension
