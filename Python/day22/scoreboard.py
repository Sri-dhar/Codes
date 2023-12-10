from turtle import Turtle, Screen

class Scoreboard(Turtle):
    def __init__(self):
        super().__init__()
        self.color("white")
        self.penup()
        self.hideturtle()
        self.l_score=0
        self.r_score=0
        self.update_scoreboard()

    def update_scoreboard(self):
        self.clear()
        self.goto(-100,200)
        self.write(self.l_score, align="center", font=("Courier", 40, "normal"))
        self.goto(100,200)
        self.write(self.r_score, align="center", font=("Courier", 40, "normal"))

    def l_point(self):
        self.l_score+=1
        self.update_scoreboard()

    def r_point(self):
        self.r_score+=1
        self.update_scoreboard()

    def game_over(self):
        self.goto(0,0)
        self.write("GAME OVER", align="center", font=("Courier", 80, "normal"))
        if self.l_score > self.r_score:
            self.goto(0,-100)
            self.write("Left Player Wins!", align="center", font=("Courier", 40, "normal"))
        else:
            self.goto(0,-100)
            self.write("Right Player Wins!", align="center", font=("Courier", 40, "normal"))