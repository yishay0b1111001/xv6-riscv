#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char* argv[])
{
    int pipes[2];
    pipe(pipes);
    int pid = fork();
    if (pid > 0) {
        //parrent;
        close(pipes[0]);
        write(pipes[1], "a", 1);
        close(pipes[1]);
        char msg[1];
	wait(0);
        read(pipes[0], msg, 1);
        fprintf(1, "%d: received ping\n", pid);
        exit(0);
    }
    else if (pid == 0) {
        //child
        close(pipes[0]);
        char msg[1];
        read(pipes[0], msg, 1);
        close(pipes[0]);
        fprintf(1, "%d: received pong\n", pid);
        write(pipes[1], "a", 1);
        close(pipes[1]);
    }
    return 0;
}
