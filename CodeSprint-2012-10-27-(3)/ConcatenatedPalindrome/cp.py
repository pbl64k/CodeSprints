
import string
import sys

def addk(t, s):
    if s == '':
        return
    c = s[0]
    if not t.has_key(c):
        t[c] = {}
    addk(t[c], s[1:])

def palin(s):
    k = len(s)
    for i in range(len(s)):
        palin = True
        for j in range(int((k - i) / 2) + 1):
            if s[j] != s[k - i - j - 1]:
                palin = False
                break
        if palin:
            return (k - i), s[0:(k - i)]

def chk(t, s):
    if s == '':
        return 0, ''
    c = s[0]
    if not t.has_key(c):
        return palin(s)
    cb, cp = chk(t[c], s[1:])
    return 2 + cb, c + cp

def check(ts, ms):
    t = {}
    for s in ts:
        addk(t, s)
    rb, rp = 0, ''
    for s in ms:
        cb, cp = chk(t, s)
        if cb > rb:
            rb, rp = cb, cp
    return rb, rp

n, m = map(int, sys.stdin.readline().split(' '))

strs = []
rstrs = []

for i in range(n):
    s = string.strip(sys.stdin.readline())
    strs.append(s)
    rstrs.append(s[::-1])

lb, lp = check(strs, rstrs)
rb, rp = check(rstrs, strs)

print max(lb, rb)

