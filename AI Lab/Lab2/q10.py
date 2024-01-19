import numpy as np
import random

ROW = 4
COL = 5

matrix = [[0 for i in range(COL)] for j in range(ROW)]
for i in range(ROW):
    for j in range(COL):
        matrix[i][j] = random.randint(1, 20)

print("The matrix created is : ")
for i in range(ROW):
    for j in range(COL):
        print(matrix[i][j], end=" ")
    print()

final_arr =[]
arr = np.zeros(10)
final_arr = np.append(final_arr, arr)

arr = np.ones(10)
final_arr = np.append(final_arr, arr)

arr = np.ones(10) * 5
final_arr = np.append(final_arr, arr)

print()
print("The arr of 10 zeros, 10 ones, 10 fives is:")
print(final_arr)




print()
print("Array of even: ")
arr = np.arange(10, 51, 2)
print(arr)

print()
print("Random number between 0 and 1: ")
num = np.random.rand(1)
print(num)


print()

print("Random matrix of 5X4: ")
ROW = 5
COL = 4

matrix = [[0 for i in range(COL)] for j in range(ROW)]
for i in range(ROW):
    for j in range(COL):
        matrix[i][j] = random.randint(1, 10)

print("The matrix created is : ")
for i in range(ROW):
    for j in range(COL):
        print(matrix[i][j], end=" ")
    print()

f = open("AI Lab/Lab2/matrix.txt", "w")
for i in range(ROW):
    for j in range(COL):
        f.write(str(matrix[i][j]) + " ")
    f.write("\n")
f.close()

print()
print("Matrix loaded from file: ")
arr = np.loadtxt("AI Lab/Lab2/matrix.txt")
print(arr)

