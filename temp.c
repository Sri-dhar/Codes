#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <setjmp.h>

int primes_between(int x, int y) {
    int count = 0;

    for (int num = x; num <= y; ++num) {
        int is_prime = 1;
        for (int i = 2; i <= num / 2; ++i) {
            if (num % i == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            printf("%d ", num);
            count++;
        }
    }

    return count;
}

jmp_buf jump_buffer;

void alarm_handler(int signo) {
    if (signo == SIGALRM) {
        printf("\nCalculation is taking too much time.\n");
        longjmp(jump_buffer, 1);
    }
}

int main() {
    int x, y, z;

    printf("Enter three numbers (x, y, z): ");
    scanf("%d %d %d", &x, &y, &z);

    pid_t child_pid;
    int prime_count;

    child_pid = fork();

    if (child_pid == 0) {
        // Child process
        prime_count = primes_between(x, y);
        exit(prime_count);
    } else if (child_pid > 0) {
        // Parent process

        // Set up the alarm signal handler
        signal(SIGALRM, alarm_handler);

        // Set the alarm for z seconds
        alarm(z);

        // Use setjmp to allow the child process to longjmp
        if (setjmp(jump_buffer) == 0) {
            // The child process has not longjmped yet

            int status;
            waitpid(child_pid, &status, 0);

            if (WIFEXITED(status)) {
                printf("\nAll the prime numbers printed\n");
            } else {
                // The child process did not exit normally
                printf("\nChild process terminated abnormally.\n");
            }
        }
    } else {
        // Fork failed
        perror("Fork failed");
        return 1;
    }

    return 0;
}
