#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#define MSGSIZE 12 
  
int main() 
{ 
    char inbuf[MSGSIZE]; 
    int p[2], pid, nbytes; 
  char msg1[] = "Hello IIITG"; 
    if (pipe(p) < 0) 
        exit(1); 
  
    
    if ((pid = fork()) > 0) { 
     //close(p[0]);
        
        write(p[1], msg1, MSGSIZE); 
        
                wait(NULL); 
    } 
  
    else { 
       // close(p[1]);
		read(p[0], inbuf, MSGSIZE); 
            printf("%s\n", inbuf); 


 		 
        printf("Finished reading\\n"); 
    } 
    return 0; 
} 