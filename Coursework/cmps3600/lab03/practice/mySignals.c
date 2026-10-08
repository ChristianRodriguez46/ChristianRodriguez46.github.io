// Christian Rodriguez
// signal handling
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void myhandler (int sig)
{
    printf("myhandler recieved signal: %i\n", sig);
    if (sig == SIGCHLD)
        printf("SIGCHLD recieved!\n");
    
    printf("terminating program.\n");
    exit(0);
}

int main()
{
    pid_t pid = fork();
    if (pid == 0) {
        // child
        // while (true) {
        //     printf("signal handling ");
        //     fflush(stdout);
        //     usleep(10000);
        // }
        usleep(1000000);
    } else {
        signal(SIGCHLD, myhandler);
        usleep(2000000);
        // signal(SIGINT, myhandler);
    }
    printf("\n\n");
    return 0;
}