#include<stdio.h>
int main(int argc, char const *argv[])
{
    int i = 1;
    while(i < argc)
    {
        if(argv[i][0]!='-')
        {
            printf("%s ",argv[i]);
        }
        i++;
    }
    return 0;
}