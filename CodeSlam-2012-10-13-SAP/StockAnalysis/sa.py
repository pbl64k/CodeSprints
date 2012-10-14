
import sys

def beta(a, b):
    return (b[1] - a[1]) / (b[0] - a[0])

def betarange(a, b, d):
    return (beta(a, (b[0], b[1] - d)), beta(a, (b[0], b[1] + d)))

def findbest(ps, i, N, d):
    j = i + d
    minbeta, maxbeta = betarange(ps[i], ps[j], D)
    bestj = j
    while True:
        j += d
        if j == N + d:
            return bestj
        cminbeta, cmaxbeta = betarange(ps[i], ps[j], D)
        minbeta = max(minbeta, cminbeta)
        maxbeta = min(maxbeta, cmaxbeta)
        if minbeta > maxbeta:
            return bestj
        else:
            curbeta = beta(ps[i], ps[j])
            if minbeta <= curbeta and curbeta <= maxbeta:
                bestj = j

N, D = map(int, sys.stdin.readline().split(' '))

D = float(D)

ps = []

for i in range(N):
    ps.append(map(float, sys.stdin.readline().split(' ')))

ps = sorted(ps, lambda x, y: cmp(x[0], y[0]))

il = 0
ir = N - 1
rsl = [ps[il]]
rsr = [ps[ir]]

while il != ir:
    il0 = findbest(ps, il, ir, 1)
    ir0 = findbest(ps, ir, il, -1)
    if il0 - il >= ir - ir0:
        rsl.append(ps[il0])
        il = il0
    else:
        rsr.append(ps[ir0])
        ir = ir0

rs = rsl + list(reversed(rsr[:-1]))

print len(rs)

for p in rs:
    print int(p[0]), int(p[1])

