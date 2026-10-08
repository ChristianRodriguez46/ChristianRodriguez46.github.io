#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>  // POSIX semaphores

int eat[5] = {0,0,0,0,0}, max_eats, done = 0;
sem_t sem[5];
pthread_mutex_t monitor;

void *philosopher(void *arg) {
    int me = (int)(long)arg;
    printf("thread %i\n", me);
    // Setting a hierarchy system
    int forknum[2] = { me, (me+1)%5 };
    if (forknum[0] > forknum[1]) {
        int tmp = forknum[0];
        forknum[0] = forknum[1];
        forknum[1] = tmp;
    }


    while (!done) {
        // think
        // grab 2 forks
        pthread_mutex_lock(&monitor);
        sem_wait(&sem[forknum[0]]);
        sem_wait(&sem[forknum[1]]);
        pthread_mutex_unlock(&monitor);
        // eat
        ++eat[me];
        printf("%i %i %i %i %i\n", eat[0], eat[1], eat[2], eat[3], eat[4]);
        
        sem_post(&sem[forknum[0]]);
        sem_post(&sem[forknum[1]]);
        
        if (eat[me] > max_eats)
            done = 1;
        // rest

    }

    return (void *)0;
}

int main(int argc, char *argv[]) {
    int i;
    void *status[5];

    if (argc > 1)
        max_eats = atoi(argv[1]);

    for (i=0; i<5; i++)
        sem_init(&sem[i], 0, 1);

    // NULL means it is unlocked(someone is allowed to get)
    pthread_mutex_init(&monitor, NULL);
    // Hone many threads: five threads
    pthread_t tid[5];
    for (i=0; i<5; i++)
        pthread_create(&tid[i], NULL, philosopher, (void *)(long)i);
    for (i=0; i<5; i++)
        pthread_join(tid[i],&status[i]);

    return 0;
}