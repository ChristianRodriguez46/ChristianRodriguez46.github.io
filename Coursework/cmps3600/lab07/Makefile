# makefile
# compile to an object file
# then link the object file with libraries needed

all: bblab7 lab7 mutex_test dotprod
# all: bblab7 mutex_test dotprod

bblab7: bblab7.c
	gcc bblab7.c -Wall -lpthread -o bblab7

# link the object files...
lab7: bblab7.o
	gcc bblab7.o -olab7 -lpthread -lm
mutex_test: mutex_test.o
	gcc mutex_test.o -omutex_test -lpthread -lm
dotprod: dotprod.o
	gcc dotprod.o -odotprod -lpthread -lm


#create the object files by compiling...
bblab7.o: bblab7.c
	gcc bblab7.c -c -Wall
mutex_test.o: mutex_test.c
	gcc mutex_test.c -c -DPOSIX_4D9 -Wall
dotprod.o: dotprod.c
	gcc dotprod.c -c -DPOSIX_4D9 -Wall

clean:
	rm -f bblab7
	rm -f *.o
	rm -f lab7
	rm -f dotprod mutex_test
	rm -f out

