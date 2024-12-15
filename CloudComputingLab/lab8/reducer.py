#!/usr/bin/env python3
import sys

current_word = None
current_count = 0

for line in sys.stdin:
    # Split line into word and count, handling unexpected formats
    try:
        word, count = line.strip().split(',', 1)
        count = int(count)  # Convert count to an integer
    except ValueError:
        # Skip lines that do not have the expected format
        continue

    # Aggregate counts for each word
    if word == current_word:
        current_count += count
    else:
        if current_word:
            # Output the count for the previous word
            print(f"{current_word},{current_count}")
        current_word = word
        current_count = count

# Output the last word's count
if current_word:
    print(f"{current_word},{current_count}")

        
#sudo docker run -it --name hadoop-container apache/hadoop:2.10.2 /bin/bash
#hdfs dfs -mkdir -p /user/root