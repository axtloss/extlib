.POSIX:

CC = cc
CFLAGS = -g -fsanitize=address,undefined

test: FORCE
	$(CC) test.c ../src/extlib.c ../src/extstring.c ../src/constraint_handler.c ../src/memset_s.c $(CFLAGS) -o test
	./test

FORCE: ; # PHONY is a non standard extension
