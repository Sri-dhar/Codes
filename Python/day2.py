str = "Hello World!"
lee = "23425"
print(len(str)) # 12
print(str[0])  # "H"    
a = str[3]
print(a) # "l"
a = str[0:5]
print(a) # "Hello"
bb = True
cc = False
pie = 3.14_159_265_358
print(pie)
no_of_chars = 43;
# # no_of_chars = len(input("What is your name? "))
# print(no_of_chars)
# print(type(no_of_chars))

# # print("The number is : "+ no_of_chars);  #invalid use of string with float
# abc = str(no_of_chars)  # Fix: Remove the parentheses after 'str'
# print("The number is : " + abc)  # Fix: Concatenate the strings correctly

#observation
#what ever text you select in python code
#VSCOde only executes that portion only

#we can use str() int() float() for type conversion

#order of arithmetic operators is  as following : 
# PEMDAS
# parentheis exponentiation (multiplication division) (addition substraction)
# in case of equal precedence we move from (left to right)

abb = 3.34523
ahh = round(abb,2)  #rounds to 1 decimal place
print(ahh)

print (8//3) #floor division prints 2
print(type(8//3)) #int
print(type(8/3)) #float

# fstring
j = 43;
jj = 43.3445
jjj = "hello"
ji = True

print(f"the number is {j+jj} and {jj} and {jjj} and {ji}")

print("{:.2f}".format(3.14159))
#prints upto 2 decimal places

