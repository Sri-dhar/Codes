#lists here

list1 = [0,1,2,3,4,5,6,7,8,9,10]
list2 = ["a","b","c","d","e","f","g","h","i","j"]
#write all the ways to create a list
list3 = list()
list4 = []
list5 = list1 + list2

list6 = [list1,list2]
list7 = [x**2 for x in list1]
print(list7)
list8 = [x**2 for x in range(1,14) if x%2 == 0] 
print(list8)

print(list1[0])

print(list1[-1])
print(list1[2:4]) #4 is not included
print(list1[2:]) #from 2 to the end
print(list1[:4]) #from 0 to 4
print(list1[-4:-1]) #from -4 to -1
print(list1[::2]) #from 0 to the end with a step of 2
print(list1[::-1]) #from the end to 0 with a step of -1
print("=======================================")
#list Methods
print(list1)
list1.append(11)
print(list1)
list1.extend(list2)
print(list1)

listx =list();
listx.append(1)
listx.append(2)
listx.append(3)
print(listx)

listx.insert(1,4)
listx.extend([5,6,7])
print(listx)
listx.remove(7)  #remove the first occurance of 7
listx.pop() #remove the last element
listx.pop(1) #remove the element at index 1
print(f"The index of first occurance of 3 is at index  {listx.index(3)}") #return the index of the first occurance of 3
listx.reverse()
print(listx)
listx.sort()
print("Listx sorted using listx.sort()")
print(listx)
listx.sort(reverse=True)
print("Listx sorted using listx.sort(reverse=True)")
print(listx)

aaaa= listx.index(2,1,3) #return the index of the first occurance of 4 between index 1 and 3 including 1 and 3
print(f"The occurace of 2 between index 1 and 3 including 1 and 3 is : {aaaa}")


print("=======================================")
#string methods of lists
stringg = " hello how are you , johhny"
listStr = stringg.split()
print(listStr)
listStr2 = stringg.split(",")
print(listStr2)


print(list.__len__(list1))
print(list1.__len__())
print(len(list1))
