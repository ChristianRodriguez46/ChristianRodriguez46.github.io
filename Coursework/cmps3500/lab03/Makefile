all: lab03 lab03_dogs

lab03: testada.adb
	gcc -c testada.adb && gnatbind testada && gnatlink testada

lab03_dogs: dogspa.adb
	gcc -c dogspa.adb && gnatbind dogspa && gnatlink dogspa
clean: 
	rm -f testada.ali testada.o testada
	rm -f dogspa.ali dogspa.o dogspa
