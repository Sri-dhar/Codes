stringg = input("Enter a string to append in the second file: ")
f = open("example2.txt", "a")
f.write(stringg)

print("\nThe content of example 2 are:")
f = open("example2.txt", "r")
print(f.read())