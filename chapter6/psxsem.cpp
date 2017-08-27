#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
//#include <sys/msg.h>
#include <fstream>
#include <string.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

int main()
{
    sem_t* sem_id;
    if ((sem_id = sem_open("/test.sem", O_CREAT, O_RDWR, 66)) == SEM_FAILED)
        perror("sem_open");
    return 0;
}
