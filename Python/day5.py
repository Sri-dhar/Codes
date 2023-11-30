fruits = ["apple", "banana", "cherry"]  
for x in fruits:
    print(x)

#different ways to run a for loops in python
#1. for x in fruits:
#2. for x in range(6):
#3. for x in range(2, 6):
#4. for x in range(2, 30, 3):
#5. for x in range(len(fruits)):

for x in range(6):
    print(x)

print("************")

for x in range(2, 6):
    print(x)

print("************")

for x in range(2, 30, 3):
    print(x)

print("************")

fruits = ["apple", "banana", "cherry"]
for x in range(len(fruits)):
    print(x)


print("************")

for x in range(2, 30, 3):
    print(x)


print("************")

listofSquares =[x**2 for x in range(4,15)]
print("max and min is : ")
print(max(listofSquares))
print(min(listofSquares))

print("************")

sum = 0;
for x in range(1,101):
    sum += x
print(f"The sum of numbers from 1 to 100 is {sum}")


print("************")


#reordering a list
fruits = ["apple", "banana", "cherry", "kiwi", "mango"]
newlist = []
import random
random.shuffle(fruits)
print(fruits)

