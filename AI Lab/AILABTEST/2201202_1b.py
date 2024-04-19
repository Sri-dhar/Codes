import collections
import re
#incliding the necessary libraries for easy io

def func(file_path):
    with open(file_path, 'r') as file:
        text = file.read()
#reading the files

#getting necessary parameters
    words = re.findall(r'\b\w+\b', text)
    lines = text.split('\n')
    spaces = text.count(' ')

    unique_words = set(words)
    word_frequency = collections.Counter(words)

    longest_word = max(words, key=len)
    average_word_length = sum(len(word) for word in words) / len(words)

#printing the necessary details
#as mentioned in the question 1b
    print(f"Total number of words: {len(words)}")
    print(f"Total number of lines: {len(lines)}")
    print(f"Total number of spaces: {spaces}")
    print(f"Number of unique words: {len(unique_words)}")
    print(f"Frequency of each word: {word_frequency}")
    print(f"Longest word: {longest_word}")
    print(f"Average word length: {average_word_length}")

#def compare_texts(text1, text2):
#    return int(text1 == text2)


def compare_texts(text1,text2):
	with open (text1,'r') as f1:
		with open (text2, 'r') as f2:
			if(f1.read() == f2.read()):
				return 1;
	return 0;

func("text.txt")
print()

if(compare_texts("text.txt","text2.txt") == 1):
	print("The two texts given are completely identical")
else : 
	print("The two texts given are not identical")


