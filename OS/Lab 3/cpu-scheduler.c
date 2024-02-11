#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_PROCESS 10
int numOfProcess = 0;

void getNoOfProcesses(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file\n");
        exit(1);
    }

    while (!feof(file))
    {
        char *name = (char *)malloc(10);
        int arrival, cpuburst;
        fscanf(file, "%s %d %d", name, &arrival, &cpuburst);
        numOfProcess++;
    }
    fclose(file);
}

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

    printf("\n%-10s%-15s%-15s%-15s%-15s\n", "Process", "Arrival", "CPU Burst", "Turnaround", "Wait");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < numProcesses; i++)
    {
        printf("%-10s%-15d%-15d%-15d%-15d\n",
               processtable[i].name,
               processtable[i].arrival,
               processtable[i].cpuburst,
               processtable[i].turnaround,
               processtable[i].wait);

        totalTurnaround += processtable[i].turnaround;
        totalWait += processtable[i].wait;
    }

    printf("-------------------------------------------------\n");

    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaround / numOfProcess);
    printf("Average Wait Time: %.2f\n", (float)totalWait / numOfProcess);
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

void roundRobinScheduling(Process processtable[MAX_PROCESS], int numProcesses, int quantum)
{
    int time = 0;
    int remainingBurst[MAX_PROCESS];

    printf("-----------------------------------------------\n");
    printf("             Round Robin Scheduling            \n");
    printf("-----------------------------------------------\n");

    // Initialize remainingBurst array and other variables
    for (int i = 0; i < numProcesses; i++)
    {
        remainingBurst[i] = processtable[i].cpuburst;
        processtable[i].wait = 0;
        processtable[i].turnaround = 0;
    }

    while (1)
    {
        bool done = true;

        for (int i = 0; i < numProcesses; i++)
        {
            if (remainingBurst[i] > 0)
            {
                done = false;

                if (remainingBurst[i] > quantum)
                {
                    time += quantum;
                    remainingBurst[i] -= quantum;
                }
                else
                {
                    time += remainingBurst[i];
                    processtable[i].turnaround = time - processtable[i].arrival;
                    processtable[i].wait = processtable[i].turnaround - processtable[i].cpuburst;
                    remainingBurst[i] = 0;
                }
            }
        }

        if (done)
            break;
    }

    printTurnaroundWaitTimes(processtable, numProcesses);
}


void srbfScheduling(Process processtable[MAX_PROCESS], int numProcesses)
{
    int time = 0;
    int remainingBurst[MAX_PROCESS];

    printf("-----------------------------------------------\n");
    printf("     Shortest Remaining Burst First Scheduling  \n");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < numProcesses; i++)
    {
        remainingBurst[i] = processtable[i].cpuburst;
    }

    while (1)
    {
        int smallest = INT_MAX;
        int shortest = -1;

        for (int i = 0; i < numProcesses; i++)
        {
            if (processtable[i].arrival <= time && remainingBurst[i] < smallest && remainingBurst[i] > 0)
            {
                smallest = remainingBurst[i];
                shortest = i;
            }
        }

        if (shortest == -1)
        {
            time++;
            continue;
        }

        remainingBurst[shortest]--;
        if (remainingBurst[shortest] == 0)
        {
            processtable[shortest].turnaround = time + 1 - processtable[shortest].arrival;
            processtable[shortest].wait = processtable[shortest].turnaround - processtable[shortest].cpuburst;
        }

        time++;

        int done = 1;
        for (int i = 0; i < numProcesses; i++)
        {
            if (remainingBurst[i] > 0)
            {
                done = 0;
                break;
            }
        }

        if (done)
            break;
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

    getNoOfProcesses(argv[1]);


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
    do
    {
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

        case 2:
        {
            int quantum;
            printf("Enter the time quantum: ");
            scanf("%d", &quantum);
            roundRobinScheduling(processtable, MAX_PROCESS, quantum);
            break;
        }
        case 3:
        {
            srbfScheduling(processtable, MAX_PROCESS);
            break;
        }

        case 4:
            return 0;

        default:
            printf("Invalid choice. Exiting...\n");
            return 1;
        }
    } while (1);
    return 0;
}

// gcc cpu-scheduler.c -o cpu-scheduler && ./cpu-scheduler process.txt