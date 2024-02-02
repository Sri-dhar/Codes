#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>

int pipe1[2], pipe2[2];
pid_t child1, child2;

void terminate_children(int sig) {
    kill(child1, SIGTERM);
    kill(child2, SIGTERM);
    printf("Child processes terminated\n");
    exit(0);
}

int main() {
    char c;

    // Create pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    // Create first child process
    child1 = fork();
    if (child1 == 0) {
        // Child 1: Read from stdin and write to pipe1
        close(pipe1[0]);
        while (1) {
            c = getchar();
            write(pipe1[1], &c, 1);
        }
    }

    // Create second child process
    child2 = fork();
    if (child2 == 0) {
        // Child 2: Read from pipe1, increment, and write to pipe2
        close(pipe1[1]);
        close(pipe2[0]);
        while (1) {
            read(pipe1[0], &c, 1);
            c++;
            write(pipe2[1], &c, 1);
        }
    }

    // Parent: Read from pipe2, decrement, and print
    signal(SIGPIPE, terminate_children);
    close(pipe1[1]);
    close(pipe2[1]);
    while (1) {
        if (read(pipe2[0], &c, 1) > 0) {
            c--;
            putchar(c);
        } else {
            raise(SIGPIPE);
        }
    }

    return 0;
}