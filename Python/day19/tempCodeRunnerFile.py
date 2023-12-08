f down_press():
    global down_pressed
    down_pressed = True

def down_release():
    global down_pressed
    down_pressed = False

screen.onkey(up_press, "Up")
screen.onkey(up_release, "Up", True)
screen.onkey(down_press, "Down")
screen.onkey(down_release, "Down", True)

while True:
    if up_pressed and down_pressed:
        moveByTenAngle()