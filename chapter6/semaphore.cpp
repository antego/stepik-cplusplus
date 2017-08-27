#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
//#include <sys/msg.h>
#include <fstream>
#include <string.h>
#include <sys/sem.h>


typedef union semun
{
  int val;
  struct semid_ds *buf;
  ushort * array;
} semun_t;

int main()
{
    key_t key;
    if ((key = ftok("/tmp/sem.temp", 1))==-1)
        perror("ftok");
    int sems;
    if ((sems = semget(key, 16, 0660 | IPC_CREAT)) == -1)
        perror("semget");
    for (int i = 0; i < 16; i++) {
        semun_t arg;
        arg.val = i;

        if (semctl(sems, i, SETVAL, arg))
            perror("semctl");
    }
    return 0;
}
