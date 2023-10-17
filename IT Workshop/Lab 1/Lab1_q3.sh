#!/bin/bash

read -p "Enter filename: " filename

if [ ! -e "$filename" ]; then
    echo "Error: File $filename does not exist."
    exit 1
fi

char_count=$(wc -m < "$filename")
word_count=$(wc -w < "$filename")
line_count=$(wc -l < "$filename")

echo "Total characters: $char_count"
echo "Total words: $word_count"
echo "Total lines: $line_count"