from turtle import Turtle, Screen
from random import randint

mike = Turtle()
mike.shape("turtle")
mike.pensize(2)
mike.speed(0)

def moveForward():
    mike.forward(10)

def moveBackward():
    mike.backward(10)

def turnLeft():
    mike.left(10)

def turnRight():
    mike.right(10)

def clearScreen():
    mike.clear()
    mike.penup()
    mike.home()
    mike.pendown()

screen = Screen()
screen.listen()
screen.onkey(moveForward, "Up")
screen.onkey(moveBackward, "Down")
screen.onkey(turnLeft, "Left")
screen.onkey(turnRight, "Right") 
screen.onkey(clearScreen, "Return")

screen.exitonclick()