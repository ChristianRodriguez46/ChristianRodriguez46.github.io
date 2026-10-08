all: testing utest dslab5 ulab5 wlab5
testing: testing.cpp
	g++ testing.cpp -Wall -o testing

utest: testing.cpp
	g++ testing.cpp -Wall -o utest -D UNIT_TEST

dslab5: dslab5.cpp
	g++ dslab5.cpp -Wall -o dslab5

ulab5: dslab5.cpp
	g++ dslab5.cpp -Wall -o ulab5 -D UNIT_TEST

wlab5: dslab5.cpp
	g++ dslab5.cpp -Wall -o wlab5 -D WHO_TEST

clean:
	rm -f testing utest dslab5 ulab5 wlab5