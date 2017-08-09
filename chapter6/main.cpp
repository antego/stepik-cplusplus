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
    key_t key = ftok("/tmp/msg.temp", 1);
    int msgid = msgget(key, IPC_CREAT);
    message* msg;
    msgrcv(msgid, (void*)msg, 80, 0, 0);
    cout << "Hello World!" << endl;
    ofstream ofs;
    ofs.open("/home/box/message.txt");
    ofs.write((msg->mtext), 80);
    ofs.close();
    return 0;
}
