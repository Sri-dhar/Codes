person = { 'first_name': 'John','last_name': 'Doe','age': 25,
'favorite_colors': ['blue', 'green'],'active': True}

print("Person: ",person)

print()

for key in person:
    print("Key: ",key)
    print("Value: ",person[key])

print()

i=0;
for key in person:
    i += 1
    if(i == 2):
        print("Value of second key: ",person[key])
        break;


