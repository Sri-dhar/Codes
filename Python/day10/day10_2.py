#docstrings documentation of a function
import os
os.system('clear')
def Fibonacci(n):
    '''This Function prints fibonacci series upto the number n'''
    a=0
    b=1
    if n==1:
        print(a)
    elif n==2:
        print(a,b)
    else:
        print(a,b,end=" ")
        for i in range(n-2):
            c=a+b
            a=b
            b=c
            print(b,end=" ")

Fibonacci(10)
print()
print(Fibonacci.__doc__)