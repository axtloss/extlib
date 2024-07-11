.POSIX:

CC = cc
CFLAGS = -g
PREFIX = /usr

TESTCFLAGS!=pkg-config --cflags extlib
TESTCFLAGS+=-g -fsanitize=undefined,address
TESTLDFLAGS!=pkg-config --libs extlib

extlib: extlib.o extstring.o constraint_handler.o memset_s.o
	$(CC) src/extlib.o src/extstring.o src/constraint_handler.o src/memset_s.o $(CFLAGS) -shared -fPIC -o libextlib.so

extlib.pc: extlib.pc.in
	sed 's|@prefix@|$(PREFIX)|g' extlib.pc.in > extlib.pc
	sed 's|@libdir@|$(PREFIX)/lib|g' extlib.pc > extlib.pc.tmp
	sed 's|@includedir@|$(PREFIX)/include|g' extlib.pc.tmp > extlib.pc
	rm extlib.pc.tmp

extlib.o:
	$(CC) src/extlib.c $(CFLAGS) -c -fPIC -o src/extlib.o

extstring.o:
	$(CC) src/extstring.c $(CFLAGS) -c -fPIC -o src/extstring.o

constraint_handler.o:
	$(CC) src/constraint_handler.c $(CFLAGS) -c -fPIC -o src/constraint_handler.o

memset_s.o:
	$(CC) src/memset_s.c $(CFLAGS) -c -fPIC -o src/memset_s.o

clean:
	rm -r src/extlib.o src/exststring.o libextlib.so extlib.pc test

install: extlib extlib.pc
	install -Dm655 libextlib.so $(PREFIX)/lib/
	install -Dm655 src/extlib.h $(PREFIX)/include/
	install -Dm655 extlib.pc $(PREFIX)/share/pkgconfig/

test: FORCE
	cd tests && make test

FORCE: ; # PHONY is a non standard extension
