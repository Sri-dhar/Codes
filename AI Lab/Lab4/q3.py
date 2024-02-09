import random

list = [random.randint(1, 20) for i in range(20)]
print(list)

print(f"The odd numbers in the list are/is ")
print(f"{[i for i in list if i % 2 != 0]}")

print()
print(f"The even numbers in the list are/is ")
print(f"{[i for i in list if i % 2 == 0]}")

def isPrime(n):
    if n <= 1:
        return False
    for i in range(2, n):
        if n % i == 0:
            return False
    return True

print()
print(f"The prime numbers in the list are/is ")
print(f"{[i for i in list if isPrime(i)]}")

print()
print(f"The composite numbers in the list are/is ")
print(f"{[i for i in list if not isPrime(i)]}")
