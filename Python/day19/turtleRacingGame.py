import turtle as t
import random

screen = t.Screen()
screen.setup(width=500, height=400)

colors = ["red", "orange", "cyan", "green", "blue", "purple"]

turtles = []
for i in range(6):
    turtles.append(t.Turtle(shape="turtle"))
    turtles[i].color(colors[i])
    turtles[i].penup()
    turtles[i].goto(x=-230, y=-100 + i * 40)

screen.title("Turtle Racing Game")
bet = screen.textinput("Welcome", "You can bet on one of the following turtles: \n"
                             "1. red\n"
                             "2. orange\n"
                             "3. cyan\n"
                             "4. green\n"
                             "5. blue\n"
                             "6. purple\n"
                             "Which turtle would you like to put your bet on (1-6): ")
bet = int(bet) - 1
finish_line = 230

text_output_turtle = t.Turtle()
text_output_turtle.hideturtle()
text_output_turtle.penup()
text_output_turtle.goto(0, 0)

def display_text(message):
    text_output_turtle.write(message, align="center", font=("Arial", 16, "normal"))

flag = False

turtles[0].forward(50)

for i in range(100):
    for turtle in turtles:
        turtle.forward(random.randint(0, 10))

        if turtle.xcor() > finish_line and not flag:
            flag = True
            if turtles.index(turtle) == bet:
                display_text(f"Your {colors[bet]} Turtle Won!\nThe winning turtle is {colors[turtles.index(turtle)]}")
            else:
                display_text(f"Your {colors[bet]} Turtle Lost!\nThe winning turtle is {colors[turtles.index(turtle)]}")
          

t.mainloop()
