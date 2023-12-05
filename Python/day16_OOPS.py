#Classes and their attributes

# class Car:
#     def __init__(self, speed, color, fuel):
#         self.speed = speed
#         self.color = color


import turtle

timmy = turtle.Turtle()
for i in range(4):
    timmy.forward(100)
    timmy.right(90)
# Move the turtle forward by 100 units
timmy.forward(100)
# Turn the turtle right by 90 degrees
timmy.right(90)

timmy.shape("turtle")
timmy.color('cyan3')
# Move the turtle forward by 100 units
timmy.forward(100)

turtle.done()

