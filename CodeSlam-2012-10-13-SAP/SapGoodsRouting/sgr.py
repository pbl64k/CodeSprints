
import sys

def travpath(n, parent, totcost = 0):
    global ms, arcs, data, avgmph, limit
    if parent is None:
        cost = 0
    else:
        cost = (60 * data[(parent, n)]) / avgmph
    climit = totcost + cost
    children = [x for x in arcs[n] if x != parent]
    branches = []
    if len(children) > 0:
        for child in children:
            branches += travpath(child, n, climit)
    lb = len(branches)
    if lb == 0:
        if n in ms:
            return [([n], [], cost, cost)]
        else:
            return []
    else:
        branches = list(sorted(branches, lambda x, y: cmp(x[3], y[3])))
        res = []
        while len(branches) > 0:
            curbranches = branches
            branches = []
            bns, bexitns, bcost0, bexitcost = curbranches[0]
            ns = bns + [n]
            exitns = [n] + bexitns
            cost0 = bcost0 + cost
            exitcost = bexitcost + cost
            for i in range(1, len(curbranches)):
                b0ns, b0exitns, b0cost0, b0exitcost = curbranches[i]
                if totcost + cost0 + bexitcost + b0cost0 <= limit:
                    ns = b0ns + exitns + ns
                    exitns = [n] + b0exitns
                    cost0 += bexitcost + b0cost0
                    existcost = b0exitcost + cost
                else:
                    branches.append((b0ns, b0exitns, b0cost0, b0exitcost))
            res.append((ns, exitns, cost0, exitcost))
        return res

N, M = map(int, sys.stdin.readline().split(' '))

ms = set(map(int, sys.stdin.readline().split(' ')))

arcs = {}
data = {}

for i in range(N - 1):
    sx, sy, sd, sp = sys.stdin.readline().split(' ')
    x = int(sx)
    y = int(sy)
    d = int(sd)
    p = float(sp)
    if not arcs.has_key(x):
        arcs[x] = set()
    arcs[x].add(y)
    if not arcs.has_key(y):
        arcs[y] = set()
    arcs[y].add(x)
    data[(x, y)] = d / p
    data[(y, y)] = d / p

unitcost, avgmph, costpm, limit = map(int, sys.stdin.readline().split(' '))

paths = travpath(0, None, 0)

for p, ep, c, ec in paths:
    actp = list(reversed(p))
    pp = zip(actp, actp[1:])
    print len(pp)
    for a, b in pp:
        print a, b

