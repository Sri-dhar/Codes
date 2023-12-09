from turtle import Turtle

class scoreBoard(Turtle):

    def get_high_score(self):
            try:
                with open("day21/high_score.txt", "r") as file:
                    return int(file.read())
            except FileNotFoundError:
                return 0

    def __init__(self):
        super().__init__()
        self.score = 0
        self.high_score = self.get_high_score()
        self.update_scoreboard()
        self.hideturtle()
        self.penup()
        self.goto(0, 260)
        self.color("white")
        self.update_scoreboard()
        self.location = (0, 260)

    def update_high_score(self):
        with open("day21/high_score.txt", "w") as file:
            file.write(str(self.high_score))
        self.update_scoreboard()
    

    def update_scoreboard(self):
        self.clear()
        self.write(f"Score: {self.score} High Score: {self.high_score}", align = "center", font = ("Roboto", 16, "normal"))

    def reset(self):
        if self.score > self.high_score:
            self.high_score = self.score
        self.update_scoreboard()
         

    def increase_score(self):
        self.score += 1
        self.update_scoreboard()
        self.update_high_score()

    def game_over(self):
        self.goto(0, 0)
        self.write("Game Over", align="center", font=("Roboto", 16, "normal"))
        self.goto(self.location)