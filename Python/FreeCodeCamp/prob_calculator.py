import copy
import random
# Consider using the modules imported above.

class Hat:
    def __init__(self, **balls):
        self.ballsInHat = []
        for color, quantity in balls.items():
            self.ballsInHat.extend([color] * quantity)
    
    def draw(self, num):
        if num >= len(self.ballsInHat):
            temp = copy.deepcopy(self.ballsInHat)
            ballsInHat = []
            return temp
        else:
            takenBalls = []
            while(num > 0):
                index_to_pop = random.randint(0, len(self.ballsInHat) - 1)
                popped_ball = self.ballsInHat.pop(index_to_pop)
                takenBalls.append(popped_ball)    
                ballsInHat.remove(popped_ball)            
                num -= 1
        
        return takenBalls



def experiment(hat, expected_balls, num_balls_drawn, num_experiments):
    
