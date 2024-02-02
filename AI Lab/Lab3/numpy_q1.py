import numpy as np
import time

P = np.random.rand(106, 104)
Q = np.random.rand(106, 104)

Q_transpose = np.transpose(Q)

result = np.zeros((106, 106))

start_time1 = time.time()

for i in range(106):
    for j in range(104):  
        for k in range(106):  
            result[i][k] += P[i][j] * Q_transpose[j][k]

end_time1 = time.time()

print("Time taken by loop-based matrix multiplication: ", end_time1 - start_time1)

start_time2 = time.time()
result_vector = np.dot(P, Q_transpose)
end_time2 = time.time()

print("Time taken by vectorized matrix multiplication: ", end_time2 - start_time2)

print(f"The speedup is : {((end_time1 - start_time1) / (end_time2 - start_time2)):.2f} times faster.")