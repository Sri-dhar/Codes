class User:
    def __init__(self,name =None,score = None, weight = None) -> None:
        self.name = name
        self.score = score
        self.weight = weight
        print(f"User created {self.name}")

    def __str__(self) -> str:
        return f"{self.name} has a score of {self.score} and a weight of {self.weight}"

# apple = User()
# apple.name = "Apple"
# apple.score = 10
# apple.weight = 20

# print(apple)

# banana = User("Banana")

print(User("Apple",10,20))