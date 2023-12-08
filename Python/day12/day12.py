# a = 23;

# def valueChanger(a):
#     a+= 2
#     print(a)


# valueChanger(a)
# print(f"Value of a outside is {a}")
a = 23

def valueChanger():
    global a
    a += 2
    print(a)

valueChanger()

print(f"Value of a outside is {a}")


#functions and its scope , block scope , etc