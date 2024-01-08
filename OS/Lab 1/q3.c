#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<ctype.h>
#define BUFSIZ 1024
int main(int argc, char const *argv[])
{
    int n;
    int f = open("q3.txt",O_RDONLY);
    if(f == -1)
    {
        perror("Error opening file");
        exit(1);
    }
    char buf[BUFSIZ];
    while((n = read(f,buf,BUFSIZ))>0 )
    {
        for (int i = 0; i < n; i++)
        {
            if(islower(buf[i]))
                printf("%c",toupper(buf[i]));
            else if(isupper(buf[i]))
                printf("%c",tolower(buf[i]));
            else
                printf("%c",buf[i]);
        }
    }
    close(f);
    return 0;
}