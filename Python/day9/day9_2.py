#Nesting Lists and Dictionaries
MyDict = dict()

List = list()
List.append([1,3,43,45,3452,52345,23,234])
#List contains a list of numbers
MyDict.update({1:List})
#MyDict contains 1 paired with a list of list of numbers
print(MyDict)

print("=====================================")

# #Nesting Dictionaries in a Dictionary
MyDict = dict()
MyDict.update({1:{"Name":"John", "Age": 23}})
print(MyDict[1]["Age"])


travel_log = [
    {"France": {"cities_visited": ["Paris", "Lille", "Dijon"], "total_visits": 12}},
    {"Germany": {"cities_visited": ["Berlin", "Hamburg", "Stuttgart"], "total_visits": 5}},

]

print(travel_log[1]["Germany"]["cities_visited"][2])

