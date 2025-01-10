#!/usr/bin/env python3
import sys
import math

# Candidate points (hard-coded)
candidates = [
    (5.8, 4.0),  # Iris-setosa
    (6.1, 2.8),  # Iris-versicolor
    (6.3, 2.7)   # Iris-virginica
]

# Function to calculate Euclidean distance
def euclidean_distance(x1, y1, x2, y2):
    return math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)

for line in sys.stdin:
    parts = line.strip().split(',')
    if len(parts) < 2:
        continue
    try:
        sepal_length, sepal_width = float(parts[0]), float(parts[1])
    except ValueError:
        continue

    # Find nearest candidate
    nearest_candidate = None
    min_distance = float('inf')
    for i, (c_length, c_width) in enumerate(candidates):
        dist = euclidean_distance(sepal_length, sepal_width, c_length, c_width)
        if dist < min_distance:
            min_distance = dist
            nearest_candidate = i

    # Output candidate index and data point
    print(f"{nearest_candidate},{sepal_length},{sepal_width}")

