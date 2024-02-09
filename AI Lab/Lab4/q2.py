import random

list = [random.randint(1, 20) for i in range(20)]
print(list)
input = int(input("Enter the element to find its occurences: "))
print(f"The element {input} occurs {list.count(input)} times in the list at the following indices")
print(f"{[i for i, x in enumerate(list) if x == input]}")


#using a custom count Occurences function

def countOccurences(list, input):
    countt = 0
    for i in range(len(list)):
        if list[i] == input:
            countt += 1
    
    return countt

print(f"The element {input} occurs {countOccurences(list, input)} times in the list at the following indices")