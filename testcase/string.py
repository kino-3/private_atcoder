import random

N = 15
use_character = "afpz"

res = ""
for i in range(N):
    res += random.choice(list(use_character))

print(res)
