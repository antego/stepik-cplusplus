#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
    int sockets[2];
    socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
    char buf[1024];
    if (fork()) {
        close(sockets[1]);
        read(sockets[0], buf, 1024, 0);
        wait();
    } else {
        close(sockets[0]);
        read(sockets[1], buf, 1024, 0);
        wait();
    }
    printf("Hello World!\n");
    return 0;
}
