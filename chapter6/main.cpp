#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fstream>

using namespace std;

struct message {
    long mtype;
    char mtext[80];
};

int main()
{
    key_t key;
    if((key = ftok("/tmp/msg.temp", 1))==-1)
        perror("ftok");
    int msgid;
    if((msgid = msgget(key, 0660 | IPC_CREAT ))==-1)
        perror("msgget");
    message* msg;
    if(msgrcv(msgid, (void*)msg, 80, 0, 0)==-1)
        perror("msgrcv()");
    cout << "Hello World!" << endl;
    ofstream ofs;
    ofs.open("/home/box/message.txt");
    ofs.write((msg->mtext), 80);
    ofs.close();
    if(msgctl(msgid, IPC_RMID, NULL)==-1)
        perror("rm queue");
    return 0;
}
