# Makefile for examples week-11

all: lab11 maptest

maptest: maptest.c
	gcc maptest.c -Wall -omaptest -lpthread

lab11: bblab11.c
	gcc bblab11.c -Wall -lpthread -o lab11

clean:
	rm -f *.o lab11 maptest

