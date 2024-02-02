import numpy as np

A = np.random.randint(1, 10, (3, 3))  
B = np.random.randint(1, 10, 3) 
x = np.linalg.solve(A, B)

print("The equation is:")
print(A, "x = ", B)

print("The solution is:", x)