from turtle import Turtle, Screen

screen = Screen()

screen.setup(width=800, height=600)
screen.bgcolor("black")
screen.title("Pong")
screen.tracer(0)

border = Turtle()
border.hideturtle()
border.penup()
border.color("white")
border.goto(-399, -299)  
border.pendown()
border.pensize(3)

for _ in range(4):
    border.forward(800 if _ % 2 == 0 else 600) 
    border.left(90)

border.penup()

screen.exitonclick()