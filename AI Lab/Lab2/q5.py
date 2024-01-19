#We are copying the content of "example.txt" to "example3.txt"
f1 = open("Python Lab/Lab2/example.txt", "r")
f2 = open("Python Lab/Lab2/example3.txt", "w")

for line in f1:
    f2.write(line)

f1.close()
print("Copied successfully")
f2.close()