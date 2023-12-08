import math
# print(math.factorial(int(input("Enter a number: "))))
# print(math.sqrt(int(input("Enter a number: "))))    
# print(math.ceil(float(input("Enter a number: "))))

#prime no. checker
def prime(n):
    if(n==1): return False
    for i in range(2,int(math.sqrt(n))):
        if(n%i==0): return False
    return True

print(prime(int(input("Enter a number: "))))