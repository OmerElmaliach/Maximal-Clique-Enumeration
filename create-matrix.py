import numpy
import sys

n = int(sys.argv[1])
edge_prob = [0.1, 0.9]
print(n)
for x in range(n):
    row = [numpy.random.choice(numpy.arange(0, 2), p=edge_prob) for x in range(n)]
    print(" ".join(map(str, row)))