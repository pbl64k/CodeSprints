
import sys
import heapq

def find(v2c, csz, v):
    if v2c[v] != v:
        v2c[v] = find(v2c, csz, v2c[v])
    return v2c[v]

def union(v2c, csz, l, r):
    rootl = find(v2c, csz, l)
    rootr = find(v2c, csz, r)

    if rootl == rootr:
        return False

    if csz[rootl] < csz[rootr]:
        rootl, rootr = rootr, rootl

    v2c[rootr] = rootl
    csz[rootl] += csz[rootr]

    return True

t = int(sys.stdin.readline())

for tt in range(t):
    n, m, k = map(int, sys.stdin.readline().split(' '))
    es = []
    for mm in range(m):
        i, j, c = map(int, sys.stdin.readline().split(' '))
        heapq.heappush(es, (c, i - 1, j - 1))
    #es = sorted(es, lambda a, b: cmp(a[0], b[0]))
    v2c = [i for i in range(n)]
    csz = [1 for i in range(n)]
    w = 0
    comps = n

    try:
        while True:
            c, i, j = heapq.heappop(es)
            if comps <= k:
                break
            if not union(v2c, csz, i, j):
                continue
            w += c
            comps -= 1
    except:
        pass

    if comps > k:
        print 'Impossible!'
    else:
        print w

