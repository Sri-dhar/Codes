#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_PROCESS 10

typedef struct
{
    char *name;
    int arrival;
    int cpuburst;
    int turnaround;
    int wait;
} Process;

Process processtable[MAX_PROCESS];

void printProcess(Process p)
{
    printf("%s %d %d %d %d\n", p.name, p.arrival, p.cpuburst, p.turnaround, p.wait);
}

void printProcessExecution(int start, int end, Process p)
{
    printf("[%d-%d] %s running\n", start, end, p.name);
}

void printTurnaroundWaitTimes(Process processtable[MAX_PROCESS], int numProcesses)
{
    int totalTurnaround = 0;
    int totalWait = 0;

    printf("\nTurnaround times:");
    for (int i = 0; i < numProcesses; i++)
    {
        printf(" %s[%d]", processtable[i].name, processtable[i].turnaround);
        totalTurnaround += processtable[i].turnaround;
    }

    printf("\nWait times:");
    for (int i = 0; i < numProcesses; i++)
    {
        printf(" %s[%d]", processtable[i].name, processtable[i].wait);
        totalWait += processtable[i].wait;
    }

    printf("\nAverage turnaround time: %.2f", (float)totalTurnaround / numProcesses);
    printf("\nAverage wait time: %.2f\n", (float)totalWait / numProcesses);
}

void fcfsScheduling(Process processtable[MAX_PROCESS], int numProcesses)
{
    int time = 0;

    printf("-------------------------------------------------\n");
    printf("         First Come First Served Scheduling      \n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < numProcesses; i++)
    {
        if (processtable[i].name != NULL)
        {
            printProcessExecution(time, time + processtable[i].cpuburst, processtable[i]);
            processtable[i].turnaround = time + processtable[i].cpuburst - processtable[i].arrival;
            processtable[i].wait = time - processtable[i].arrival;
            time += processtable[i].cpuburst;
        }
    }

    printTurnaroundWaitTimes(processtable, numProcesses);
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: cpu-scheduler <inputfile>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error: Could not open file\n");
        return 1;
    }

    printf("The processes are : \n");

    while (!feof(file))
    {
        char *name = (char *)malloc(10);
        int arrival, cpuburst;
        fscanf(file, "%s %d %d", name, &arrival, &cpuburst);
        Process p = {name, arrival, cpuburst, 0, 0};
        printf("%s %d %d\n", p.name, p.arrival, p.cpuburst);
        processtable[arrival] = p;
    }

    fclose(file);

    int choice;
    printf("--------------------------------------------------\n");
    printf("           CPU SCHEDULING SIMULATION              \n");
    printf("--------------------------------------------------\n");
    printf("Select the scheduling algorithm [1,2,3 or 4]:\n");
    printf("1. First-Come First-Served (FCFS)\n");
    printf("2. Round-Robin\n");
    printf("3. SRBF\n");
    printf("4. Exit\n");

    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        fcfsScheduling(processtable, MAX_PROCESS);
        break;
    }

    // Add cases for other scheduling algorithms if needed

    case 4:
        // Exit
        return 0;

    default:
        printf("Invalid choice. Exiting...\n");
        return 1;
    }

    return 0;
}
