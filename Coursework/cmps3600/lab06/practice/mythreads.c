
// Christian Rodriguez

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>  //POSIX semaphores
#include <pthread.h>    //POSIX threads

sem_t sem[2];

void *xthread(void *arg) {
    int num = (int)(long)arg;
    int other = !num;
    int count = 0;
    while (count++ < 5) {
        sem_wait(&sem[num]);
        /* Start critcal section*/
        printf("I am thread %i\n", num);
        fflush(stdout);
        /* End critcal section*/
        sem_post(&sem[other]);
    }
    return (void *)0;
}

int main()
{
    void *status;
    /* 
     * make both zero in last funct arg will cause sems to wait
     * make one at least 1 to make one available
    */

    sem_init( &sem[0], 0, 1);   // <- give semaphores[0] intial values
    sem_init( &sem[1], 0, 0);   // <- give semaphores[1] intial values

    pthread_t tid[2];
    /*thread ID, NULL, funct name, arg list*/
    pthread_create(&tid[0], NULL, (void *)xthread, (void *)0);
    pthread_create(&tid[1], NULL, (void *)xthread, (void *)1);
    pthread_join(tid[0], &status);
    pthread_join(tid[1], &status);
    return 0;
}
