import random


def matrix(row, col, low, high):
    for _ in range(row):
        print(" ".join([str(random.randint(low, high)) for _ in range(col)]))


matrix(3, 5, 0, 9)
