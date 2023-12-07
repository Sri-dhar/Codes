import turtle

mike = turtle.Turtle()
mike.shape("turtle")
mike.pensize(2)
mike.forward(100)
mike.speed(1)

screen = mike.getscreen()
screen.colormode(255)
screen.exitonclick()

#for circle
for i in range(360):
    mike.forward(1)
    mike.rt(1)