from turtle import Turtle

STARTING_POSITION = (0, -280)
MOVE_DISTANCE = 10
FINISH_LINE_Y = 280


class Player(Turtle):
    def __init__(self):
        super().__init__()
        self.shape("turtle")
        self.color("red")
        self.penup()
        self.setheading(90)
        self.goto(STARTING_POSITION)

    def move(self):
        self.forward(MOVE_DISTANCE)

    def reset(self):
        self.goto(STARTING_POSITION)
    
    def is_at_finish_line(self):
        if self.ycor() > FINISH_LINE_Y:
            return True
        else:
            return False
    
    def is_at_start_line(self):
        if self.ycor() < -280:
            return True
        else:
            return False
    
    def go_to_start(self):
        self.goto(STARTING_POSITION)

    def increase_speed(self):
        global MOVE_DISTANCE
        MOVE_DISTANCE += 10
        print(MOVE_DISTANCE)

    def is_at_finish_line(self):
        if self.ycor() > FINISH_LINE_Y:
            return True
        else:
            return False
        
    def is_at_start_line(self):
        if self.ycor() < -280:
            return True
        else:
            return False
    
    def go_to_start(self):
        self.goto(STARTING_POSITION)


