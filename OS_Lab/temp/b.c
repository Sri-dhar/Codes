#include<stdio.h>
#include<unistd.h>
int main()
{
    fork();
    if(fork()&&fork())
    {
        printf("hii ");
    }
    printf("1 ");
}