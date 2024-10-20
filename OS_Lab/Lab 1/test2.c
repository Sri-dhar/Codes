#include<fcntl.h>
#include<stdio.h>
#define BUFSIZ 1024
int main()
{
    int f;
    f = creat("test.txt", O_RDWR);
    char buf[BUFSIZ];
    int n;
    while ((n = read(f, buf, BUFSIZ)) > 0)
    {
        int a = write(f, buf, n);
        if(a != n)
            printf("write error");
    }

}