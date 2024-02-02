import numpy as np
arr = np.random.rand(4,4)

print("The original array is: \n", arr)
print()

print("The second column is:")
print(arr[:, 1])

print()
print("The last row is: ")
print(arr[-1, :])