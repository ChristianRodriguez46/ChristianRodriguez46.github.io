/* Christian Rodriguez */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd[2];
    int ret = pipe(fd);
    (void)ret;
    printf("pipe fd: %i %i\n", fd[0], fd[1]);
    
    pid_t pid = fork();
    if (pid == 0) {
        /* child */
        close(fd[1]);
        char str[100];
        read(fd[0], str, 100);
        printf("child reads: %s\n", str);
        
        exit(0);
    } else {
        /* parent */
        sleep(5);
        write(fd[1], "hello", 5);
        close(fd[0]);
        close(fd[1]);
    }

    printf("program ending\n");
    fflush(stdout);
    return 0;
}