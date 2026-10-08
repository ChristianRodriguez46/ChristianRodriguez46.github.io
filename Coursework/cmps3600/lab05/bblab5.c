/*
 * You may start with this program for lab-5
 *
 * __lab5.c
 *
 * This file uses shared memory. If you do not understand how shared memory 
 * works, review week-4 examples. Your job in lab-5 is to add a semaphore 
 * to control order. You know things have gone awry when you run the code:
 *  
 *    $ make lab5
 *    $ ./lab5
 *    child reads: 0
 *
 * The desired result is for the parent to compute fib(n), write the result to
 * shared memory then the child reads the result and displays it to the screen.
 * The problem is that things are out of order - by the time the parent computes
 * fib(10) the child has already read memory; i.e., the parent modifies the 
 * segment too late.
 * 
 * This scenario is a race condition. For example, if you pass a small enough 
 * number to fib, the child generally grabs the value OK:
 *
 *    $ ./lab5 10
 *    child reads: 55 
 *
 * but this may not work
 *
 *    $ ./lab5 18
 *    child reads: 0  <---- wrong results 
 *
 * To fix this problem you need to add a semaphore to control order. You want 
 * the parent to grab the semaphore first. Meanwhile the child is blocked on 
 * the semaphore. After the parent writes fib(n) to memory the parent releases 
 * the semaphore and the child can then grab it.
 * 
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/file.h>   /* `open()` system call -> write to log file*/

#define BUFSIZE 256
int status;
int fib(int);

union {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
} my_semun;

struct sembuf grab[2], release[1];
int sem_value;   /* the value of the semaphore */
int semid;


int main(int argc, char **argv)
{
    int n;
    char buf[BUFSIZE];
    pid_t cpid;
    int shmid; 
    int *shared;

    /* check if n was given on command-line */
    if (argc >= 2)
        n = atoi(argv[1]);
    else
        n = 25;

    /* IPC_PRIVATE will provide a unique key without using an ipckey 
     * it works with related processes but not unrelated ones - it is
     * a safe way to get a ipckey to use in a fork */
    shmid = shmget(IPC_PRIVATE, sizeof(int)*100, IPC_CREAT | 0666); // <- ipcKey
    /* attach and initialize memory segment */
    shared = (int *)shmat(shmid, (void *) 0, 0);
    *shared = 0;

    /* Just above we created some shared memory.  */
    /* Enough to hold 100 4-byte integers.        */

    /* get a semaphore set with 1 semaphore in it (i.e., sem 0) */
	int nsem = 1;

    semid = semget(shmid, nsem, 0666 | IPC_CREAT);
	if (semid < 0) {
		printf("Error - %s\n", strerror(errno));
		_exit(1);
	}

    /* setup the GRAB semaphore operation */
	/* apply an operation to semaphore 0 in the set */
	/* first, tell it which semaphore */ 
	grab[0].sem_num = 0;
	grab[1].sem_num = 0;
	/* next, let it release semaphore if holder dies */ 
	grab[0].sem_flg = SEM_UNDO;
	grab[1].sem_flg = SEM_UNDO;
	/* here are the 2 operations */
	/* wait until value is zero */
	grab[0].sem_op = 0;
	/* increment sem value by 1 */
	grab[1].sem_op = 1;

	/* setup RELEASE semaphore operation */
	/* apply the operation to semaphore 0 in the set */
	release[0].sem_num = 0;
	/* release semaphore if holder dies */ 
	release[0].sem_flg = SEM_UNDO;
	/* decrement semaphore by -1 to unlock it */
	/* Actually, we add -1 to the semaphore value,
	 * which is like a decrement. */
	release[0].sem_op = -1;

    my_semun.val = 0;
    semctl(semid, 0, SETVAL, my_semun);

    int logfd;
    
    /* open a log */
    logfd = open("log", O_WRONLY|O_CREAT|O_TRUNC, 0644);

    semop(semid, grab, 2);

    cpid = fork();

    if (cpid < 0) {
        printf("Error - fork command\n");
        fflush(stdout);
        exit(0);
    }

    if (cpid == 0) {
        /* CHILD */
        /* Attach to shared memory -
         * both child and parent must do this
         * but the parent can do it before the fork. See above. */
        shared = shmat(shmid, (void *)0, 0);

        /* child reads and displays shared memory */

        /* Critical section start */
        /* Now, perform the grab operation. */
    	/* 2 means perform 2 operations in the sembuf struct */
        semop(semid, grab, 2);

        int val = *shared;
        sprintf(buf, "child reads: %d\n", val);
        write(logfd, buf, strlen(buf));
        /* Critical section end */

        /* release the semaphore now */
        semop(semid, release, 1);

        shmdt(shared); /* detach from segment */
        semctl(semid, IPC_RMID, 0);
        exit(0);
    } else {
        /* PARENT */
        /* Parent computes fib(n) and writes it to shared memory */

        /* Critical section start */
        *shared = fib(n);
        /* Critical section end */
        semop(semid, release, 1);

        wait(&status); 

        shmdt(shared);              /* detach from segment   */
        shmctl(shmid, IPC_RMID, 0); /* remove shared segment */
        semctl(semid, IPC_RMID, 0);

    }
    return 0;
}

/* Some busy work for the parent */
int fib(int n)
{
    /* We will write this function in class together. */
    if (n ==1 || n == 2)
        return 1;
    return fib(n-1) + fib(n-2);
}



