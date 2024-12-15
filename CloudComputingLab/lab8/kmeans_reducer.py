#!/usr/bin/env python3
import sys

current_candidate = None
count = 0
total_length = 0.0
total_width = 0.0

for line in sys.stdin:
    candidate, length, width = line.strip().split(',')
    length = float(length)
    width = float(width)

    if candidate == current_candidate:
        total_length += length
        total_width += width
        count += 1
    else:
        if current_candidate is not None:
            # Output the average for the previous candidate
            avg_length = total_length / count
            avg_width = total_width / count
            print(f"{current_candidate},{avg_length},{avg_width}")
        current_candidate = candidate
        total_length = length
        total_width = width
        count = 1

# Output for the last candidate
if current_candidate is not None:
    avg_length = total_length / count
    avg_width = total_width / count
    print(f"{current_candidate},{avg_length},{avg_width}")

