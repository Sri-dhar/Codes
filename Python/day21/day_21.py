#inheritance
class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age
    def myfunc(self):
        print("Hello my name is " + self.name)

class Student(Person):
    def __init__(self, name, age):
        super().__init__(name, age)
        self.graduationyear = 2019
    def welcome(self):
        print("Welcome", self.name, "to the class of", self.graduationyear)

x = Student("Mike", 21)
x.welcome() 
#Python Iterators
mytuple = ("apple", "banana", "cherry")
myit = iter(mytuple)
print(next(myit))
print(next(myit))
print(next(myit))
print()
#Looping Through an Iterator
mytuple = ("apple", "banana", "cherry")
for x in mytuple:
    print(x)

print()
#Create an Iterator
class MyNumbers:
    def __iter__(self):
        self.a = 1
        return self
    def __next__(self):
        x = self.a
        self.a += 1
        return x**2
myclass = MyNumbers()
myiter = iter(myclass)
print(next(myiter))
print(next(myiter))
print(next(myiter))

print()

#StopIteration
class MyNumbers:
    def __iter__(self):
        self.a = 1
        return self
    def __next__(self):
        if self.a <= 20:
            x = self.a
            self.a += 1
            return x**2
        else:
            raise StopIteration
myclass = MyNumbers()
myiter = iter(myclass)
for x in myiter:
    print(x)
print()
