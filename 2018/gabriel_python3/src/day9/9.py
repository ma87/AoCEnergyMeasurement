#!/usr/bin/env python3

from collections import deque

inputs = [
#'9 players; last marble is worth 25 points',  #high score is 32
#'10 players; last marble is worth 1618 points',  #high score is 8317
#'13 players; last marble is worth 7999 points',  #high score is 146373
#'17 players; last marble is worth 1104 points',  #high score is 2764
#'21 players; last marble is worth 6111 points',  #high score is 54718
#'30 players; last marble is worth 5807 points',  #high score is 37305
'473 players; last marble is worth 70904 points',
'473 players; last marble is worth 7090400 points'
]


def parse_input(game):
    line = game.split(' ')
    return int(line[0]), int(line[6])

def marble(num_players, last):
    players = [0] * num_players
    circle = deque([0])
    current = 0

    for i in range(1, last + 1):
        if i % 23 == 0:
            circle.rotate(7)
            players[i % len(players)] += i
            players[i % len(players)] += circle.pop()
            circle.rotate(-1)
        else:
            circle.rotate(-1)
            circle.append(i)

    return max(players)

for game in inputs:
    num_players, last = parse_input(game)
    print(game, 'high score is', marble(num_players, last))
