import numpy as np

A = np.random.uniform(1, 10, (3, 3))  
b = np.random.uniform(1, 10, 3) 
x = np.linalg.solve(A, b)

#print the equation
print("The equation is:")
print(A, "x = ", b)

print("The solution is:", x)