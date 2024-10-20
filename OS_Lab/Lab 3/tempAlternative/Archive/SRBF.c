#include <stdio.h>
#include <stdlib.h>

#define maximum_processes 1000
typedef struct {
    char *name;
    int arrival;
    int cpu_burst;
    int turnaround;
    int wait;
    int time_received;
    int finished;
    int timeCompleted;


} Process;

typedef struct {
    Process **processes;
    int numberOfProcesses;
} ProcessArray;

ProcessArray *readProcessesFromFile(char *filename) {
    //Opening the file to read
    FILE *file = fopen(filename, "r");

    //Initialising the Processes Array
    ProcessArray *pa = malloc(sizeof(ProcessArray));
    pa->processes = calloc(maximum_processes, sizeof(Process));
    pa->numberOfProcesses = 0;


    char input[25];

    while (fgets(input, 25, file)) {
        char *processName = malloc(5 * sizeof(char));
        int arrival, cpuBurst;
        sscanf(input, "%s %d %d\n", processName, &arrival, &cpuBurst);
        printf("%s %d %d\n", processName, arrival, cpuBurst);
        Process *p = malloc(sizeof(Process));
        p->name = processName;
        p->arrival = arrival;
        p->cpu_burst = cpuBurst;
        p->wait = -1;
        p->turnaround = -1;
        p->time_received=0;
        p->finished=0;
        p->timeCompleted=-1;
        pa->processes[pa->numberOfProcesses++] = p; // Adding the process to the array
    }
    return pa;


};

void printProcessTable(ProcessArray *pa) {
    for (int i = 0; i < pa->numberOfProcesses; i++) {
        printf("Process Name: %s\n", pa->processes[i]->name);
        printf("Arrival: %d || ", pa->processes[i]->arrival);
        printf("CPU Burst: %d || ", pa->processes[i]->cpu_burst);
        printf("Turnaround: %d || ", pa->processes[i]->turnaround);
        printf("Wait: %d || ", pa->processes[i]->wait);
        printf("Time Completed: %d \n", pa->processes[i]->timeCompleted);

    }
}


int main() {
    int currentTime = 0, completed_process = 0;
    ProcessArray *pa = readProcessesFromFile("processes.txt");
    printProcessTable(pa);

}