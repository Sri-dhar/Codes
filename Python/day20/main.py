import random
import time
from turtle import Turtle, Screen
from snake import Snake 
from food import Food 

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

game_is_on = True
while game_is_on:
    screen.update()
    time.sleep(0.1)
    snake.move()  
    # snake.turn_right(Turtle.RIGHT)
