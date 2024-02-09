import random
import copy

goal_matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
possible_input = [1, 2, 3, 4, 5, 6, 7, 8, 0]
state_matrix = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]

for i in range(3):
    for j in range(3):
        state_matrix[i][j] = random.choice(possible_input)
        possible_input.remove(state_matrix[i][j])

# state_matrix = [[1, 2, 3], [4, 5, 6], [7, 0, 8]]

def printState(matrix):
    print("+---+---+---+")
    for i in range(3):
        for j in range(3):
            print("|", matrix[i][j], end=" ")
        print("|")
        print("+---+---+---+")

printState(state_matrix)

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

# BFS
def BFS(matrix):
    queue = []
    queue.append(matrix)
    while queue:
        current = queue.pop(0)
        if goalTest(current):
            print("Goal State Found")
            printState(current)
            exit()
            return True
        else:
            up_result = moveUp(current)
            if up_result:
                queue.append(up_result)
                printState(up_result)
            down_result = moveDown(current)
            if down_result:
                queue.append(down_result)
                printState(down_result)
            left_result = moveLeft(current)
            if left_result:
                queue.append(left_result)
                printState(left_result)
            right_result = moveRight(current)
            if right_result:
                queue.append(right_result)
                printState(right_result)
    return False

print("BFS: ", BFS(state_matrix))
