import numpy as np

scores = np.array([85, 92, 75, 85, 90, 92, 85, 75, 85, 92, 75, 85, 90, 92, 85, 75, 85, 92])
frequency = np.count_nonzero(scores == 85)

print("The frequency of the score 85 is:", frequency)