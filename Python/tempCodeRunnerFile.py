
print("=======================================")
listA = ["$", "$", "$"]
listB = ["$", "$", "$"]
listC = ["$", "$", "$"]

map =print(f"{listA}\n{listB}\n{listC}")

position = input("Where do you want to put the treasure? ")
inputRow = int(position[0])
inputCol = int(position[1])
map[inputRow-1][inputCol-1] = "X"
print(f"{listA}\n{listB}\n{listC}")