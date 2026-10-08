//Author: Christian Rodriguez
// 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int status;

int main(void)
{
    printf("Parent process is starting.\n");
    pid_t pid = fork();
    if (pid < 0) {
        printf("Error on fork().\n");
        exit(0);
    }
    if (pid == 0){
        // child
        printf("Child process is staring.\n");
        sleep(10);
        printf("Child process is ending.\n");
        exit(14);
    }
    else{
        //parent
        printf("My child's pid: %i\n", pid);
        wait(&status);
        if (WIFEXITED(status))
            printf("child exit code: %i\n", WEXITSTATUS(status));
        printf("Parent process is ending.\n");
    }
    return 0;
}
