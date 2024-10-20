#include<stdio.h>

void pill(int start, int target)
{
    int operations=0;
    
    if (start==target)
    printf("no of operations required = 0");
    
    if (start==0 && target>0)
    printf("no operation is possible");
    
    if (start<0 && target>0)
        printf("enter valid starting and target value");

    while(start>0 && target>0 && target!=start)
    {
        if (target<start)
        {
        target++;
        operations++;
        }
        
        else
        {
            if (target%2==0)
            {
                target=target/2;
                operations++;
            }
            else
            {
                target++;
                operations++;
            }
        }
    }
    
   while(start>0 && target<0 && target!=start)
   {
       while(start>=-1)
       {
           start=start-1;
           operations++;
       }
   }
    
    int target1=target;
    
    while(start<0 && target<0 && target!=start)
    {   
        if (target1>start)
        {printf("not possible\n");
        break;}
        
        else
        {
            if (target/2>start)
           {
               start--;
            operations++;
           }
           
           else{
            if (target%2==0)
            {
                target/=2;
                operations++;
            }
            else
            {
                target++;
                operations++;
            }
           }
        }
    }
    
    if (operations>0)
    printf("minimum number of operations required is %d", operations);
}

int main()
{
    int a, b;
    printf("enter starting value: ");
    scanf("%d", &a);
    printf("enter target value: ");
    scanf("%d", &b);
    pill(a, b);
}