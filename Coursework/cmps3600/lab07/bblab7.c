#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> /* rand(3c) */
#include <string.h> /* For strerror(3c) */
#include <errno.h>  /* For errno */
/* SEMAPHORES*/
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

//#include <semaphore.h>  // POSIX semaphores

int eat[5] = {0,0,0,0,0}, max_eats = 5, delay = 10, done = 0;

/*
    REFACTOR POSIX TO SYSTEM-V
        sem_t sem[5];
*/
/* START OF SEMAPHORES*/

union {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
} my_semun;

char pathname[200];
key_t ipckey;
int semid;

/* END OF SEMAPHORES*/

pthread_mutex_t monitor;
int fib(int n);

void *philosopher(void *arg) {
    struct sembuf grab[2][2], release[2][1];
    int me = (int)(long)arg;
    // printf("thread %i\n", me);
    // Setting a hierarchy system
    int forknum[2] = { me, (me+1)%5 };
    if (forknum[0] > forknum[1]) {
        int tmp = forknum[0];
        forknum[0] = forknum[1];
        forknum[1] = tmp;
    }

    for (int i =0; i <2; i++) {
        grab[i][0].sem_num = forknum[i];
        grab[i][1].sem_num = forknum[i];
        grab[i][0].sem_flg = SEM_UNDO;
        grab[i][1].sem_flg = SEM_UNDO;
        grab[i][0].sem_op = 0;
        grab[i][1].sem_op = 1;
    
        release[i][0].sem_num = forknum[i];
        release[i][0].sem_flg = SEM_UNDO;
        release[i][0].sem_op = -1;
    }

    while (!done) {
        // think
        // grab 2 forks
        fib(delay);
        pthread_mutex_lock(&monitor);
        semop(semid, grab[0], 2);
        semop(semid, grab[1], 2);
        pthread_mutex_unlock(&monitor);
        // eat
        ++eat[me];
        printf("%i eating %i %i %i %i %i\n", me, eat[0], eat[1], eat[2], eat[3], eat[4]);

        
        semop(semid, release[0], 1);
        semop(semid, release[1], 1);
        
        if (eat[me] > max_eats)
            done = 1;
        // rest

    }

    return (void *)0;
}

int main(int argc, char *argv[]) {
    int i;
    void *status[5];

    if (argc > 1)
        max_eats = atoi(argv[1]);
    if (argc > 2)
        delay = atoi(argv[2]);
    /*
    if (argc > 3) 
         max_eaters = atoi(argv[3]);
    */ 



    //SEMPAHORES
    getcwd(pathname,200);
	strcat(pathname,"/foo");
	ipckey = ftok(pathname, 42);

    int nsem = 5;
	semid = semget(ipckey, nsem, 0666 | IPC_CREAT);
	if (semid < 0) {
		printf("Error - %s\n", strerror(errno));
		_exit(1);
	}


    my_semun.val = 0;
    for (i=0; i<5; i++)
        semctl(semid, i, SETVAL, my_semun);

    // NULL means it is unlocked(someone is allowed to get)
    pthread_mutex_init(&monitor, NULL);
    // Hone many threads: five threads
    pthread_t tid[5];
    for (i=0; i<5; i++)
        pthread_create(&tid[i], NULL, philosopher, (void *)(long)i);
    for (i=0; i<5; i++)
        pthread_join(tid[i],&status[i]);

    pthread_mutex_destroy(&monitor);
    semctl(semid, IPC_RMID, 0);
    return 0;
}

int fib(int n)
{
    if (n == 1 || n == 2)
        return 1;
    return fib(n-1) + fib(n-2);
}