import random
import sys

n = int(sys.argv[1])
print(n)
for _ in range(n):
    row = [random.randint(0, 1) for _ in range(n)]
    print(" ".join(map(str, row)))