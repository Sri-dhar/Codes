import random
import copy
import heapq

goal_matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
possible_input = [1, 2, 3, 4, 5, 6, 7, 8, 0]
state_matrix = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]

for i in range(3):
    for j in range(3):
        state_matrix[i][j] = random.choice(possible_input)
        possible_input.remove(state_matrix[i][j])

state_matrix_copy = copy.deepcopy(state_matrix)

with open("state_matrix.txt", "w") as file:
    for i in range(3):
        for j in range(3):
            file.write(str(state_matrix[i][j]) + " ")
        file.write("\n")

def printState(matrix):
    print("+---+---+---+")
    for i in range(3):
        for j in range(3):
            print("|", matrix[i][j], end=" ")
        print("|")
        print("+---+---+---+")

printState(state_matrix)

def is_solvable(puzzle):
    puzzle = [item for sublist in puzzle for item in sublist if item != 0]
    
    inversions = 0
    for i in range(len(puzzle)):
        for j in range(i + 1, len(puzzle)):
            if puzzle[i] > puzzle[j]:
                inversions += 1

    return inversions % 2 == 0

if is_solvable(state_matrix):
    print("The puzzle is solvable")
else:
    print("The puzzle is not solvable")
    exit()

def goalTest(matrix):
    for i in range(3):
        for j in range(3):
            if matrix[i][j] != goal_matrix[i][j]:
                return False
    return True

print("Goal Test of current state matrix: ", goalTest(state_matrix))
print("INITIAL MATRIX is not the FINAL MATRIX")

def moveDown(matrix):
    for i in range(3):
        for j in range(3):
            if matrix[i][j] == 0:
                if i == 2:
                    return False
                else:
                    new_matrix = copy.deepcopy(matrix)
                    new_matrix[i][j], new_matrix[i+1][j] = new_matrix[i+1][j], new_matrix[i][j]
                    return new_matrix

def moveLeft(matrix):
    for i in range(3):
        for j in range(3):
            if matrix[i][j] == 0:
                if j == 0:
                    return False
                else:
                    new_matrix = copy.deepcopy(matrix)
                    new_matrix[i][j], new_matrix[i][j-1] = new_matrix[i][j-1], new_matrix[i][j]
                    return new_matrix

def moveRight(matrix):
    for i in range(3):
        for j in range(3):
            if matrix[i][j] == 0:
                if j == 2:
                    return False
                else:
                    new_matrix = copy.deepcopy(matrix)
                    new_matrix[i][j], new_matrix[i][j+1] = new_matrix[i][j+1], new_matrix[i][j]
                    return new_matrix

def moveUp(matrix):
    for i in range(3):
        for j in range(3):
            if matrix[i][j] == 0:
                if i == 0:
                    return False
                else:
                    new_matrix = copy.deepcopy(matrix)
                    new_matrix[i][j], new_matrix[i-1][j] = new_matrix[i-1][j], new_matrix[i][j]
                    return new_matrix

no_of_states_checked = 0

def heuristic(matrix, goal_matrix):
    distance = 0
    for i in range(3):
        for j in range(3):
            if matrix[i][j] != 0:
                x, y = divmod(matrix[i][j] - 1, 3)
                distance += abs(x - i) + abs(y - j)
    return distance if distance is not None else float('inf')

def greedy_bfs(matrix):
    global no_of_states_checked
    queue = []
    visited = set()
    heapq.heappush(queue, (heuristic(matrix, goal_matrix), matrix))
    visited.add(str(matrix))
    while queue:
        _, current = heapq.heappop(queue)
        no_of_states_checked += 1
        if goalTest(current):
            print("Goal State Found")
            printState(current)
            with open('state_matrix.txt', 'a') as f:
                f.write(f'Number of states checked using Greedy BFS: {no_of_states_checked}\n')
            return True
        else:
            for move in [moveUp, moveDown, moveLeft, moveRight]:
                result = move(current)
                if result and str(result) not in visited:
                    heapq.heappush(queue, (heuristic(result, goal_matrix), result))
                    visited.add(str(result))
    return False

print("Greedy BFS: ", greedy_bfs(state_matrix))

no_of_states_checked = 0

def a_star(matrix):
    global no_of_states_checked
    queue = []
    visited = set()
    heapq.heappush(queue, (heuristic(matrix, goal_matrix) + no_of_states_checked, matrix))
    visited.add(str(matrix))
    while queue:
        _, current = heapq.heappop(queue)
        no_of_states_checked += 1
        if goalTest(current):
            print("Goal State Found")
            printState(current)
            with open('state_matrix.txt', 'a') as f:
                f.write(f'Number of states checked using A* Search: {no_of_states_checked}\n')
            return True
        else:
            for move in [moveUp, moveDown, moveLeft, moveRight]:
                result = move(current)
                if result and str(result) not in visited:
                    heapq.heappush(queue, (heuristic(result, goal_matrix) + no_of_states_checked, result))
                    visited.add(str(result))
    return False

print("A* Search: ", a_star(state_matrix))
