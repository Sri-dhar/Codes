#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>

int x, y, z;
#define MAX_PRIME_LIMIT 100000000 // maximum limit of prime nos.
#define EXIT_CODE_1 1
#define EXIT_CODE_0 0

int is_prime(int num)
{
    int *seiveOfEratosthenes = (int *)malloc(MAX_PRIME_LIMIT);
    // using sieveOfEratosthenes algorithms for efficient prime calculation
    //  if (num <= 1) return 0;
    for(int i=0; i<y; i++)
    {

    }
    if (num % 2 == 0 && num > 2)
        return 0;
    for (int i = 3; i * i <= num; i += 2)
        if (num % i == 0)
            return 0;
    return 1;
}

void find_primes(int x, int y)
{
    for (int i = x; i <= y; i++) if (is_prime(i)) printf("%d\n", i);
}

jmp_buf jmp_buf_variable;

void alarm_handler(int signum)
{
    longjmp(jmp_buf_variable, 1);
    printf("Alarm_handler called: by %d",signum);
}

int main()
{
    printf("Enter the values of x , y and z:");
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &z);

    pid_t pid = fork();

    if (pid == 0)
    {
        find_primes(x, y);
        exit(0);
    }
    else if (pid > 0)
    {
        signal(SIGALRM, alarm_handler);
        alarm(z);
        // setting alarm to go off after z seconds
        if (setjmp(jmp_buf_variable) == 0)
        {
            // if setjmp returns 0 we have to wait for the child to complete its execution
            wait(NULL);
            printf("All the prime numbers printed\n");
        }
        else
        {
            // if setjmp return something different
            // we have to kill the child process
            // by raising the alarm signal
            kill(pid, SIGKILL);
            printf("Calculation is taking too much time\n");
        }
    }
    else
    {
        printf("Error in fork\n");
        return EXIT_CODE_1;
    }

    return EXIT_CODE_0;
}