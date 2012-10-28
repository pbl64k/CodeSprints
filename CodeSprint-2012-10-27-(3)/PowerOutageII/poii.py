
import sys

n, m = map(int, sys.stdin.readline().split(' '))

es = {}

for i in range(n):
    es[(i, i)] = 0

for i in range(m):
    i, j, d = map(int, sys.stdin.readline().split(' '))
    i -= 1
    j -= 1
    es[(i, j)] = d
    es[(j, i)] = d

ls = map(int, sys.stdin.readline().split(' '))
gs = map(int, sys.stdin.readline().split(' '))

paths = {}

for (i, j), d in es.iteritems():
    paths[(i, j)] = d

for k in range(n):
    for i in range(n):
        for j in range(n):
            if paths.has_key((i, j)):
                bp = paths[(i, j)]
            else:
                bp = None
            if paths.has_key((i, k)) and paths.has_key((k, j)):
                if bp is None or (paths[(i, k)] + paths[(k, j)] < bp):
                    paths[(i, j)] = paths[(i, k)] + paths[(k, j)]

lds = [[] for i in range(n)]

for (i, j), d in paths.iteritems():
    lds[i].append((d, j))

lds = [sorted(x, lambda a, b: cmp(a[0], b[0])) for x in lds]

mgs = range(n)
mngs = []
mls = range(n)

def rmval(g):
    res = gs[g]
    for lix in range(n):
        if mls[lix] == g:
            if len(lds[lix]) == 1:
                return 0
            df = (lds[lix][1][0] - lds[lix][0][0]) * ls[lix]
            res -= df
    return res

def rm(g):
    global mgs
    mgs = [x for x in mgs if x != g]
    mngs.append(g)
    for lix in range(n):
        lds[lix] = [x for x in lds[lix] if x[1] != g]
        if mls[lix] == g:
            mls[lix] = lds[lix][0][1]

def addval0(g):
    res = -gs[g]
    for lix in range(n):
        if paths.has_key((g, lix)) and paths[(g, lix)] < lds[lix][0][0]:
            df = (lds[lix][0][0] - paths[(g, lix)]) * ls[lix]
            res += df
    return res

def add0(g):
    global mngs
    mngs = [x for x in mngs if x != g]
    mgs.append(g)
    for lix in range(n):
        if paths.has_key((g, lix)):
            d = paths[(g, lix)]
            if d < lds[lix][0][0]:
                mls[lix] = g
            lds0 = lds[lix]
            lds[lix] = []
            appended = False
            for c, j in lds0:
                if not appended:
                    if d < c:
                        lds[lix].append((d, g))
                        appended = True
                lds[lix].append((c, j))

while True:
    changed = False
    remove = None
    removeval = 0
    for gen in mgs:
        r = rmval(gen)
        if r > removeval:
            remove = gen
            removeval = r
    if remove is not None:
        rm(remove)
        changed = True
    add = None
    addval = 0
    for gen in mngs:
        r = addval0(gen)
        if r > addval:
            add = gen
            addval = r
    if add is not None:
        add0(add)
        changed = True
    if not changed:
        break

print len(mgs)
print ' '.join(map(lambda x: str(x + 1), mgs))
print ' '.join(map(lambda x: str(x + 1), mls))

