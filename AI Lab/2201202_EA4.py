import math

class GameStones:
    def __init__(self, num_stones):
        self.num_stones = num_stones
        self.max = 2
        self.min = 1
        self.max_depth = 10
    
    def removestones(self, stones):
        self.num_stones -= stones
    
    def printstones(self):
        for i in range(self.num_stones):
            print("🪨", end = " ")

    def computerTurn(self):
        position = self.alphabeta(self.num_stones, True,-math.inf, math.inf, 0)[1]
        return position

    def alphabeta(self, stones, player, alpha, beta, depth):
        if self.num_stones == 0:
            return [-1, None] if player else [1, None]
        if depth == self.max_depth:
            return [0, None]

        if player:
            best = [-math.inf, None]
        else:
            best = [math.inf, None]

        for i in range(self.min, min(self.max, self.num_stones)+1):
            self.num_stones -= i
            result = self.alphabeta(stones, not player, alpha, beta, depth + 1)
            self.num_stones += i
            result[1] = i
            if player:
                if result[0] > best[0]:
                    best = result
                alpha = max(alpha, best[0])
            else:
                if result[0] < best[0]:
                    best = result
                beta = min(beta, best[0])

            if beta <= alpha:
                break
        return best
    
    def game(self):
        result = 0
        while self.num_stones > 0:    
            self.printstones()
            while True:
                result = int(input(f"\nEnter the number of stones to remove between {self.min} and {self.max} : "))        
                if self.max >= result >= self.min and result <= self.num_stones:
                    break; 
            self.removestones(result)
            if self.num_stones == 0:
                print("\nThe player has won!")
                break
            self.printstones()   
            computer = self.computerTurn();
            self.removestones(computer)
            print(f"\nThe computer has removed {computer} stones.")
            if self.num_stones == 0:
                print("\nThe computer has won")
            if self.num_stones < self.max:
                self.max = self.num_stones

            

num_stones = 50
board = GameStones(num_stones)

board.game()