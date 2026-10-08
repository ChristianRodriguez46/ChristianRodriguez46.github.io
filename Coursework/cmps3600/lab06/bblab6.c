
/*
 *  echo.c
 *
 *  Demonstrate classic producer/consumer problem; the parent thread (the 
 *  producer) writes one character at a time from a file into a shared buffer
 *
 *  The buffer is shared because it is defined globally.
 *
 *  The consumer reads from buffer and writes it to a log file. With no 
 *  synchronization, the consumer will read the same character multiple times
 *  because the producer is slower than the consumer.
 *  Output is not deterministic - it varies across executions. 
 *
 *  This is a problem of concurrency. When two threads access shared resources 
 *  without synchronization, it's a race condition as to which thread gets 
 *  there first or next. Without synchronization, the consumer may read a value
 *  multiple times (empty buffer) or the producer overwrite a value before the 
 *  consumer had a chance to read it. 
 *
 *    $ gcc -o echo echo.c -lpthread   # link in POSIX pthread library  
 *    $ ./echo 
 */

#include <pthread.h>    //POSIX threads
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/sem.h>  // System-V semaphores
#include <sys/ipc.h>  //IPC keys
#include <sys/shm.h>  // Shared memory
#include <errno.h>
#include <sys/file.h>   /* `open()` system call -> write to log file*/

#define DEBUG 0 
#define PRODUCER 0 
#define CONSUMER 1 

union {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
} my_semun;

char pathname[200];
key_t ipckey;
int semid;

// struct sembuf grab[2], release[1];

/* thread function prototypes */
void *consumer(void *arg); 
void *producer(void *arg);
/* A note on the differences between forks and threads. Variables local to 
 * main that exist before the fork are inherited by the child but not shared.
 * Threads, since they are functions, can only see globals. These globals are
 * not only visible but shared by all threads since threads share user space.
 */

int retval;
int LIMIT = 50;  /* for testing read 6 chars from the file */
char buf[1];           /* 1 char buffer */
int fib(int);
FILE *fin;
FILE *fout;  /* needs to be global so threads can see it */

int main(int argc, char *argv[])
{
    if (argc > 1) {
        if  (atoi(argv[1]) > 136)
            LIMIT = 136;
        else
            LIMIT = atoi(argv[1]);
    }

    /*SEMPHORE SETUP START*/
	getcwd(pathname,200);
	strcat(pathname,"/foo");
	ipckey = ftok(pathname, 42);

	/* get a semaphore set with 1 semaphore in it (i.e., sem 0) */
	int nsem = 2;
	semid = semget(ipckey, nsem, 0666 | IPC_CREAT);
	if (semid < 0) {
		printf("Error - %s\n", strerror(errno));
		_exit(1);
	}

    /* you can set the semaphore to any positive number */
    // who has intial control (Producer)
	my_semun.val = PRODUCER;
	semctl(semid, 0, SETVAL, my_semun);
	my_semun.val = CONSUMER;
	semctl(semid, 1, SETVAL, my_semun);

    /*SEMPHORE SETUP END*/

    pthread_t ctid;  /* ctid is thread-ID for the consumer thread */
    pthread_t ptid;  /* ctid is thread-ID for the producer thread */
    // int dummy;

    /* We are using formatted fopen(2) to make life easier - normally
     * in systems coding you would use open(2)
	 * This is C Standard File I/O
     */
    fin = fopen("poem", "r");
    if (!fin) {
		//File pointer is NULL, error.
        fprintf(stderr, "error opening input file.\n");
        exit(1);
    }
    
    fout = fopen("log", "w");
    if (fout == NULL) {
        fprintf(stderr, "error opening output file.\n");
        exit(1);
    }

    /* create consumer thread */
    if (pthread_create(&ctid, NULL,  (void *)consumer, (void *)1) != 0)
        fprintf(stderr,"Error creating thread (Consumer)\n");
    
    /* create producer thread */
    if (pthread_create(&ptid, NULL,  (void *)producer, (void *)PRODUCER) != 0)
        fprintf(stderr,"Error creating thread (PRODUCER)\n");


    buf[0] = ' ';

    /* Get the thread-ID of main(). */
    pid_t tid = syscall(SYS_gettid);
    if (DEBUG)
        printf("main thread pid: %d tid: %d \n", getpid(), tid);

    /* the parent thread always joins with its spawned threads */
    if ((pthread_join(ptid, (void*)&retval)) < 0) {
        perror("pthread_join");
    } else {
        if (DEBUG)
            printf("joined parent thread w exit code: %d\n", retval);
    }

    /* the parent thread always joins with its spawned threads */
    if ((pthread_join(ctid, (void*)&retval)) < 0) {
        perror("pthread_join");
    } else {
        if (DEBUG)
            printf("joined consumer thread w exit code: %d\n", retval);
    }
    /* parent closes input file */
    fclose(fin);
    fclose(fout);
    semctl(semid, IPC_RMID, 0);
    exit(0);
}

/* CONSUMER thread function
 * reads data from shared buffer and writes to screen
 */
 void *consumer(void *arg)
 {
    struct sembuf grab[2], release[1];
    grab[0].sem_num = CONSUMER;
	grab[1].sem_num = CONSUMER;
	grab[0].sem_flg = SEM_UNDO;
	grab[1].sem_flg = SEM_UNDO;
	grab[0].sem_op = 0;
	grab[1].sem_op = 1;

	release[0].sem_num = PRODUCER;
	release[0].sem_flg = SEM_UNDO;
	release[0].sem_op = -1;

    int count = 0;
    pid_t tid = syscall(SYS_gettid);
    fprintf(fout, "consumer thread pid: %d tid: %d\n\n", getpid(), tid);
    while (1) {
        if (count == LIMIT)
            break;
        /* grab the semaphore*/
        semop(semid, grab, 2);

        /* critical section start */
        fputc(buf[0], fout);
        /* critical section end */

        /* release the semaphore now */
        semop(semid, release, 1);

        fib(14);   /* make consumer slightly faster than producer */
        count++;
    }
    fputc('\n', fout);
    pthread_exit(0);
}

void *producer(void *arg)
{
    struct sembuf grab[2], release[1];
    grab[0].sem_num = PRODUCER;
	grab[1].sem_num = PRODUCER;
	grab[0].sem_flg = SEM_UNDO;
	grab[1].sem_flg = SEM_UNDO;
	grab[0].sem_op = 0;
	grab[1].sem_op = 1;

	release[0].sem_num = CONSUMER;
	release[0].sem_flg = SEM_UNDO;
	release[0].sem_op = -1;

    /* PRODUCER
     * reads 1 char from poem file and writes that char to buffer */
    int count = 0;
    // pid_t tid = syscall(SYS_gettid);
    // fprintf(stdout, "producer thread pid: %d tid: %d \n", getpid(), tid);
    while (1) {
        if (count == LIMIT)
            break;
        /* grab the semaphore*/
        semop(semid, grab, 2);

        /* critical section start */
        buf[0] = fgetc(fin);
        /* critical section end */
        
        /* release the semaphore now */
        semop(semid, release, 1);

        if (DEBUG)
            putc(buf[0], stdout);
        fib(15);    /* make the producer slightly slower than consumer */
        count++;
    }
    pthread_exit(0);
}

int fib(int n)
{
    if (n == 1 || n == 2)
        return 1;
    return fib(n-1) + fib(n-2);
}


