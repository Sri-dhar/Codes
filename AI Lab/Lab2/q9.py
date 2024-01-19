import random

ROW = 8
COL = 7

matrix = [[0 for i in range(COL)] for j in range(ROW)]
for i in range(ROW):
    for j in range(COL):
        matrix[i][j] = random.randint(1, 10)

print("The matrix is : ")
for i in range(ROW):
    for j in range(COL):
        print(matrix[i][j], end=" ")
    print()

    
for i in range(COL):
    max = matrix[0][i]
    min = matrix[0][i]
    for j in range(ROW):
        if matrix[j][i] > max:
            max = matrix[j][i]
        if matrix[j][i] < min:
            min = matrix[j][i]
    print("\nMax of COL:", i, " = ", max,"|| Min of COL:", i, " = ", min,end=" ")
    print()



