all: lab1cpp lab1c xwin89

lab1cpp: lab1.cpp
	g++ lab1.cpp -Wall -o lab1cpp

lab1c: lab1.c
	gcc lab1.c -Wall -o lab1c

xwin89: xwin89.c
	gcc xwin89.c -Wall -lX11 -o xwin89

clean:
	rm -f lab1cpp
	rm -f lab1c
	rm -f xwin89