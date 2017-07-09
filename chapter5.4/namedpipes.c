#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main() {
        char* in_pipe = "in.fifo";
        char* out_pipe = "out.fifo";
        mkfifo(in_pipe, 0666);
        mkfifo(out_pipe, 0666);
        int in = open(in_pipe, O_RDWR);
        FILE* out = fopen(out_pipe, "w");
        char c;
        while (read(in, &c, 1) == 1) {
                fputc(c, out);
                printf(&c);
        }
        close(in);
        fclose(out);
}
