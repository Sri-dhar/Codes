import turtle

mike = turtle.Turtle()
mike.shape("turtle")
mike.pensize(2)
mike.speed(100)

screen = mike.getscreen()
screen.colormode(255)

#for circle
for i in range(360):
    tem = i+1
    mike.forward(10)
    mike.rt(tem)

mike.hideturtle()

screen.exitonclick()