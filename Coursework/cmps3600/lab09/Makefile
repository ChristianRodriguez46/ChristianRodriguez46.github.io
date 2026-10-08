all: bblab9 friday procstat bbphase3

bblab9: bblab9.c
	gcc -o bblab9 bblab9.c -Wall -lX11 -lXext -lpthread

friday: friday.c
	gcc -o friday friday.c -Wall -lX11 -lXext -lpthread

procstat: procstat.c
	gcc -o procstat procstat.c -Wall -lX11

bbphase3: bbphase3.c
	gcc -o bbphase3 bbphase3.c -Wall -lX11

clean:
	rm -f bblab9 friday procstat bbphase3