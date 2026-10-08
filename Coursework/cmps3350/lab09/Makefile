all: rand montecarlo lab9

rand: rand.cpp
	g++ rand.cpp -Wall -o rand

montecarlo: montecarlo.cpp
	g++ montecarlo.cpp -Wall -o montecarlo

lab9: vrlab9.cpp
	g++ vrlab9.cpp -Wall -std=c++11 -ansi -pedantic -o lab9

clean: 
	rm -f lab9 rand montecarlo