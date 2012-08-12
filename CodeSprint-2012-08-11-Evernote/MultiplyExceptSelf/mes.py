
import sys

n = int(sys.stdin.readline())

ns = []

for i in range(n):
    ns.append(int(sys.stdin.readline()))

prd = reduce(lambda x, y: x * y, ns, 1)

n0s = [prd / x for x in ns]

for x in n0s:
    print x

