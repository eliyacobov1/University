CC= $(CC)
CFLAGS= -Wvla -Wall

all: NumericalAnalyzer libinfi.a

#libinfi.a is a dependency for the executable
NumericalAnalyzer: NumericalAnalyzer.c infi.h infi.c
	gcc $(CFLAGS) infi.h infi.c NumericalAnalyzer.c -lm -o NumericalAnalyzer

#link library files into a static library
libinfi.a:  infi.c infi.h
	ar rcs libinfi.a infi.c infi.h

libs: libinfi.a

.PHONY: clean

clean:
	rm -f *.o *.a NumericalAnalyzer

