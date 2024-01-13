my_list = ['AI','DBMS','OS','Optimization','Algorithms','ML']
print("Original list: ", my_list)

print("Elements from 3rd to end: ", my_list[2:])
mid = len(my_list) // 2
my_list.insert(mid, 40)
my_list.append(100)
print("List after inserting : ", my_list)

print("3rd, 4th, and 5th elements: ", my_list[2:5])