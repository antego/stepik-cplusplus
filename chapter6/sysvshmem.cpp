#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
//#include <sys/msg.h>
#include <fstream>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main()
{
    key_t key;
    if ((key = ftok("/tmp/mem.temp", 1)) == -1)
        perror("ftok");
    int shmid;
    if ((shmid = shmget(key, 2*1024*1024, 0666 | IPC_CREAT)) == -1)
        perror("shmget");
    void* addr;
    if ((addr = shmat(shmid, NULL, 0)) == (void*)-1)
        perror("shmat");
    memset(addr, 42, 3*512*1024);

    return 0;
}
