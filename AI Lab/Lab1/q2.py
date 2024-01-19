a = 5
b = 10
print("Before swap (with temp variable): a =", a, "b =", b)

temp = a
a = b
b = temp
print("After swap (with temp variable): a =", a, "b =", b)

a = 5
b = 10
print("Before swap (without temp variable): a =", a, "b =", b)

a, b = b, a
print("After swap (without temp variable): a =", a, "b =", b)