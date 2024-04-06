'''
You are required to implement the Minimax algorithm along with Alpha-Beta Pruning
for a two-player game of your choice. The game should have a well-defined state
space and should be suitable for demonstrating the effectiveness of both algorithms.
(a) Implement the game rules: Create the necessary data structures and functions to
represent the game state, allow players to make moves, and determine when the game
is over. Define an evaluation function to estimate the desirability of a game state for
the maximizing player.
(b) Implement the Minimax algorithm: Write the Minimax algorithm to search the
game tree and determine the best move for the maximizing player while assuming the
opponent plays optimally.

(c) Implement Alpha-Beta Pruning: Extend your implementation to incorporate Alpha-
Beta Pruning.
'''

#using tic tac toe as the two player game

import random
import math

def print_board(board):
    print(" ")
    print(" ", board[0], " | ", board[1], " | ", board[2])
    print("----|----|----")
    print(" ", board[3], " | ", board[4], " | ", board[5])
    print("----|----|----")
    print(" ", board[6], " | ", board[7], " | ", board[8])
    print(" ")

def check_win(board, player):
    win = False
    if (board[0] == player and board[1] == player and board[2] == player) or \
        (board[3] == player and board[4] == player and board[5] == player) or \
        (board[6] == player and board[7] == player and board[8] == player) or \
        (board[0] == player and board[3] == player and board[6] == player) or \
        (board[1] == player and board[4] == player and board[7] == player) or \
        (board[2] == player and board[5] == player and board[8] == player) or \
        (board[0] == player and board[4] == player and board[8] == player) or \
        (board[2] == player and board[4] == player and board[6] == player):
        win = True
    return win

def check_draw(board):
    draw = False
    if " " not in board:
        draw = True
    return draw

def get_empty_cells(board):
    empty_cells = []
    for i in range(9):
        if board[i] == " ":
            empty_cells.append(i)
    return empty_cells

def minimax(board, player):
    empty_cells = get_empty_cells(board)
    if check_win(board, "X"):
        return -1
    elif check_win(board, "O"):
        return 1
    elif check_draw(board):
        return 0

    if player == "O":
        best = -1
        for cell in empty_cells:
            board[cell] = player
            val = minimax(board, "X")
            best = max(best, val)
            board[cell] = " "
    else:
        best = 1
        for cell in empty_cells:
            board[cell] = player
            val = minimax(board, "O")
            best = min(best, val)
            board[cell] = " "
    return best

def get_best_move(board, player):
    empty_cells = get_empty_cells(board)
    best_val = -1
    best_move = -1
    for cell in empty_cells:
        board[cell] = player
        val = minimax(board, "X")
        if val > best_val:
            best_val = val
            best_move = cell
        board[cell] = " "
    return best_move

def play_game():
    board = [" " for i in range(9)]
    print_board(board)
    while True:
        player_move = int(input("Enter your move: "))
        board[player_move] = "X"
        print_board(board)
        if check_win(board, "X"):
            print("You won!")
            break
        elif check_draw(board):
            print("It's a draw!")
            break
        computer_move = get_best_move(board, "O")
        board[computer_move] = "O"
        print_board(board)
        if check_win(board, "O"):
            print("Computer won!")
            break
        elif check_draw(board):
            print("It's a draw!")
            break

play_game()
