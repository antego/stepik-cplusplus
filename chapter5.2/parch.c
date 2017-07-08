#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void handleSigchld(int ign) {
	int st;
	wait(&st);
}

void main() {
	signal(SIGCHLD, &handleSigchld);
	fork();
	pause();
}
