import turtle as t

mike = t.Turtle()
mike.shape("turtle")

colors = ["red","blue","green","cyan","orange","purple","pink"]

for i in range(3,11):
    mike.color(colors[i%7])
    for x in range(1,i+1):
        mike.forward(100)
        mike.rt(360/i)

mike.getscreen().exitonclick()