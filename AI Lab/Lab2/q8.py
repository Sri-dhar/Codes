import random
sizeOfArr1 = random.randint(1, 10)
sizeOfArr2 = random.randint(1, 10)
arr1 = []
arr2 = []
for i in range(sizeOfArr1):
    arr1.append(random.randint(1, 20))
for i in range(sizeOfArr2):
    arr2.append(random.randint(1, 20))

print("Array 1: ", arr1)
print("Array 2: ", arr2)

print("The concat of two arrays is : ")
arr_concat = arr1 + arr2
print(arr_concat)
print()

print("Both arrays sorted are :")
arr1.sort()
arr2.sort()
print("Array 1: ", arr1)
print("Array 2: ", arr2)
print()

print("The addition of two arrays is : ")
arr_add = []
for i in range(min(len(arr1),len(arr2))):
    arr_add.append(arr1[i]+arr2[i])
print(arr_add)
print()

print("The substraction of two arrays is : ")
arr_sub = []
for i in range(min(len(arr1),len(arr2))):
    arr_sub.append(arr1[i]-arr2[i])
print(arr_sub)
print()


print("The multiplication of two arrays is : ")
arr_mul = []
for i in range(min(len(arr1),len(arr2))):
    arr_mul.append(arr1[i]*arr2[i])
print(arr_mul)
print()


print("The division of two arrays is : ")
arr_div = []
for i in range(min(len(arr1),len(arr2))):
    arr_div.append(arr1[i]/arr2[i])
print(arr_div)
print()

