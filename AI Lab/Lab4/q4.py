import random

list = [random.randint(1,30) for i in range(20)]
list2 = [random.randint(1,30) for i in range(20)]

print("List 1: ", list)
print("List 2: ", list2)

list_final = [max(list[i], list2[i]) for i in range(20)]

print("The final list is: ", list_final)