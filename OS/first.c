#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    // Forking a new process
    pid = fork();

    if (pid < 0) {
        // Error occurred during fork
        fprintf(stderr, "Fork failed!\n");
        return 1;
    } else if (pid == 0) {
        // Code executed by child process

        printf("Child process: PID=%d, Parent PID=%d\n", getpid(), getppid());

        // Child process-specific code

        return 0;
    } else {
        // Code executed by parent process

        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), pid);

        // Parent process-specific code

        return 0;
    }
}
