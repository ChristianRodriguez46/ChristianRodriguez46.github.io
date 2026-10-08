// Christian Rodriguez
// sample shared memory program
// System-V shared memory

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    char pathname[200];
    getcwd(pathname, 200);
    printf("**%s**\n", pathname);
    strcat(pathname, "/foo");
    // strcat(pathname, "/myshared.c");
    
    // ipcs <- run command in terminal
    int ipckey = ftok(pathname, 25);
    
    // Shared memory ID
    int shmid;
    
    // gets the shared memory ID (location, how big the address should be, create with premissions)
    // sizeof(int)*2  --> 2 bytes
    shmid = shmget(ipckey, sizeof(int)*2, IPC_CREAT | 0666);

    // Shared memory attach
    int *shared = shmat(shmid, (void *)0, 0);
    *shared = 225;
    printf("Shared memory address: %p\n", shared);     // %p -> passing a pointer
    printf("Shared memory address: %i\n", *shared);    // %i -> passing a integer
    usleep(2000000);

    // Detach shared memory
    shmdt(shared);
    // shared memory control, rm id
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}