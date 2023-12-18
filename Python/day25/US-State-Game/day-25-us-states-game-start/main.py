import turtle
import pandas

screen = turtle.Screen()
screen.title("U.S. States Game")

screen.addshape("blank_states_img.gif")

turtle.shape("blank_states_img.gif")
data = pandas.read_csv("50_states.csv")
# print(type(data))
data_list = data["state"].to_list()
# print(data_list)

answer = screen.textinput(title="Guess the State", prompt="What's another state's name?").title()
if answer in data_list:
    t = turtle.Turtle()
    t.hideturtle()
    t.penup()
    state_data = data[data.state == answer]
    t.goto(int(state_data.x), int(state_data.y))
    t.write(answer)
    data_list.remove(answer)

    while len(data_list) > 0:
        answer = screen.textinput(title=f"{len(data_list)} States Correct", prompt="What's another state's name?").title()
        if answer == "Exit":
            break
        if answer in data_list:
            t = turtle.Turtle()
            t.hideturtle()
            t.penup()
            state_data = data[data.state == answer]
            t.goto(int(state_data.x), int(state_data.y))
            t.write(answer)
            data_list.remove(answer)

screen.exitonclick()   