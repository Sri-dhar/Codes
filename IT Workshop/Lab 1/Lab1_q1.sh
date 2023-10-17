read -p "Enter filename: " filename

if [ -e "$filename" ]; then
    echo "File $filename exists. Content:"
    cat "$filename"
else
    echo "File $filename does not exist. Creating a new file..."
    touch "$filename"
fi