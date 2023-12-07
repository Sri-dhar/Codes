import copy
import random

class Hat:
    def __init__(self, **balls):
        self.contents = []
        for color, quantity in balls.items():
            self.contents.extend([color] * quantity)
    
    def draw(self, num):
        if num >= len(self.contents):
            temp = copy.deepcopy(self.contents)
            self.contents = []
            return temp
        else:
            taken_balls = random.sample(self.contents, num)
            for ball in taken_balls:
                self.contents.remove(ball)

            return taken_balls

def experiment(hat, expected_balls, num_balls_drawn, num_experiments):
    success = 0
    for i in range(num_experiments):
        hat_copy = copy.deepcopy(hat)
        taken = hat_copy.draw(num_balls_drawn)
        taken_dict = {}
        for ball in taken:
            if ball in taken_dict:
                taken_dict[ball] += 1
            else:
                taken_dict[ball] = 1
        flag = True
        for color, quantity in expected_balls.items():
            if color not in taken_dict or taken_dict[color] < quantity:
                flag = False
                break
        if flag:
            success += 1
    return success / num_experiments
