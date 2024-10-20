#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>

//creating pipes and child processes
int pipe1[2], pipe2[2];
pid_t child1, child2;

void killl(int sig)
{
    kill(child1,SIGTERM);
    kill(child2,SIGTERM);
    printf("Child killed\n");
    printf("Getting out of Killl function\n");
    exit(0);
}

int main()
{ 
    //creating pipes and checking for errors
    if(pipe(pipe1) == -1)
    {
        fprintf(perror, "Creation of pipe 1 failed");
        exit(0);
    }
    if(pipe(pipe2) == -1)
    {
        fprintf(perror,"creation of pipe 2 failed");
        exit(0);
    }

    if((child1 = fork()) == -1)
    {
        fprintf(perror,"forking failed");
        exit(0);
    }

    char pipe_char;

    if(child1 == 0)
    {
        close(pipe1[0]);
        while(1)
        {
            pipe_char = getchar();
            if(pipe_char == EOF)
            {   
                //calling sigpipe signals to kill the child process
                signal(SIGPIPE,killl);
                puts("THe program is terminated due to EOF ");
                char *args[] = {"exit",  NULL};
                execv("/bin/", args);
            }
            write(pipe1[1],&pipe_char,sizeof(char));
        }
    }
    
    //fork failed error messages
    //not compulsary

    if((child2 = fork())== -1)
    {
        fprintf(perror,"forking failed");
        exit(0);
    }

    if(child2 == 0)
    {
        close(pipe1[1]);
        close(pipe2[0]);
        while(1)
        {
            read(pipe1[0],&pipe_char,sizeof(char));
            pipe_char++;
            //incrementing as given in the question
            write(pipe2[1],&pipe_char,sizeof(char));
        }
    }


    signal(SIGPIPE,killl);
    close(pipe1[1]);
    close(pipe2[1]);

    while(1)
    {
        int a = read(pipe2[0],&pipe_char,sizeof(char));
        if(a<0)
        {
            fprintf(perror,"Reading from pipe 2's read end was not feasible");
            raise(SIGPIPE);
        }
        pipe_char--;
        //decrementing as given 
        char temp = pipe_char+1;
        if(temp == EOF)
        {
            printf("The program ends by EOF");
            signal(SIGPIPE,killl);
        }    
        if(pipe_char != EOF)
            putchar(pipe_char);

    }


    printf("The program ends here");
    return 0;
    
}

