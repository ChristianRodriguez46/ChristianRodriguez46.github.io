// Christian Rodriguez
// Lab 4
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>   /* `open()` system call -> write to log file*/

int status;

int main()
{
    // Part 1
    /* create a variable of the required message structure type */
    int mqid;
    struct {
        long type;
        char text[100];
    } mymsg;

    char pathname[200];
    getcwd(pathname, 200);
    strcat(pathname, "/foo");

    // ipcs <- run command in terminal
    int ipckey = ftok(pathname, 25);    
    
    if (ipckey == -1) {
        perror("ipckey error: ");
        exit(EXIT_FAILURE);
    }

    // Shared memory ID
    int shmid;
    shmid = shmget(ipckey, sizeof(int)*2, IPC_CREAT | 0666);

    int *shared = shmat(shmid, (void *) 0, 0);

    // P <- gets input
    // C <- rev msg
    // mqid -> message Queue ID
    mqid = msgget(ipckey, IPC_CREAT | 0666);
    if (mqid < 0) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    int logfd;
    
    /* open a log */
    logfd = open("log", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    // End of Part 1

    pid_t pid = fork();
    if (pid == 0) {
        // CHILD
        int old = *shared;
        int received;

        while (old == *shared) {
            usleep(4250);  /* sleep for 4.25-thousandths of a second */
        }

        char buf[30];
        sprintf(buf, "%i\n", *shared);
        write(logfd, buf, sizeof(buf));
        /* received is -1 if there is a problem otherwise the number of bytes */
        received = msgrcv(mqid, &mymsg, sizeof(mymsg.text), 0, 0); /* blocks on queue */
        if (received > 0) {
            write(logfd, mymsg.text, sizeof(mymsg.text));
        }  

        close(logfd);   
        shmdt(shared);
        msgctl(mqid, IPC_RMID, NULL);
		exit(0);
    } else {
        // Parent
        char buf[100]; 
        memset(buf, 0, 100);
 

        write(1, "\nEnter a 2-digit number: ", 26);
        fgets(buf, sizeof(buf), stdin);
        int number = atoi(buf);
        memset(buf, 0, 100);

        *shared = number;

        write(1, "\nEnter a word: ", 15);
        fgets(buf, sizeof(buf), stdin);
                
        /* construct and send a message */
        memset(mymsg.text, 0, 100); /* clear out the space first */
        strcpy(mymsg.text, buf);
        mymsg.type = 1;
        msgsnd(mqid, &mymsg, sizeof(mymsg.text), 0);

        wait(&status);   /* wait for the child to die */
        printf("\nchild terminated with code %i\n", WEXITSTATUS(status));
    
        shmdt(shared);
		shmctl(shmid, IPC_RMID, 0);
    }
    printf("\n");


    return 0;
}