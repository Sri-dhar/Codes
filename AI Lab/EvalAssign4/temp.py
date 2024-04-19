'''
Design AI vs. human game and construct a game tree with alpha-beta pruning for the
following game.
● Played with two players and piles of 50-stones
● Each player removes 1/2 stones from the pile.
● Each player picks up stones alternatively.
● If it is the turn of player 1 and there are no stones left then player 1 loses.
● First turn will be randomly decided with a toss.
'''


import math
import random
