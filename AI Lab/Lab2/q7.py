import numpy as np
a = np.array([[10,16,71,9],[71,91,31,51]])

if a.shape[0] == a.shape[1]:
    print("Square matrix")
else:
    print("Rectangle matrix")
print(f"The dimension of array is : {a.ndim}")
print(f"The shape of a is : {a.shape}")
print(f"The size of a is : {a.size}")