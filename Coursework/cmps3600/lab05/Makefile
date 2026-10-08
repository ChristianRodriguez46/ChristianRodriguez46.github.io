# Makefile for week 5

all: bblab5 lab5 sem_ctrl sem_delete sem_get_info semtest

bblab5: bblab5.c
	gcc bblab5.c -Wall -o bblab5

lab5: lab.c
	gcc lab.c -Wall -olab5

sem_ctrl: sem_ctrl.c
	gcc sem_ctrl.c -Wall -o sem_ctrl

sem_delete: sem_delete.c
	gcc sem_delete.c -Wall -o sem_delete

sem_get_info: sem_get_info.c
	gcc sem_get_info.c -Wall -o sem_get_info

semtest: semtest.c
	#gcc semtest.c -Wall -D_GNU_SOURCE -ansi -pedantic -o semtest
	gcc semtest.c -Wall -o semtest

clean:
	rm -f bblab5 lab5 sem_ctrl sem_delete sem_get_info semtest

