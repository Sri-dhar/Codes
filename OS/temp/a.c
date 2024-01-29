#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main() {
    pid_t childPID = fork();

    if (childPID == -1) {
        perror("fork");
        return 1;  // Error in forking
    }

    if (childPID == 0) {
        // Code executed by the child process
        printf("Child process: PID = %d  Parent ID: %d\n", getpid(),getppid());
    } else {
        // Code executed by the parent process
        printf("Parent process: PID = %d, Child PID = %d\n Parent PID: %d\n", getpid(), childPID, getppid());
    }
   // while(1) 
    printf("%d || %d\n",childPID,getpid());

    return 0;
}
