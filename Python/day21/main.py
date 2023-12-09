import random
import time
from turtle import Turtle, Screen
from snake import Snake 
from food import Food 
from scoreboard import scoreBoard

screen = Screen()
screen.setup(width=600, height=600)
screen.bgcolor("black")
screen.title("Snake Game")
screen.tracer(0)

# Initial positions of the snake
Turtle.STARTING_POSITIONS = [(0, 0), (-20, 0), (-40, 0)]
Turtle.MOVE_DISTANCE = 20
Turtle.RIGHT = 0
Turtle.UP = 90
Turtle.LEFT = 180   
Turtle.DOWN = 270

snake = Snake()  
screen.update()
screen.listen()
screen.onkey(snake.up, "Up")
screen.onkey(snake.down, "Down")
screen.onkey(snake.left, "Left")
screen.onkey(snake.right, "Right")

food = Food()
ScoreBoard = scoreBoard()

game_is_on = True
while game_is_on:
    screen.update()
    time.sleep(0.1)
    snake.move()  
    if(snake.head.distance(food) < 15):
        food.refresh()
        ScoreBoard.increase_score()
        snake.extend()
        ScoreBoard.update_high_score()
    # snake.turn_right(Turtle.RIGHT)

    #detect collision with wall
    if(snake.head.xcor() > 290 or snake.head.xcor() < -290 or snake.head.ycor() > 280 or snake.head.ycor() < -290):
        ScoreBoard.reset()
        snake.reset()
        food.disappear()
        ScoreBoard.update_high_score()
        ScoreBoard.game_over()

    #detect collision with tail
    for segment in snake.segments[1:]:
        if(snake.head.distance(segment) < 10):
            ScoreBoard.reset()
            snake.reset()
            food.disappear()
            ScoreBoard.update_high_score()
            ScoreBoard.game_over()


screen.exitonclick()
