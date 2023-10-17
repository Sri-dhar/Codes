read -p "Enter the C source code filename: " source_file

if [ ! -e "$source_file" ]; then
    echo "Error: File $source_file does not exist."
    exit 1
fi

output_file="${source_file%.c}"

gcc "$source_file" -o "$output_file"

echo "Compilation successful. Executable generated: $output_file"
