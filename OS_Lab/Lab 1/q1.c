#include<stdio.h>
int main(int argc, char const *argv[])
{
    printf(" the number of arguments is %d",argc);
    printf("\n The arguments without '-' are:\n");
    for (int i = 1; i < argc; i++)
    {
        if(argv[i][0] != '-')
            printf(" %s\n",argv[i]);
    }
}