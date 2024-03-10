from queue import PriorityQueue 

class State:
    def __init__(self, missionaries_left, cannibals_left, boat, missionaries_right, cannibals_right, cost):
        # Initialize a state with the given number of missionaries and cannibals on each side, boat position, and cost
        self.missionaries_left = missionaries_left
        self.cannibals_left = cannibals_left
        self.boat = boat
        self.missionaries_right = missionaries_right
        self.cannibals_right = cannibals_right
        self.cost = cost

    def is_valid(self):
        # Check if the current state is valid according to the problem constraints
        if self.missionaries_left < 0 or self.missionaries_right < 0 or \
           self.cannibals_left < 0 or self.cannibals_right < 0:
            return False
        if self.missionaries_left < self.cannibals_left and self.missionaries_left > 0:
            return False
        if self.missionaries_right < self.cannibals_right and self.missionaries_right > 0:
            return False
        return True

    def is_goal(self):
        # Check if the current state is the goal state (no missionaries or cannibals on the left side)
        return self.missionaries_left == 0 and self.cannibals_left == 0

    def __eq__(self, other):
        return self.missionaries_left == other.missionaries_left and \
               self.cannibals_left == other.cannibals_left and \
               self.boat == other.boat and \
               self.missionaries_right == other.missionaries_right and \
               self.cannibals_right == other.cannibals_right

    def __hash__(self):
        return hash((self.missionaries_left, self.cannibals_left, self.boat,
                     self.missionaries_right, self.cannibals_right))

    def __lt__(self, other):
        return self.cost < other.cost


def get_successors(current_state):
    successors = []
    if current_state.boat == 'left':
        for m in range(3):
            for c in range(3):
                if 0 < m + c <= 2: 
                    new_state = State(current_state.missionaries_left - m,
                                      current_state.cannibals_left - c,
                                      'right',
                                      current_state.missionaries_right + m,
                                      current_state.cannibals_right + c,
                                      current_state.cost + m * 10 + c * 20)
                    if new_state.is_valid():
                        successors.append(new_state)
    else:
        # If the boat is on the right side, consider moving it to the left side
        for m in range(3):
            for c in range(3):
                if 0 < m + c <= 2:  
                    new_state = State(current_state.missionaries_left + m,
                                      current_state.cannibals_left + c,
                                      'left',
                                      current_state.missionaries_right - m,
                                      current_state.cannibals_right - c,
                                      current_state.cost + m * 10 + c * 20)
                    if new_state.is_valid():
                        successors.append(new_state)
    return successors

def uniform_cost_search(x, y):
    initial_state = State(x, y, 'left', 0, 0, 0) 
    frontier = PriorityQueue()  
    frontier.put((0, initial_state)) 

    explored = set()  
    parent_map = {initial_state: None}  
    while not frontier.empty():
        current_state = frontier.get()[1]  
        if current_state.is_goal():
            return current_state, parent_map

        explored.add(current_state) 

        successors = get_successors(current_state) 
        for successor in successors:
            if successor not in explored and all(successor != item[1] for item in frontier.queue):
                frontier.put((successor.cost, successor))  
                parent_map[successor] = current_state  
    return None, None

def print_solution(solution, parent_map):
    if solution is None:
        print("No solution found.")
    else:
        path = []
        while solution:
            path.append(solution)
            solution = parent_map[solution] if solution in parent_map else None

        for t in reversed(path):
            print(f"Boat on the {t.boat} side")
            print("Left bank: ", t.missionaries_left, " missionaries, ", t.cannibals_left, " cannibals")
            print("Right bank: ", t.missionaries_right, " missionaries, ", t.cannibals_right, " cannibals")
            print("Cost: Rs", t.cost)
            print("\n")

if __name__ == "__main__":
    x = int(input("Enter the number of Missionaries : "))
    y = int(input("Enter the number of Cannibals : "))
    solution, parent_map = uniform_cost_search(x, y)
    print_solution(solution, parent_map)