import random


def matrix(row, col, low, high):
    for _ in range(row):
        print(" ".join([str(random.randint(low, high)) for _ in range(col)]))


N = 3
print(N)
for _ in range(N):
    print(" ".join([str(random.randint(-2, 2)), str(random.randint(1, 3))]))

Q = 2
print(Q)
matrix(1, Q, -5, 5)
