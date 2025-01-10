#!/bin/bash

# Define the input and output files
LEX_FILE="example.l"
C_FILE="lex.yy.c"
OUTPUT_FILE="lexer"

# Check if the Lex file exists
if [ ! -f "$LEX_FILE" ]; then
    echo "Error: $LEX_FILE not found!"
    exit 1
fi

# Step 1: Generate the C code from the Lex file
echo "Running lex on $LEX_FILE..."
lex $LEX_FILE
if [ $? -ne 0 ]; then
    echo "Error: Lex failed to generate $C_FILE"
    exit 1
fi

# Step 2: Compile the generated C code
echo "Compiling $C_FILE..."
gcc $C_FILE -o $OUTPUT_FILE -lfl
if [ $? -ne 0 ]; then
    echo "Error: Compilation failed"
    exit 1
fi

# Step 3: Run the lexer
echo "Running $OUTPUT_FILE..."
echo "Enter your input (Ctrl+D to finish):"
./$OUTPUT_FILE

# Cleanup (optional)
echo "Cleaning up temporary files..."
rm -f $C_FILE $OUTPUT_FILE
