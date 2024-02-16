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
# state_matrix = [[1, 2, 3], [4, 5, 6], [7, 0, 8]]

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

if(is_solvable(state_matrix)):
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

# BFS
# def BFS(matrix):
#     queue = []
#     queue.append(matrix)
#     while queue:
#         current = queue.pop(0)
#         no_of_states_checked += 1
#         if goalTest(current):
#             print("Goal State Found")
#             printState(current)
#             exit()
#             return True
#         else:
#             up_result = moveUp(current)
#             if up_result:
#                 queue.append(up_result)
#                 printState(up_result)
#             down_result = moveDown(current)
#             if down_result:
#                 queue.append(down_result)
#                 printState(down_result)
#             left_result = moveLeft(current)
#             if left_result:
#                 queue.append(left_result)
#                 printState(left_result)
#             right_result = moveRight(current)
#             if right_result:
#                 queue.append(right_result)
#                 printState(right_result)
#     return False

# BFS with no. of states checked
# def BFS(matrix):
#     global no_of_states_checked  
#     queue = []
#     queue.append(matrix)
#     while queue:
#         current = queue.pop(0)
#         no_of_states_checked += 1
#         if goalTest(current):
#             print("Goal State Found")
#             printState(current)
#             with open('state_matrix.txt', 'a') as f:
#                 f.write(f'Number of states checked: {no_of_states_checked}\n')
#             exit()
#             return True
#         else:
#             up_result = moveUp(current)
#             if up_result:
#                 queue.append(up_result)
#                 printState(up_result)
#             down_result = moveDown(current)
#             if down_result:
#                 queue.append(down_result)
#                 printState(down_result)
#             left_result = moveLeft(current)
#             if left_result:
#                 queue.append(left_result)
#                 printState(left_result)
#             right_result = moveRight(current)
#             if right_result:
#                 queue.append(right_result)
#                 printState(right_result)
#     return False

# BFS with no. of states checked and visited set
# def BFS(matrix):
#     global no_of_states_checked  
#     queue = []
#     visited = set()  
#     queue.append(matrix)
#     visited.add(str(matrix))  
#     while queue:
#         current = queue.pop(0)
#         no_of_states_checked += 1
#         if goalTest(current):
#             print("Goal State Found")
#             printState(current)
#             with open('state_matrix.txt', 'a') as f:
#                 f.write(f'Number of states checked using BFS: {no_of_states_checked}\n')
#             # exit()
#             return True
#         else:
#             up_result = moveUp(current)
#             if up_result and str(up_result) not in visited:  
#                 queue.append(up_result)
#                 visited.add(str(up_result))  
#                 printState(up_result)
#             down_result = moveDown(current)
#             if down_result and str(down_result) not in visited:  
#                 queue.append(down_result)
#                 visited.add(str(down_result))  
#                 printState(down_result)
#             left_result = moveLeft(current)
#             if left_result and str(left_result) not in visited:  
#                 queue.append(left_result)
#                 visited.add(str(left_result))  
#                 printState(left_result)
#             right_result = moveRight(current)
#             if right_result and str(right_result) not in visited:  
#                 queue.append(right_result)
#                 visited.add(str(right_result))
#                 printState(right_result)
#     return False

# print("BFS: ", BFS(state_matrix))

# state_matrix = state_matrix_copy

# def DFS(matrix):
#     global no_of_states_checked
#     stack = []
#     visited = set()
#     stack.append(matrix)
#     visited.add(str(matrix))
#     while stack:
#         current = stack.pop()
#         no_of_states_checked += 1
#         if goalTest(current):
#             print("Goal State Found")
#             printState(current)
#             with open('state_matrix.txt', 'a') as f:
#                 f.write(f'Number of states checked using DFS: {no_of_states_checked}\n')
#             # exit()
#             return True
#         else:
#             up_result = moveUp(current)
#             if up_result and str(up_result) not in visited:
#                 stack.append(up_result)
#                 visited.add(str(up_result))
#                 printState(up_result)
#             down_result = moveDown(current)
#             if down_result and str(down_result) not in visited:
#                 stack.append(down_result)
#                 visited.add(str(down_result))
#                 printState(down_result)
#             left_result = moveLeft(current)
#             if left_result and str(left_result) not in visited:
#                 stack.append(left_result)
#                 visited.add(str(left_result))
#                 printState(left_result)
#             right_result = moveRight(current)
#             if right_result and str(right_result) not in visited:
#                 stack.append(right_result)
#                 visited.add(str(right_result))
#                 printState(right_result)
#     return False

