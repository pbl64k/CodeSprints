
import sys

k = int(sys.stdin.readline())

xs = map(int, sys.stdin.readline().split(' '))

adj = {}

for i in range(k):
    s = sys.stdin.readline()
    for j in range(len(s)):
        if s[j] == 'Y':
            adj[(i, j)] = True
            adj[(j, i)] = True

visited = [False for i in range(k)]
comps = [0 for i in range(k)]
ccs = []

for i in range(k):
    if visited[i]:
        continue
    q = [i]
    cc = []
    while len(q) > 0:
        v = q.pop()
        if visited[v]:
            continue
        visited[v] = True
        comps[v] = i
        cc.append(v)
        for j in range(k):
            if adj.has_key((v, j)) and not visited[j]:
                q.append(j)
    ccs.append(cc)

for cc in ccs:
    cc = sorted(cc)
    ws = sorted([xs[i] for i in cc])
    xs0 = xs
    for ix, w in zip(cc, ws):
        xs0[ix] = w
    xs = xs0

print ' '.join(map(str, xs))

