read -p "Enter the directory name containing C source code files: " source_directory

if [ ! -d "$source_directory" ]; then
    echo "Error: Directory $source_directory does not exist."
    exit 1
fi

mkdir -p bin

find "$source_directory" -name "*.c" -type f -print0 | while IFS= read -r -d '' source_file; do
    output_file="bin/$(basename "${source_file%.c}")"
    gcc "$source_file" -o "$output_file"
    echo "Compiled $source_file -> $output_file"
done

echo "Compilation of C files in $source_directory and its subdirectories completed."
