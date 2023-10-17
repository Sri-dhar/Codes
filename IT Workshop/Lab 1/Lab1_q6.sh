read -p "Enter the current filename: " old_filename

if [ ! -e "$old_filename" ]; then
    echo "Error: File $old_filename does not exist."
    exit 1
fi

read -p "Enter the new filename: " new_filename

mv "$old_filename" "$new_filename"

echo "File renamed from $old_filename to $new_filename"