# print("DFS: ", DFS(state_matrix))

# state_matrix = state_matrix_copy

# def iterative_deepening(matrix):
#     global no_of_states_checked
#     for i in range(100):
#         stack = []
#         visited = set()
#         stack.append(matrix)
#         visited.add(str(matrix))
#         while stack:
#             current = stack.pop()
#             no_of_states_checked += 1
#             if goalTest(current):
#                 print("Goal State Found")
#                 printState(current)
#                 with open('state_matrix.txt', 'a') as f:
#                     f.write(f'Number of states checked using Iterative Deepening: {no_of_states_checked}\n')
#                 # exit()
#                 return True
#             else:
#                 up_result = moveUp(current)
#                 if up_result and str(up_result) not in visited:
#                     stack.append(up_result)
#                     visited.add(str(up_result))
#                     printState(up_result)
#                 down_result = moveDown(current)
#                 if down_result and str(down_result) not in visited:
#                     stack.append(down_result)
#                     visited.add(str(down_result))
#                     printState(down_result)
#                 left_result = moveLeft(current)
#                 if left_result and str(left_result) not in visited:
#                     stack.append(left_result)
#                     visited.add(str(left_result))
#                     printState(left_result)
#                 right_result = moveRight(current)
#                 if right_result and str(right_result) not in visited:
#                     stack.append(right_result)
#                     visited.add(str(right_result))
#                     printState(right_result)
#     return False

# print("Iterative Deepening: ", iterative_deepening(state_matrix))

# state_matrix = state_matrix_copy
# def uniform_cost_search(matrix):
#     global no_of_states_checked
#     queue = []
#     visited = set()
#     queue.append(matrix)
#     visited.add(str(matrix))
#     while queue:
#         current = queue.pop(0)
#         no_of_states_checked += 1
#         if goalTest(current):
#             print("Goal State Found")
#             printState(current)
#             with open('state_matrix.txt', 'a') as f:
#                 f.write(f'Number of states checked using Uniform Cost Search: {no_of_states_checked}\n')
#             # exit()
#             return True
#         else:
#             up_result = moveUp(current)
#             if up_result and str(up_result) not in visited:
#                 queue.append(up_result)
#                 visited.add(str(up_result))
#                 printState(up_result)
#             down_result = moveDown(current)
#             if down_result and str(down_result) not in visited:
#                 queue.append(down_result)
#                 visited.add(str(down_result))
#                 printState(down_result)
#             left_result = moveLeft(current)
#             if left_result and str(left_result) not in visited:
#                 queue.append(left_result)
#                 visited.add(str(left_result))
#                 printState(left_result)
#             right_result = moveRight(current)
#             if right_result and str(right_result) not in visited:
#                 queue.append(right_result)
#                 visited.add(str(right_result))
#                 printState(right_result)
#     return False

# print("Uniform Cost Search: ", uniform_cost_search(state_matrix))

state_matrix = state_matrix_copy

def heuristic(matrix, goal_matrix):
    distance = 0
    for i in range(3):
        for j in range(3):
            if matrix[i][j] != 0:
                x, y = divmod(matrix[i][j]-1, 3)
                distance += abs(x - i) + abs(y - j)
    return distance

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
                    printState(result)
    return False

print("Greedy BFS: ", greedy_bfs(state_matrix))

state_matrix = state_matrix_copy

def a_star(matrix):
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
                f.write(f'Number of states checked using A* Search: {no_of_states_checked}\n')
            return True
        else:
            for move in [moveUp, moveDown, moveLeft, moveRight]:
                result = move(current)
                if result and str(result) not in visited:
                    heapq.heappush(queue, (heuristic(result, goal_matrix) + no_of_states_checked, result))
                    visited.add(str(result))
                    printState(result)
    return False

print("A* Search: ", a_star(state_matrix))