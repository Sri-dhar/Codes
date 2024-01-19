n = int(input("Enter the value of n (rows): "))
m = int(input("Enter the value of m (columns): "))

matrix = [[0 for i in range(m)] for j in range(n)]

for i in range(n):
    row_input = input(f"Enter space-separated values for row {i+1}: ")
    row_values = list(map(int, row_input.split()))
    matrix[i] = row_values


print("\nThe matrix you entered is : ")
for i in range(n):
    for j in range(m):
        print(matrix[i][j],end=" ")
    print()

transpose_matrix = [[0 for i in range(n)] for j in range(m)]

for i in range(n):
    for j in range(m):
        transpose_matrix[j][i] = matrix[i][j]

print("\nThe transpose matrix is : ")
for i in range(m):
    for j in range(n):
        print(transpose_matrix[i][j],end=" ")
    print()

print()
print("The flattened matrix is : ")

flat_matrix = []

for i in range(n):
    for j in range(m):
        flat_matrix.append(matrix[i][j])

print(flat_matrix)



# import numpy as np
# n = int(input("Enter n: "))
# m = int(input("Enter m: "))
# arr = list(map(int, input().split()))
# arr = np.array(arr)
# arr = arr.reshape(n,m)
# print(arr.transpose())
# print(arr.flatten())