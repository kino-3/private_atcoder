import random

N = 12
print(N)

res = ""
for i in range(N):
    res += random.choice(list("aszk"))
print(res)
