# file handling
file = open("file.txt", "r")
print(file.read())

# file = open("file.txt", "w")
# file.write("Hello World")
# file.close()

# file = open("file.txt", "a")
# file.write("Hello World")
# file.close()

with open("file.txt", "a") as file:
    file.write("Hello World")

# file = open("file.txt", "r")

# print(file.read())
# print(file.readline())