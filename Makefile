.POSIX:

CC = cc
CFLAGS = -g
PREFIX = /usr

TESTCFLAGS!=pkg-config --cflags extlib
TESTCFLAGS+=-g -fsanitize=undefined,address
TESTLDFLAGS!=pkg-config --libs extlib

extlib: extlib.o extstring.o
	$(CC) src/extlib.o src/extstring.o $(CFLAGS) -shared -fPIC -o libextlib.so

extlib.pc: extlib.pc.in
	sed 's|@prefix@|$(PREFIX)|g' extlib.pc.in > extlib.pc
	sed 's|@libdir@|$(PREFIX)/lib|g' extlib.pc > extlib.pc.tmp
	sed 's|@includedir@|$(PREFIX)/include|g' extlib.pc.tmp > extlib.pc
	rm extlib.pc.tmp

extlib.o:
	$(CC) src/extlib.c $(CFLAGS) -c -fPIC -o src/extlib.o

extstring.o:
	$(CC) src/extstring.c $(CFLAGS) -c -fPIC -o src/extstring.o

clean:
	rm -r src/extlib.o src/exststring.o libextlib.so extlib.pc test

install: extlib extlib.pc
	install -Dm655 libextlib.so $(PREFIX)/lib/
	install -Dm655 src/extlib.h $(PREFIX)/include/
	install -Dm655 extlib.pc $(PREFIX)/share/pkgconfig/

test:
	$(CC) $(TESTCFLAGS) $(TESTLDFLAGS) test.c -o test
	./test
