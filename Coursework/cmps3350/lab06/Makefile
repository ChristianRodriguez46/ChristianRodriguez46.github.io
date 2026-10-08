all: waterlab6 test

waterlab6: waterlab6.cpp
	g++ waterlab6.cpp libggfonts.a -Wall -lX11 -lGL -lGLU -lm -o waterlab6
test: test.cpp
	g++ test.cpp libggfonts.a -Wall -lX11 -lGL -lGLU -lm -o test

clean:
	rm -f waterlab6 test