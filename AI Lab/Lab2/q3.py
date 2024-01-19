stringg = input("Enter a string to append in the second file: ")
f = open("Python Lab/Lab2/example2.txt", "a")
f.write(stringg)

print("\nThe content of example 2 are:")
f = open("Python Lab/Lab2/example2.txt", "r")
print(f.read())