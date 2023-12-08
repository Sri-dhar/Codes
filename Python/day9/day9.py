# #Dictionaries and Nesting

# programming_dictionary = {"Bug": "An error in a program that prevents the program from running as expected."}
# print(programming_dictionary["Bug"])

# a dictionary can be created by using the dict() function
Diction = dict()
print(Diction)
Diction.update({1:"one", 2:"two", 3:"three"})
print(Diction[2])

# adding new items to dictionary
Diction[4] = "four"
print(Diction)

# updating items in dictionary
Diction[4] = "Five"
print(Diction)

# deleting items from dictionary
del Diction[4]
print(Diction)

# looping through dictionary
# for key, value in Diction.items():
#     print(key, value)

for key in Diction:
    print(f"{key},{Diction[key]}")

for key, value in Diction.items():
    print(key, value)