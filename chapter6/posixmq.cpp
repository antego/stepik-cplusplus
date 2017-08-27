#include <iostream>
#include <sys/types.h>
#include <fstream>
#include <string.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

using namespace std;

int main()
{
    mqd_t id;
    if ((id = mq_open("/test.mq", O_RDONLY | O_CREAT)) == -1)
        perror("mq_open");
    char msg[80];
    if (mq_receive(id, msg, 80, NULL) == -1)
        perror("mq_receive");
    cout << "Hello World!" << endl;
    ofstream ofs;
    ofs.open("/home/box/message.txt");
    ofs.write((msg), strlen(msg));
    ofs.close();
    if(mq_close(id) == -1)
        perror("mq_close");
    return 0;
}
