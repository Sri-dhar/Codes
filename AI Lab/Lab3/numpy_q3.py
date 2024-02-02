import numpy as np  

arr = np.random.randint(1, 8, (5, 6))
print("The Matrix is :")
print(arr)

print("\nThe frequency array is :")

unique, counts = np.unique(arr, return_counts=True)
freq = np.asarray((unique, counts)).T
print(freq)