// Christian Rodriguez
// Lab 3

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>   /* for wait system call          */

int logfd;

void myhandler(int sig)
{
	/* signal handler */
    write(logfd, " (got the signal) ", 18);
}

int main() 
{
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, NULL);
    
    int ret;
    
    /* sa is a variable name for a sigaction structure */
	struct sigaction sa; 
	sa.sa_handler = myhandler; /* point it at your handler function */
	sigfillset(&sa.sa_mask);
	sa.sa_flags = 0;
    
    ret = sigaction(SIGTERM, &sa, NULL);
	ret = sigaction(SIGUSR1, &sa, NULL);
	if (ret == -1) {
        perror("sigaction");
		exit(1); 
	}   
    
    pid_t pid = fork();
    if (pid == 0) {
        logfd = open("log", O_WRONLY|O_CREAT|O_TRUNC, 0644);

        write(logfd, "Hard work at CSUB", 17);   // line 1 
        
        sigdelset(&mask, SIGUSR1);
        sigsuspend(&mask);                       // line 2
        // HANDLER
        write(logfd, "pays off!\n", 11);         // line 3
        close(logfd);                            // line 4
        exit(0);  
    } else {
        kill(pid, SIGTERM);
        kill(pid, SIGUSR1);
        
        int status = 0;
        wait(&status);   /* wait for the child to die */
        printf("child terminated with code %i", WEXITSTATUS(status));
    }
    printf("\n");
    return 0;
}
