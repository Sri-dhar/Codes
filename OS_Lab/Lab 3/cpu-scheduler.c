#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROC 100
#define INFINITY_VAL 999999

typedef struct {
    char *proc_name;
    int arrival_time;
    int cpu_burst_time;
    int remaining_burst_time;
    int turnaround_time;
    int wait_time;
} Process;

void ReadProcTable(char *filename);
void PrintProcTable();
void FCFS();
void RoundRobin(int quantum);
void ShortestRemainingBurstFirst();
void DataPrint();
void PrintRoundRobinHeader();

Process proctable[MAX_PROC];
int num_procs = 0;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    ReadProcTable(argv[1]);
    PrintProcTable();

    int choice;
    int quantum;

    do {
        printf("\n-------------------------------------------------\n");
        printf("CPU Scheduling Simulation\n");
        printf("-------------------------------------------------\n");
        printf("Select the scheduling algorithm [1,2,3 or 4]:\n");
        printf("1. First Come First Served (FCFS)\n");
        printf("2. Round Robin (RR)\n");
        printf("3. Shortest Remaining Burst First (SRBF)\n");
        printf("4. Exit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("-------------------------------------------------\n");
                printf("First Come First Served Scheduling\n");
                printf("-------------------------------------------------\n");
                FCFS();
                DataPrint();
                break;
            case 2:
                printf("Enter the time quantum: ");
                scanf("%d", &quantum);
                printf("-------------------------------------------------\n");
                printf("Round Robin Scheduling\n");
                printf("-------------------------------------------------\n");
                RoundRobin(quantum);
                DataPrint();
                break;
            case 3:
                printf("-------------------------------------------------\n");
                printf("Shortest Remaining Burst First Scheduling\n");
                printf("-------------------------------------------------\n");
                ShortestRemainingBurstFirst();
                DataPrint();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                break;
        }
        ReadProcTable(argv[1]);
    } while (choice != 4);

    return 0;
}

void ReadProcTable(char *filename) {
    num_procs = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char name[10];
    int arrival, cpuburst;
    while (fscanf(file, "%s %d %d", name, &arrival, &cpuburst) == 3) {
        proctable[num_procs].proc_name = strdup(name);
        proctable[num_procs].arrival_time = arrival;
        proctable[num_procs].cpu_burst_time = cpuburst;
        proctable[num_procs].remaining_burst_time = cpuburst;
        proctable[num_procs].turnaround_time = 0;
        proctable[num_procs].wait_time = 0;
        num_procs++;
    }

    fclose(file);
}

void PrintProcTable() {
    printf("Process Table:\n");
    for (int i = 0; i < num_procs; i++) {
        printf("%s %d %d\n", proctable[i].proc_name, proctable[i].arrival_time, proctable[i].cpu_burst_time);
    }
}

void FCFS() {
    int current_time = 0;
    for (int i = 0; i < num_procs; i++) {
        if (current_time < proctable[i].arrival_time) {
            current_time = proctable[i].arrival_time;
        }
        printf("[%d - %d] %s running\n", current_time, current_time + proctable[i].cpu_burst_time, proctable[i].proc_name);
        proctable[i].wait_time = current_time - proctable[i].arrival_time;
        current_time += proctable[i].cpu_burst_time;
        proctable[i].turnaround_time = current_time - proctable[i].arrival_time;
    }
}

void PrintRoundRobinHeader() {
    printf("-------------------------------------------------\n");
    printf("Round Robin Scheduling\n");
    printf("-------------------------------------------------\n");
}

void RoundRobin(int quantum) {
    int *visited = (int *)calloc(num_procs, sizeof(int));
    int currentTime = 0;

    int queue[MAX_PROC];
    int front = 0, rear = -1, itemCount = 0;

    for (int i = 0; i < num_procs; i++) {
        if (proctable[i].arrival_time <= currentTime) {
            visited[i] = 1;
            rear = (rear + 1) % MAX_PROC;
            queue[rear] = i;
            itemCount++;
        }
    }

    PrintRoundRobinHeader();

    while (itemCount > 0) {
        int selected_proc = queue[front];
        front = (front + 1) % MAX_PROC;
        itemCount--;

        if (proctable[selected_proc].remaining_burst_time > quantum) {
            printf("[%d - %d] %s running\n", currentTime, currentTime + quantum, proctable[selected_proc].proc_name);
            currentTime += quantum;
            proctable[selected_proc].remaining_burst_time -= quantum;
        } else {
            printf("[%d - %d] %s running\n", currentTime, currentTime + proctable[selected_proc].remaining_burst_time, proctable[selected_proc].proc_name);
            currentTime += proctable[selected_proc].remaining_burst_time;
            proctable[selected_proc].remaining_burst_time = 0;
            proctable[selected_proc].turnaround_time = currentTime - proctable[selected_proc].arrival_time;
            proctable[selected_proc].wait_time = proctable[selected_proc].turnaround_time - proctable[selected_proc].cpu_burst_time;
        }

        for (int i = 0; i < num_procs; i++) {
            if (proctable[i].arrival_time <= currentTime && visited[i] == 0) {
                visited[i] = 1;
                rear = (rear + 1) % MAX_PROC;
                queue[rear] = i;
                itemCount++;
            }
        }

        if (proctable[selected_proc].remaining_burst_time > 0) {
            rear = (rear + 1) % MAX_PROC;
            queue[rear] = selected_proc;
            itemCount++;
        }
    }
    free(visited);
}

void ShortestRemainingBurstFirst() {
    int current_time = 0;
    int completed_procs = 0;
    while (num_procs > completed_procs) {
        int shortest_remaining_burst = INFINITY_VAL;
        int selected_proc = -1;

        for (int i = 0; i < num_procs; i++) {
            if (proctable[i].arrival_time <= current_time && proctable[i].remaining_burst_time > 0) {
                if (shortest_remaining_burst > proctable[i].remaining_burst_time) {
                    shortest_remaining_burst = proctable[i].remaining_burst_time;
                    selected_proc = i;
                }
            }
        }

        if (selected_proc != -1) {
            printf("[%d - %d] %s running\n", current_time, current_time + 1, proctable[selected_proc].proc_name);
            proctable[selected_proc].remaining_burst_time -= 1;
            if (proctable[selected_proc].remaining_burst_time == 0) {
                completed_procs++;
                proctable[selected_proc].turnaround_time = current_time - proctable[selected_proc].arrival_time + 1;
                proctable[selected_proc].wait_time = proctable[selected_proc].turnaround_time - proctable[selected_proc].cpu_burst_time;
            }
            current_time++;
        } else {
            current_time++;
        }
    }
}

void DataPrint() {
    printf("Process   Arrival        CPU Burst      Turnaround     Wait\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < num_procs; i++) {
        printf("%-10s%-15d%-15d%-15d%-15d\n",
               proctable[i].proc_name, proctable[i].arrival_time,
               proctable[i].cpu_burst_time, proctable[i].turnaround_time,
               proctable[i].wait_time);
    }
    printf("-------------------------------------------------\n");

    double avg_turnaround = 0, avg_wait = 0;
    for (int i = 0; i < num_procs; i++) {
        avg_turnaround += proctable[i].turnaround_time;
        avg_wait += proctable[i].wait_time;
    }
    avg_turnaround /= num_procs;
    avg_wait /= num_procs;
    printf("Average Turnaround Time: %.2f\n", avg_turnaround);
    printf("Average Wait Time: %.2f\n", avg_wait);
}
