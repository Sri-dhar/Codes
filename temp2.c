#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf env;

void alarm_handler(int signum) {
    longjmp(env, 1);
}

int is_prime(int num) {
    if (num <= 1) return 0;
    if (num % 2 == 0 && num > 2) return 0;
    for(int i = 3; i * i <= num; i += 2) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

void find_primes(int x, int y) {
    for (int i = x; i <= y; i++) {
        if (is_prime(i)) {
            printf("%d\n", i);
        }
    }
}

int main() {
    int x, y, z;
    printf("Enter three numbers: ");
    scanf("%d%d%d", &x, &y, &z);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        find_primes(x, y);
        exit(0);
    } else if (pid > 0) {
        // Parent process
        signal(SIGALRM, alarm_handler);
        alarm(z);
        if (setjmp(env) == 0) {
            wait(NULL);
            printf("All the prime numbers printed\n");
        } else {
            kill(pid, SIGKILL);
            printf("Calculation is taking too much time\n");
        }
    } else {
        // Fork failed
        printf("Error in fork\n");
        return 1;
    }

    return 0;
}