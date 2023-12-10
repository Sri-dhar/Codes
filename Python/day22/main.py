from turtle import Turtle, Screen
from paddle import Paddle
from ball import Ball 
from scoreboard import Scoreboard
import time

screen = Screen()

screen.setup(width=800, height=600)
screen.bgcolor("black")
screen.title("Pong")
screen.tracer(0)

border = Turtle()
border.hideturtle()
border.penup()
border.color("white")
border.goto(-400, -300)  
border.pendown()
border.pensize(3)

for _ in range(2):
    border.forward(800) 
    border.left(90)
    border.forward(600)
    border.left(90)

border.penup()
border.goto(0, -300)
border.pendown()
border.pensize(3)
border.setheading(90)
for _ in range(15):
    border.forward(20)
    border.penup()
    border.forward(20)
    border.pendown()

border.penup()

r_paddle = Paddle((350, 0))
l_paddle = Paddle((-350, 0))
ball = Ball()
scoreboard = Scoreboard()
game_over_score = screen.numinput(title="Game Over Score", prompt="Enter the score to win the game", default=5)

screen.listen()
screen.onkeypress(r_paddle.go_up, "Up")
screen.onkeypress(r_paddle.go_down, "Down")
screen.onkey(l_paddle.go_up, "w")
screen.onkey(l_paddle.go_down, "s")



game_is_on = True
while game_is_on:
    screen.update()
    ball.move()
    time.sleep(ball.move_speed)

    #collison with wall
    if ball.ycor()>280 or ball.ycor()< -280:
        ball.bounce_y()
        ball.move_speed *= 0.9

    #collison with paddle
    if ball.distance(r_paddle) < 50 and ball.xcor()>320 or ball.distance(l_paddle) < 50 and ball.xcor()< -320:
        ball.bounce_x()
        ball.move_speed *= 0.9

    #detect right paddle misses
    if ball.xcor()>380:
        ball.reset_position()
        ball.bounce_y()
        scoreboard.l_point()
        ball.move_speed=0.1


    #detect left paddle misses
    if ball.xcor()< -380:
        ball.reset_position()
        ball.bounce_y()
        scoreboard.r_point()
        ball.move_speed=0.1

    if scoreboard.l_score==game_over_score or scoreboard.r_score==game_over_score:
        game_is_on=False
        scoreboard.game_over()






screen.exitonclick()