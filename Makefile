CC = gcc
CFLAGS = -g
PREFIX = /usr

extlib: extlib.o extstring.o
	$(CC) src/extlib.o src/extstring.o $(CFLAGS) -shared -fPIC -o libextlib.so

extlib.pc: extlib.pc.in
	sed 's|@prefix@|$(PREFIX)|g' extlib.pc.in > extlib.pc
	sed 's|@libdir@|$(PREFIX)/lib|g' extlib.pc > extlib.pc.tmp
	sed 's|@includedir@|$(PREFIX)/include|g' extlib.pc.tmp > extlib.pc
	rm extlib.pc.tmp

extlib.o:
	cc src/extlib.c $(CFLAGS) -c -fPIC -o src/extlib.o

extstring.o:
	cc src/extstring.c $(CFLAGS) -c -fPIC -o src/extstring.o

clean:
	rm -r src/extlib.o src/exststring.o libextlib.so extlib.pc test

install: extlib extlib.pc
	install -Dm655 -t $(PREFIX)/lib/ libextlib.so
	install -Dm655 -t $(PREFIX)/include/ src/extlib.h
	install -Dm655 -t $(PREFIX)/share/pkgconfig/ extlib.pc

test:
	$(CC)  -g -lextlib -I/usr/include/extlib -fsanitize=undefined,address test.c -o test
	./test
