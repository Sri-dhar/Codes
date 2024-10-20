#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
pid_t pid;

pid = fork();
if (pid < 0) { /* error occurred */
printf("Fork Failed");
return 1;
}
else if (pid == 0) { /* child process */
execlp("./test","test", NULL);
}
else { /* parent process */
/* parent will wait for the child */
wait (NULL);
printf ("Child Complete");
}

return 0;}