
import sys
import random

MM = 142857

def product(l):
    return reduce(lambda x, y: x * y, l)

c = {}

def exteuc(a, b):
    if not c.has_key((a, b)):
        x1 = 1
        y1 = 0
        r1 = a
        x2 = 0
        y2 = 1
        r2 = b
        r3 = 1
        
        while r3 > 0:
            q = r1 / r2
            x3 = x1 - (q * x2)
            y3 = y1 - (q * y2)
            r3 = (x3 * a) + (y3 * b)
        
            x1 = x2
            y1 = y2
            r1 = r2
            x2 = x3
            y2 = y3
            r2 = r3
        
        c[(a, b)] = y1

    return c[(a, b)]

def crt(l):
    m0s = [x[0] for x in l]
    a0s = [x[1] for x in l]
    m = product(m0s)
    x = 0
    for i in range(len(m0s)):
        x += a0s[i] * (m / m0s[i]) * (exteuc(m0s[i], (m / m0s[i]) % m0s[i]) % m0s[i])
    return x

def lcp(x, p):
    r = []
    while x > 0:
        r.append(x % p)
        x /= p
    return r

def lpr(xs, p, q):
    x0s = xs + [0 for i in range(q - 1)]
    x0s = x0s[1:]
    x1s = xs
    for i in range(q - 1):
        x1s = [x1 + (x0 * (p ** (i + 1))) for x1, x0 in zip(x1s, x0s[i:])]
    return x1s

fpp = {}

def fp(x, p, pq):
    if not fpp.has_key((x, p, pq)):
        r = 1
        for i in range(2, x + 1):
            if i % p != 0:
                r = (r * i) % pq
        fpp[(x, p, pq)] = r
    return fpp[(x, p, pq)]

def ces0(ms, rs, p):
    c = []
    c0 = 0
    for m, r in zip(ms, rs):
        if m + r + c0 >= p:
            c0 = 1
            c.append(1)
        else:
            c0 = 0
            c.append(0)
    cc = []
    cc0 = 0
    for i in range(len(c)):
        cc0 += c[len(c) - i - 1]
        cc.append(cc0)
    cc.reverse()
    return cc

def lc1(p, n, m):
    r = n - m
    N0s = lcp(n, p)
    M0s = lcp(m, p)
    while len(M0s) < len(N0s):
        M0s.append(0)
    R0s = lcp(r, p)
    while len(R0s) < len(N0s):
        R0s.append(0)
    es = ces0(M0s, R0s, p)
    while len(es) < 1:
        es.append(0)
    #print n0s
    #print m0s
    #print r0s
    #print N0s
    #print M0s
    #print R0s
    #print 'es', es
    res = 1
    for i in range(len(N0s)):
        res = (res * fp(N0s[i], p, p)) % p
    res0 = 1
    for i in range(len(N0s)):
        res = (res * (exteuc(p, fp(M0s[i], p, p) % p) % p)) % p
        res = (res * (exteuc(p, fp(R0s[i], p, p) % p) % p)) % p
    res = (res * (p ** es[0])) % p
    res = (res * ((-1) ** es[0])) % p
    return res

def lc(p, q, n, m):
    pq = p ** q
    r = n - m
    n0s = lcp(n, p)
    N0s = lpr(n0s, p, q)
    m0s = lcp(m, p)
    while len(m0s) < len(n0s):
        m0s.append(0)
    M0s = lpr(m0s, p, q)
    while len(M0s) < len(N0s):
        M0s.append(0)
    r0s = lcp(r, p)
    while len(r0s) < len(n0s):
        r0s.append(0)
    R0s = lpr(r0s, p, q)
    while len(R0s) < len(N0s):
        R0s.append(0)
    es = ces0(m0s, r0s, p)
    while len(es) < q:
        es.append(0)
    #print n0s
    #print m0s
    #print r0s
    #print N0s
    #print M0s
    #print R0s
    #print 'es', es
    res = 1
    for i in range(len(n0s)):
        res = (res * fp(N0s[i], p, pq)) % pq
    res0 = 1
    for i in range(len(n0s)):
        res = (res * (exteuc(pq, fp(M0s[i], p, pq) % pq) % pq)) % pq
        res = (res * (exteuc(pq, fp(R0s[i], p, pq) % pq) % pq)) % pq
    res = (res * (p ** es[0])) % pq
    res = (res * ((-1) ** es[q - 1])) % pq
    return res

def llc(n, k):
    #return crt([(27, lc(3, 3, n, k)), (11, lc(11, 1, n, k)), (13, lc(13, 1, n, k)), (37, lc(37, 1, n, k))]) % MM
    return crt([(27, lc(3, 3, n, k)), (11, lc1(11, n, k)), (13, lc1(13, n, k)), (37, lc1(37, n, k))]) % MM

def bc(n, k):
    if k == 0 or k == n:
        return 1
    return product(range(n - k + 1, n + 1)) / product(range(1, k + 1))

#for i in range(100000):
#    n = random.randint(1, 1000000000)
#    k = random.randint(n, 1000000000)
#    print llc(n, k)
#
#exit()

#alarms = 0
#
#for k in range(1, 201):
#    for n in range(k, 201):
#        a = bc(n, k) % MM
#        b = llc(n, k)
#        if a != b:
#            print n, k, a, b
#            print 'Alarm!'
#            alarms += 1
#            #exit()
#
#print 'Alarms:', alarms
#
#exit()

t = int(sys.stdin.readline())

for i in range(t):
    n, k = map(int, sys.stdin.readline().split(' '))
    print llc(n, k)

