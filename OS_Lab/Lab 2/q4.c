#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>

void count() {
    int count = 0;
    int ch;

    while ((ch = getchar()) != EOF) {
        if (!isalpha(ch)) {
            count++;
        }
        putchar(ch);
    }

    fprintf(stderr, "Count of non alphabetic characters: %d\n", count);
    exit(0);
}

void convert() {
    int ch;

    while ((ch = getchar()) != EOF) {
        if (islower(ch)) {
            putchar(toupper(ch));
        } else if (isupper(ch)) {
            putchar(tolower(ch));
        } else {
            putchar(ch);
        }
    }

    exit(0);
}

int main(int argc, char *argv[]) {
    int fd_in, fd_out;
    int pipe_fd[2];
    pid_t pid_count, pid_convert;
    int status;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        exit(1);
    }

    fd_in = open(argv[1], O_RDONLY);
    if (fd_in == -1) {
        perror("Error opening file1");
        exit(1);
    }

    fd_out = creat(argv[2], 0644);
    if (fd_out == -1) {
        perror("Error creating file2");
        close(fd_in);
        fd_out = creat(argv[2], 0644);
        exit(1);
    }

    // In Unix-like systems, file descriptors 0, 1, and 2 are reserved 
    // for standard input, standard output, and standard error, respectively.
    // By closing file descriptor 0 and duplicating fd_in to file descriptor
    // 0 using dup(fd_in), the program redirects standard input from the 
    // keyboard to the file specified by file1.

    close(0);
    if (dup(fd_in) == -1) {
        perror("Error duplicating file descriptor for stdin");
        close(fd_in);
        close(fd_out);
        exit(1);
    }

    close(1);
    if (dup(fd_out) == -1) {
        perror("Error duplicating file descriptor for stdout");
        close(fd_in);
        close(fd_out);
        exit(1);
    }

    if (pipe(pipe_fd) == -1) {
        perror("Error creating pipe");
        close(fd_in);
        close(fd_out);
        exit(1);
    }

    pid_count = fork();
    if (pid_count == -1) {
        perror("Error forking count");
        close(fd_in);
        close(fd_out);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        exit(1);
    }

    if (pid_count == 0) {
        close(pipe_fd[1]);
        close(0);
        dup(pipe_fd[0]);
        close(pipe_fd[0]);
        close(fd_in);
        close(fd_out);
        count();
    } 
    else 
    {
        pid_convert = fork();
        if (pid_convert == -1) {
            perror("Error forking convert");
            close(fd_in);
            close(fd_out);
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            waitpid(pid_count, &status, 0);
            exit(1);
        }

        if (pid_convert == 0) {
            close(pipe_fd[0]);
            close(1);
            dup(pipe_fd[1]);
            close(pipe_fd[1]);
            close(fd_in);
            close(fd_out);
            convert();
        } 
        else {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            waitpid(pid_count, &status, 0);
            waitpid(pid_convert, &status, 0);
            close(fd_in);
            close(fd_out);
            exit(0);
        }
    }
}
