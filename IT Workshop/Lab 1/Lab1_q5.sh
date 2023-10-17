read -p "Enter filename: " filename

if [ ! -e "$filename" ]; then
    echo "Error: File $filename does not exist."
    exit 1
fi

read -p "Enter the word to find its frequency: " word

grep -o -i "$word" "$filename" | wc -l
