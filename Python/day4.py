# Randomization and Lists
# askpython.com

import random
import day4myModule

a = random.randint(1, 10)  # random integer between 1 and 10 inclusive
print(a)
print(day4myModule.b)

random_float = random.random()  # random float between 0 and 1
print(random_float)  # doesn't include 1
random_float = random.random() * 5  # random float between 0 and 5
print("{:.2f}".format(random_float))

list1 = ["sridhar", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J"]
print(random.choice(list1))  # randomly choose one element from the list
print(random.choice(list1))  # randomly choose one element from the list

print("=======================================")
listA = ["$", "$", "$"]
listB = ["$", "$", "$"]
listC = ["$", "$", "$"]

map = [listA, listB, listC]
print(f"{listA}\n{listB}\n{listC}")

position = input("Where do you want to put the treasure? ")
inputRow = int(position[0])
inputCol = int(position[1])
map[inputRow-1][inputCol-1] = "X"
print(f"{listA}\n{listB}\n{listC}")