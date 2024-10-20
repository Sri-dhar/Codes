#include <fcntl.h>
#define BUFSIZ 1024
main()
{
    char buf[BUFSIZ];
    int n;
    while ((n = read(0, buf, BUFSIZ)) > 0)
    {
        int a = write(1, buf, n);
        if(a != n)
            printf("write error");
    }
        
}