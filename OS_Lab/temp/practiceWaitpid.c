#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int pid1 = fork();
    if (pid1 == -1) {
        printf("Error creating process");
        return 1;
    }
    if (pid1 == 0) {
        sleep(4);
        printf("Finished execution (%d)\n", getpid());
        return 0;   
    }

    int pid2 = fork();
    if (pid2 == -1) {
        printf("Error creating process");
        return 2;
    }
    if (pid2 == 0) {
        sleep(1);
        printf("Finished execution (%d)\n", getpid());
        return 0;   
    }

    int pid1_res = waitpid(-1, NULL, WNOHANG);
    printf("Waited for %d\n", pid1_res);
    int pid2_res = waitpid(pid2, NULL, WNOHANG);
    printf("Waited for %d\n", pid2_res);

    return 0;
}