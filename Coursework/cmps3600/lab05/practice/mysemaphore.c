// Christian Rodriguez
// POSIX semaphores
// Named semaphores

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>  //POSIX semaphores
#include <fcntl.h>  //Used: for O_CREAT and O_EXCL

#define PARENT 0
#define CHILD 1
sem_t *sem[2];

int main()
{
    int i;
    // sem_unlink("/pntcrodriguez4");
    // sem_unlink("/cldcrodriguez4");
    //sem_open returns a pointer (path,(create and excluively), permission, value)
    sem[PARENT] = sem_open("/pntcrodriguez4", O_CREAT | O_EXCL, 0644, 1);  
    sem[CHILD] = sem_open("/cldcrodriguez4", O_CREAT | O_EXCL, 0644, 0);  
    
    
    pid_t pid = fork();

    if (pid == 0) {
        // child
        for (i=0; i<5; i++) {
            sem_wait(sem[CHILD]);
            // Start critcal section
            printf("I'm the child\n");
            // End critcal section
            sem_post(sem[PARENT]);
        }
    } else {
        // parent
        for (i=0; i<5; i++) {
            sem_wait(sem[PARENT]);
            printf("I'm the parent\n");
            sem_post(sem[CHILD]);
        }
        sem_unlink("/pntcrodriguez4");
        sem_unlink("/cldcrodriguez4");
    }
    return 0;
}
