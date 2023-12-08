from turtle import Turtle,Screen
timmy = Turtle()
print(timmy)
timmy.shape("turtle")
timmy.color('cyan3')

for i in range(1000,10):
    timmy.forward(int(i%200))
    timmy.right(int(i%90))

# timmy.forward(100)
Screen().exitonclick()
# for i in range(1000):
#     timmy.forward(i%200)
#     timmy.right(i%90)