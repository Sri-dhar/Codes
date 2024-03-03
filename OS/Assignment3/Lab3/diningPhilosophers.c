#include <stdio.h>

#define NUM_PHILOSOPHERS 5

int completedEating = 0, i;

struct fork
{
    int inUse;
} ForkAvailable[NUM_PHILOSOPHERS];

struct philosopher
{
    int leftFork;
    int rightFork;
} PhilosopherStatus[NUM_PHILOSOPHERS];

void eatDinner(int philosopherID)
{
    if (PhilosopherStatus[philosopherID].leftFork == 10 && PhilosopherStatus[philosopherID].rightFork == 10)
        printf("Philosopher %d has finished eating\n", philosopherID + 1);
    else if (PhilosopherStatus[philosopherID].leftFork == 1 && PhilosopherStatus[philosopherID].rightFork == 1)
    {
        printf("Philosopher %d has finished eating\n", philosopherID + 1);

        PhilosopherStatus[philosopherID].leftFork = PhilosopherStatus[philosopherID].rightFork = 10;
        int otherFork = philosopherID - 1;

        if (otherFork == -1)
            otherFork = (NUM_PHILOSOPHERS - 1);

        ForkAvailable[philosopherID].inUse = ForkAvailable[otherFork].inUse = 0;
        printf("Philosopher %d put down fork %d and fork %d\n", philosopherID + 1, philosopherID + 1, otherFork + 1);
        completedEating++;
    }
    else if (PhilosopherStatus[philosopherID].leftFork == 1 && PhilosopherStatus[philosopherID].rightFork == 0)
    {
        if (philosopherID == (NUM_PHILOSOPHERS - 1))
        {
            if (ForkAvailable[philosopherID].inUse == 0)
            {
                ForkAvailable[philosopherID].inUse = PhilosopherStatus[philosopherID].rightFork = 1;
                printf("Fork %d picked up by philosopher %d\n", philosopherID + 1, philosopherID + 1);
            }
            else
            {
                printf("Philosopher %d is waiting for fork %d\n", philosopherID + 1, philosopherID + 1);
            }
        }
        else
        {
            int dupPhilosopherID = philosopherID;
            philosopherID -= 1;

            if (philosopherID == -1)
                philosopherID = (NUM_PHILOSOPHERS - 1);

            if (ForkAvailable[philosopherID].inUse == 0)
            {
                ForkAvailable[philosopherID].inUse = PhilosopherStatus[dupPhilosopherID].rightFork = 1;
                printf("Fork %d picked up by Philosopher %d\n", philosopherID + 1, dupPhilosopherID + 1);
            }
            else
            {
                printf("Philosopher %d is waiting for Fork %d\n", dupPhilosopherID + 1, philosopherID + 1);
            }
        }
    }
    else if (PhilosopherStatus[philosopherID].leftFork == 0)
    {
        if (philosopherID == (NUM_PHILOSOPHERS - 1))
        {
            if (ForkAvailable[philosopherID - 1].inUse == 0)
            {
                ForkAvailable[philosopherID - 1].inUse = PhilosopherStatus[philosopherID].leftFork = 1;
                printf("Fork %d picked up by philosopher %d\n", philosopherID, philosopherID + 1);
            }
            else
            {
                printf("Philosopher %d is waiting for fork %d\n", philosopherID + 1, philosopherID);
            }
        }
        else
        {
            if (ForkAvailable[philosopherID].inUse == 0)
            {
                ForkAvailable[philosopherID].inUse = PhilosopherStatus[philosopherID].leftFork = 1;
                printf("Fork %d picked up by Philosopher %d\n", philosopherID + 1, philosopherID + 1);
            }
            else
            {
                printf("Philosopher %d is waiting for Fork %d\n", philosopherID + 1, philosopherID + 1);
            }
        }
    }
    else
    {
    }
}

int main()
{
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
        ForkAvailable[i].inUse = PhilosopherStatus[i].leftFork = PhilosopherStatus[i].rightFork = 0;

    while (completedEating < NUM_PHILOSOPHERS)
    {
        for (i = 0; i < NUM_PHILOSOPHERS; i++)
            eatDinner(i);
        printf("\nSo far, %d philosophers have finished eating\n\n", completedEating);
    }

    return 0;
}