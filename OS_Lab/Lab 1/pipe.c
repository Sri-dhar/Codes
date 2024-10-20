#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    int pipefd[2];
    char buffer[100];

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process (reader)
        close(pipefd[1]);  // Close the write end

        // Read data from the pipe
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer));

        if (bytesRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Process the data read from the pipe
        printf("Child Process: Received data from parent: %.*s\n", (int)bytesRead, buffer);

        // Close the read end of the pipe
        close(pipefd[0]);
    } else {
        // Parent process (writer)
        close(pipefd[0]);  // Close the read end

        // Write data into the pipe
        const char *data = "Hello, child!";
        ssize_t bytesWritten = write(pipefd[1], data, strlen(data));

        if (bytesWritten == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Close the write end of the pipe
        close(pipefd[1]);
    }

    return 0;
}
