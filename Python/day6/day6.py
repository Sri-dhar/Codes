#Function CodeBlocks and Scope and Indentation 

def my_function():
    print("Hello from a function")

my_function()

def my_function2(fname):
    print(fname + " Refsnes")

my_function2("Emil") #Emil is the argument

def my_function3(fname, lname):
    print(fname + " " + lname)

my_function3("Emil", "Refsnes")

def my_function4(*kids):
    print("The youngest child is " + kids[2])

my_function4("Emil", "Tobias", "Linus")

def my_function5(*nums):
    print(nums[2])

testList = [1,23,2345,324]
my_function5(*testList)  # Unpack the list using the * operator

i = 3
j = 5
while not i>5:
    print(i)
    i += 1

