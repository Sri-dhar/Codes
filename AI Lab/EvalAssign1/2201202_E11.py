from queue import PriorityQueue

def is_state(state):
    m, c, boat = state
    if m < 0 or c < 0 or m > 3 or c > 3:
        return False
    if m > 0 and m < c:
        return False
    if m < 3 and (3 - m) < (3 - c):
        return False
    return True

def successor_fn(state):
    states = []
    m, c, boat = state

    if boat == 'left':
        for i in range(3):
            for j in range(3):
                if i + j > 2:
                    continue
                new_state = (m - i, c - j, 'right')
                if is_state(new_state):
                    states.append(new_state)
    else:
        for i in range(3):
            for j in range(3):
                if i + j > 2:
                    continue
                new_state = (m + i, c + j, 'left')
                if is_state(new_state):
                    states.append(new_state)

    return states

def UCS(x,y):
    start_state = (x, y, 'left')
    goal_state = (0, 0, 'right')

    queuee = PriorityQueue()
    queuee.put((0, start_state))
    explored = set()

    while not queuee.empty():
        cost, current_state = queuee.get()
        if current_state == goal_state:
            return cost

        explored.add(current_state)

        for next_state in successor_fn(current_state):
            if next_state not in explored:
                new_cost = cost + (10 * abs(current_state[0] - next_state[0])) + (20 * abs(current_state[1] - next_state[1]))
                queuee.put((new_cost, next_state))

    return -1

x = int(input("Enter the no. of Missionaries : "))
y = int(input("ENter the no. of Cannibals : "))

cost = UCS(x,y)

print("Minimum cost for moving :", cost)