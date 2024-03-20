#include<stdio.h>
#include<stdlib.h>

void printAllocationMatrix(int n, int m, int matrix[n][m])
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

int main()
{
    FILE *file = fopen("/home/ketone/Codes/OS/Assignment 4/allocation_matrix2.txt", "r");
    if(file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }
    int n, m;
    fscanf(file, "%d %d", &n, &m);
    int allocation[n][m];
    int available[m]; 
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            fscanf(file, "%d", &allocation[i][j]);

    for(int i = 0; i < m; i++)
        fscanf(file, "%d", &available[i]);

    fclose(file); 

    printf("The allocation matrix is : \n");
    printAllocationMatrix(n, m, allocation);

    printf("The available resources are : \n");
    for(int i = 0; i < m; i++)
        printf("%d ", available[i]);
    printf("\n");

    //check if deadlock exists 
    //if it exists tell the minimum no. of process whose termination ends deadlock
    int process[n];
    for(int i = 0; i < n; i++)
        process[i] = 0;
    int deadlock = 0;
    for(int i = 0; i < m; i++)
    {
        int flag = 0;
        for(int j = 0; j < n; j++)
            if(allocation[j][i] != 0)
            {
                flag = 1;
                break;
            }
        if(flag == 0)
        {
            deadlock = 1;
            for(int j = 0; j < n; j++)
                process[j] = 1;
        }
    }
    if(deadlock == 1)
    {
        printf("Deadlock exists\n");
        printf("The minimum no. of process whose termination ends deadlock is : ");
        for(int i = 0; i < n; i++)
            if(process[i] == 1)
                printf("%d ", i);
        printf("\n");
    }
    else
        printf("Deadlock does not exist\n");
    return 0;
}