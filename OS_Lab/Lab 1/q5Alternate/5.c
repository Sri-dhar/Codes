#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        exit(1);
    }

    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
       fprintf(stderr,"Error opening %s",argv[1]);
        exit(1);
    }
    close(0);
    if (dup(fd1) == -1) {
        perror("Error duplicating file descriptor");
        exit(1);
    }

    int fd2 = open(argv[2], O_CREAT | O_WRONLY, 0644);
    if (fd2 == -1) {
        fprintf(stderr,"Error opening %s",argv[2]);
        exit(1);
    }
    close(1);
    if (dup(fd2) == -1) {
        perror("Error duplicating file descriptor");
        exit(1);
    }

    int p[2];
    if (pipe(p) == -1) {
        perror("Error creating pipe");
        exit(1);
    }

    if (fork() != 0) {
        if (fork() != 0) {
            close(p[1]);
            close(p[0]);
            wait(NULL);
            wait(NULL);
        } else {  // c2
            close(1);
            if (dup(p[1]) == -1) {
                perror("Error duplicating file descriptor");
                exit(1);
            }
            execl("./convert", "convert", (char*)0);
            perror("Error executing convert");
            exit(1);
        }
    } else {
        // c1
        close(p[1]);
        close(0);
        if (dup(p[0]) == -1) {
            perror("Error duplicating file descriptor");
            exit(1);
        }
        execl("./count", "count", (char*)0);
        perror("Error executing count");
        exit(1);
    }

    exit(0);
}
