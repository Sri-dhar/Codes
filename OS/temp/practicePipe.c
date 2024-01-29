#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>

int main()
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        printf("Error occurred while creating pipe");
        return 1;
    }
    //pipe is ready

    pid_t id;
    if ((id = fork()) == -1)
    {
        printf("Error occurred while forking");
        return 2;
    }

    if (id == 0) //inside child
    {
        close(fd[0]);
        int x = 0;
        printf("Enter a number: ");
        scanf("%d", &x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int y = 0;
        read(fd[0], &y, sizeof(int));
        printf("The number received using the child process is: %d", y);
        close(fd[0]);
    }
    return 0;
}