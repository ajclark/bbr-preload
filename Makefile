CC=gcc
CFLAGS=-fPIC -ansi -pedantic -Wall
LDFLAGS=-shared -Wl,-soname,libbbr.so
LDLIBS=-ldl

default: libbbr.so

%.so: %.o
	$(CC) $(LDFLAGS) -o $@ $< $(LDLIBS)

clean:
	rm -f *.so *.o
