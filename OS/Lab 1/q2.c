#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<ctype.h>
#define BUFSIZ 1024
int main(int argc, char const *argv[])
{
    int n;
    int f = open("q2.txt",O_RDONLY);
    if(f == -1)
    {
        perror("Error opening file");
        exit(1);
    }
    char buf[BUFSIZ];
    while((n = read(f,buf,BUFSIZ))>0 )
    {
        for (int i = 0; i < n; i++)
            if(!isalpha(buf[i]))
                printf("%c",buf[i]);
    }
    return 0;

    // char buf[BUFSIZ];
    // while((n = read(0,buf,BUFSIZ))>0 )
    // {
    //     for (int i = 0; i < n; i++)
    //     {
    //         if(!isalpha(buf[i]))
    //             printf("%c",buf[i]);
    //     }
    // }
    // return 0;
    // for this code the endoffile is given by ctrl+d
} 