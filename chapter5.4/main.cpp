#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

int pipe_proc(char* proc_name, int in) {
    std::vector<std::string> tokens;
    const char* token = strtok(proc_name, " ");
    while(token) {
        tokens.push_back(std::string(token));
        token = strtok(NULL, " ");
    }
    std::vector<const char *> tokens_ch;
    for (int i = 0; i < tokens.size(); i++) {
        tokens_ch.push_back(tokens[i].c_str());
    }
    tokens_ch.push_back(NULL);

    int pfd[2];
    pipe(pfd);
    if (fork()) {
        close(STDOUT_FILENO);
        dup2(pfd[1], STDOUT_FILENO);
        close(STDIN_FILENO);
        dup2(in, STDIN_FILENO);
        close(pfd[1]);
        close(pfd[0]);
        close(in);
        execvp(tokens_ch[0], (char* const*)&tokens_ch[0]);
        return 0;
    } else {
        close(pfd[1]);
        return pfd[0];
    }
}

int main()
{
    char* line = NULL;
    size_t line_length;
    getline(&line, &line_length, stdin);
    // remove trailing newline character
    char *pch = strstr(line, "\n");
    if(pch != NULL)
      strncpy(pch, "\0", 1);

    char* token = strtok(line, "|");
    std::vector<char *> tokens;
    do {
        tokens.push_back(token);
        token = strtok(NULL, "|");
    } while(token);
    int in = STDIN_FILENO;
    for (int i = 0; i < tokens.size(); i++) {
        in = pipe_proc(tokens[i], in);
    }
    remove("/home/box/result.out");
    FILE* file = fopen("/home/box/result.out", "w+");
    char c;
    while (read(in, &c, 1) == 1)
        fputc(c, file);
    fclose(file);
}


#include <unistd.h>


void main() {
        char* in_pipe = "/home/box/in.fifo";
        char* out_pipe = "/home/box/out.fifo";
        mkfifo(in_pipe, 0666);
        mkfifo(out_pipe, 0666);
        FILE* in = fopen(in_pipe, "r");
        FILE* out = fopen(out_pipe, "w");
        char c;
        while (read(in, &c, 1) == 1)
                fputc(c, out);
        fclose(in);
        fclose(out);
}
