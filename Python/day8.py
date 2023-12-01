#Functions
def fibo(n): 
    if n == 0:
        return 0
    if n == 1:
        return 1
    elif n > 1:
        return fibo(n-1) + fibo(n-2)
    else:
        return -1

for i in range(int(input("Enter a number: "))):
    print(fibo(i)   )