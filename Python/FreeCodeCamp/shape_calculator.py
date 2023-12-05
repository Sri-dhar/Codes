class Rectangle:
    def __init__(self, widthH, heightH):
        self.width = widthH
        self.height = heightH

    def set_width(self, width):
        self.width = width

    def set_height(self, height):
        self.height = height

    def get_area(self):
        return self.width * self.height

    def get_perimeter(self):
        return 2 * (self.width + self.height)

    def get_diagonal(self):
        return (self.width**2 + self.height**2)**0.5

    def get_picture(self):
        if self.width > 50 or self.height > 50:
            return "Too big for picture."
        else:
            picture = ""
            for _ in range(self.height):
                for _ in range(self.width):
                    picture += "*"
                picture += "\n"
            return picture

    def get_amount_inside(self, shape):
        return self.get_area() // shape.get_area()
    
    def __str__(self):
        return f"Rectangle(width={self.width}, height={self.height})"


class Square(Rectangle):
    def __init__(self, side):
        self.width = side
        self.height = side

    def set_side(self, side):
        self.width = side
        self.height = side

    def set_width(self, side):
        self.set_side(side)

    def set_height(self, side):
        self.set_side(side)

    def __str__(self):
        return f"Square(side={self.width})"

    def get_picture(self):
        if self.width > 50 or self.height > 50:
            return "Too big for picture."
        else:
            picture = ""
            for _ in range(self.height):
                picture += "*" * self.width + "\n"
            return picture

# R = Rectangle(4, 8)
# print(R.get_area())

# S = Square(4)
# print(S.get_picture())
