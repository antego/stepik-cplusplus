#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
//#include <sys/msg.h>
#include <fstream>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int memfd;
    if ((memfd = shm_open("/test.shm", O_RDWR | O_CREAT, 0)) == -1)
        perror("shm_open");
    if (ftruncate(memfd, 1*1024*1024) == -1)
        perror("ftruncate");
    void* addr;
    if ((addr = mmap(NULL, 1*1024*1024, PROT_WRITE | PROT_READ, MAP_SHARED, memfd, 0)) == MAP_FAILED)
        perror("mmap");
    memset(addr, 13, 1*1024*1024);


    return 0;
}
