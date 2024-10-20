#include <stdio.h>
#include <stdbool.h>

#define MAX_RESOURCES 10
#define MAX_PROCESSES 10

bool isSafe(int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int n, int m) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};

    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    return count == n;
}

void detectDeadlock(int resources[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int n, int m) {
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    int deadlockProcesses[MAX_PROCESSES];
    int deadlockCount = 0;

    for (int i = 0; i < m; i++) {
        work[i] = resources[i];
    }

    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            bool canAllocate = true;
            for (int j = 0; j < m; j++) {
                if (max[i][j] - allocation[i][j] > work[j]) {
                    canAllocate = false;
                    break;
                }
            }
            if (canAllocate) {
                for (int j = 0; j < m; j++) {
                    work[j] += allocation[i][j];
                }
                finish[i] = true;
                i = -1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            deadlockProcesses[deadlockCount++] = i;
        }
    }

    if (deadlockCount == 0) {
        printf("No deadlock.\n");
    } else {
        printf("Deadlock detected. Processes in deadlock: ");
        for (int i = 0; i < deadlockCount; i++) {
            printf("P%d ", deadlockProcesses[i]);
        }
        printf("\n");
    }
}

int main() {
    int resources[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int n, m;

    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    fscanf(file, "%d", &m);
    fscanf(file, "%d", &n); 

    for (int i = 0; i < m; i++) {
        fscanf(file, "%d", &resources[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(file, "%d", &allocation[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(file, "%d", &max[i][j]);
        }
    }

    fclose(file);

    detectDeadlock(resources, max, allocation, n, m);

    return 0;
}

