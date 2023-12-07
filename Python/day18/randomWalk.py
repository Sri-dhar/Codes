import random
import turtle as t

mike = t.Turtle()
mike.shape("turtle")
mike.pensize(5)
mike.speed(0)

for i in range(1000):
    random_color = "#{:02x}{:02x}{:02x}".format(
        random.randint(0, 255),
        random.randint(0, 255),
        random.randint(0, 255)
    )
    mike.color(random_color)
    mike.forward(40)
    mike.right(random.randint(0, 360))
    print(i)

mike.getscreen().exitonclick()
