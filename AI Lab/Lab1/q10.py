def fun(listt):
    newList =[]
    for num in listt:
        if num not in newList: 
            newList.append(num)
    return newList

my_list =[1,1,2,3,5,3,1,34,43,4,42,45,34]
print("The original list is :\n",my_list)

my_list = fun(my_list)
print("The new list is :\n ",my_list)

