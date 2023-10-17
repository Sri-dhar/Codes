read -p "Enter filename: " filename

if [ ! -e "$filename" ]; then
    echo "Error: File $filename does not exist."
    exit 1
fi

while IFS= read -r line; do
    echo "$line"
done < "$filename"