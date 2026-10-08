all: mythread execve

execve: execve.c
	gcc execve.c -Wall -lX11 -o execve

mythread: mythreads.c
	gcc mythreads.c -Wall -lpthread -o mythread

clean:
	rm -f execve mythread a.out
