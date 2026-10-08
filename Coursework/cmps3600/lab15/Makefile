all: myxwindow bbphase2 bbphase3 bbphase4

myxwindow: myxwindow.c
	gcc myxwindow.c -Wall -lX11 -o myxwindow

bbphase2: bbphase2.c
	gcc bbphase2.c -Wall -lX11 -o bbphase2

bbphase3: bbphase3.c
	gcc bbphase3.c -Wall -lX11 -o bbphase3

bbphase4: bbphase4.c
	gcc bbphase4.c -Wall -lX11 -lXext -lpthread -o bbphase4

clean: 
	rm -f myxwindow bbphase2 bbphase3 bbphase4