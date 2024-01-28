#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("test.txt", O_RDONLY);
    printf("open: File descriptor: %d\n", fd);

    int fd2 = creat("newfile.txt", 0777);
    printf("creat: File descriptor: %d\n", fd2);

    int newfd = dup(fd);
    printf("dup: Duplicated file descriptor: %d\n", newfd);

    int newfd2 = dup2(fd, 15);
    printf("dup2: Duplicated file descriptor: %d\n", newfd2);

    int pipefd[2];
    pipe(pipefd);
    printf("pipe: Read file descriptor: %d, Write file descriptor: %d\n", pipefd[0], pipefd[1]);

    char buffer[10];
    read(fd, buffer, 10);
    printf("read: Data: %s\n", buffer);

    char *data = "Hello, world!";
    write(fd2, data, 13);
    printf("write: Wrote data to file\n");

    close(fd);
    close(fd2);
    close(newfd);
    close(newfd2);
    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}