/*
 * This program is here so that the Makefile will work.
 * You can start your lab with this program.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       /* to write time                 */
#include <sys/file.h>   /* open system call              */
#include <unistd.h>     /* header file for the POSIX API */
#include <sys/wait.h>   /* for wait system call          */

int fib(int n)
{
    if (n == 1 || n ==2)
        return 1;
    return fib(n-1) + fib(n-2);

}

int main(int argc, char *argv[])
{
    int status;
    pid_t cpid;
    int nTerm = 0;
    char buf[100];

    /* grab nsecs if passed */
    if (argc == 2) {
        nTerm = atoi(argv[1]);
    } else {
        printf("Usage: %s <n>\n", argv[0]);
        printf("    for 9th fibonacci, enter: %s 9\n", argv[0]);
        exit(1);
    }
    
    cpid = fork();
    
    if (cpid < 0) {
        printf("Error on fork().\n");
        exit(0);
    }
    if (cpid == 0) {
        // CHILD
        int logfd;

        /* open a log */
        logfd = open("log", O_WRONLY|O_CREAT|O_TRUNC, 0644);

        /* write info to child's log file */
        time_t timer;
        struct tm *tm_info;
        time(&timer);
        tm_info = localtime(&timer);
        
        strftime(buf, 26, "%Y:%m:%d %H:%M:%S\n", tm_info);
        write(logfd, buf, strlen(buf));

        /* write pids to log */
        int finAns = fib(nTerm);
        sprintf(buf, "fib sequence number %i = %i\n", nTerm, finAns); 
        write(logfd, buf, strlen(buf));
        
        close(logfd);
        exit(nTerm); 
    } else {
        // PARENT

        wait(&status);   /* wait for the child to die */
        if (WIFEXITED(status))
            sprintf(buf,"my child (%i) exited with code: %d\n", cpid, WEXITSTATUS(status));
        write(1, buf, strlen(buf));
        exit(0);
    }
    return 0;
}
