import turtle

mike = turtle.Turtle()
mike.shape("turtle")
mike.pensize(2)
mike.speed(100)

screen = mike.getscreen()
screen.colormode(255)

colors = ["red", "orange", "blue", "green", "blue", "purple"]

for i in range(36):
    mike.color(colors[i % 6])
    mike.circle(100)
    mike.left(10)

screen.exitonclick()