# Makefile for examples week-10

all: bblab10 mypipes pipetest dotprod pgflt_test cache_check test rlimit

bblab10:bblab10.c
	gcc bblab10.c -Wall -lpthread -ansi -pedantic -o bblab10

mypipes: mypipes.c
	gcc mypipes.c -Wall -omypipes
	
pipetest: pipetest.c
	gcc pipetest.c -Wall -opipetest -lpthread

dotprod: dotprod.c
	gcc dotprod.c -Wall -odotprod -lpthread

pgflt_test: pgflt_test.c
	gcc pgflt_test.c -Wall -opgflt_test

cache_check: cache_check.c
	gcc cache_check.c -Wall -ocache_check

test: test.c
	gcc test.c -Wall -otest

rlimit: rlimit.c
	gcc rlimit.c -Wall -orlimit

clean:
	rm -f mypipes
	rm -f *.o pipetest dotprod pgflt_test cache_check
	rm -f test rlimit a.out

