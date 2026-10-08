all: original lab3

original: 
	gcc lab3-ssl.c -Wall -lssl -lcrypto -o original

lab3:
	g++ lab3-ssl.cpp -Wall -lssl -lcrypto -o lab3
clean:
	rm -f original
	rm -f lab3