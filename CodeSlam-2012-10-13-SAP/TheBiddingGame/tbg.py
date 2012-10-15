#!/bin/python

def calculate_bid(player,pos,first_moves,second_moves):
    """your logic here"""

    ###

    import random

    bank = 100

    win = True
    first_wins = []
    for a, b in zip(first_moves, second_moves):
        if a == b:
            if win:
                first_wins.append(a)
            else:
                first_wins.append(0)
            win = not win
        elif a > b:
            first_wins.append(a)
        else:
            first_wins.append(0)
    fw = win

    win = False
    second_wins = []
    for a, b in zip(second_moves, first_moves):
        if a == b:
            if win:
                second_wins.append(a)
            else:
                second_wins.append(0)
            win = not win
        elif a > b:
            second_wins.append(a)
        else:
            second_wins.append(0)
    sw = win

    win = fw if player == 1 else sw
    tw = 0 if win else 1

    money = [bank - sum(x) for x in first_wins, second_wins]

    my_money = money[player - 1]
    their_money = money[player % 2]

    if my_money == 0:
        return 0

    f = min(my_money, their_money)

    maxp = 9 if player == 1 else 1
    maxp0 = 10 if player == 1 else 0

    if maxp + pos == 10:
        return max(1, my_money)
    elif maxp == pos:
        return max(1, min(my_money, their_money + tw))

    pf = 0.9
    dist = abs(maxp0 - pos)
    fact = [(1 / (i ** pf)) for i in range(1, dist + 1)]
    coeff = sum(fact)
    mu = f / (coeff * (dist ** pf))
    mu += tw

    return max(1, min(my_money, int(round(mu))))

    ###

    return 0

#gets the id of the player
player = input()

scotch_pos = input()         #current position of the scotch

first_moves = [int(i) for i in raw_input().split()]
second_moves = [int(i) for i in raw_input().split()]
bid = calculate_bid(player,scotch_pos,first_moves,second_moves)
print bid

