f = open("AI Lab/Lab2/text.txt", "r")
count = 0
for line in f:
    if line[0] != 'T':
        count += 1

print(f"The no. of lines that dont start with T are : {count}")
print("The lines that dont start with T are :\n ")

f = open("AI Lab/Lab2/text.txt", "r")
for line in f:
    if line[0] != 'T':
        print(line, end="")

f.close()