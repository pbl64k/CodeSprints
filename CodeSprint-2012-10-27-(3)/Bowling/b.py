
import sys

m = 1000000007L

mm = {}

def f(fr, sc, n1, n2):
    #print fr, sc, n1, n2
    if not mm.has_key((fr, sc, n1, n2)):
        mm[(fr, sc, n1, n2)] = ff(fr, sc, n1, n2)
    return mm[(fr, sc, n1, n2)]

def ff(fr, sc, n1, n2):
    if fr < 0 or sc < 0 or sc > 30 * fr:
        return 0
    elif n1 is not None:
        if n2 is not None:
            return ff12(fr, sc, n1, n2)
        return ff1(fr, sc, n1)
    elif fr == 1:
        if sc > 20:
            return 1
        else:
            # spare + strike
            return sc + 1
    elif sc == 30 * fr:
        return 1
    elif sc == 0:
        return 1
    elif fr == 0:
        return 0
    else:
        cnt = 0
        # 0 - 9
        for tsc in range(10):
            cnt = (cnt + (((tsc + 1) * f(fr - 1, sc - tsc, None, None)) % m)) % m
        #print ' ', fr, sc, cnt
        #
        for tsc in range(11):
            cnt = (cnt + ((10 * f(fr - 1, sc - 10 - tsc, tsc, None)) % m)) % m
        #print '/', fr, sc, cnt
        #
        cnt = (cnt + f(fr, sc, 10, None)) % m
        #print 'X', fr, sc, cnt
        return cnt

def ff1(fr, sc, n1):
    if fr == 0 and sc == 0:
        return 1
    elif sc < n1:
        return 0
    elif n1 == 10 and fr > 1:
        cnt = 0
        for tsc in range(10):
            cnt = (cnt + (((tsc + 1) * f(fr - 2, sc - 10 - (tsc * 2), None, None)) % m)) % m
        for tsc in range(10):
            cnt = (cnt + f(fr - 1, sc - 20, tsc, 10 - tsc)) % m
        for tsc in range(11):
            cnt = (cnt + f(fr - 1, sc - 20 - tsc, 10, tsc)) % m
        return cnt
    elif n1 == 10 and fr == 1:
        cnt = 0
        for tsc in range(10):
            cnt = (cnt + (((tsc + 1) * f(fr - 1, sc - 10 - tsc, None, None)) % m)) % m
        for tsc in range(10):
            cnt = (cnt + f(fr - 1, sc - 20, tsc, 10 - tsc)) % m
        for tsc in range(11):
            cnt = (cnt + f(fr - 1, sc - 20 - tsc, 10, tsc)) % m
        return cnt
    else:
        cnt = 0
        for tsc in range(10 - n1):
            cnt = (cnt + f(fr - 1, sc - n1 - tsc, None, None)) % m
        for tsc in range(11):
            cnt = (cnt + f(fr - 1, sc - 10 - tsc, tsc, None)) % m
        return cnt

def ff12(fr, sc, n1, n2):
    if fr == 0 and sc == 0:
        return 1
    elif sc < n1 + n2:
        return 0
    elif n1 == 10:
        if n2 == 10:
            cnt = 0
            for tsc in range(11):
                cnt = (cnt + f(fr - 1, sc - 20 - tsc, n2, tsc)) % m
            return cnt
        else:
            cnt = 0
            for tsc in range(11 - n2):
                cnt = (cnt + f(fr - 1, sc - 10 - n2 - tsc, n2, tsc)) % m
            return cnt
    elif n1 + n2 == 10:
        cnt = 0
        for tsc in range(11):
            cnt = (cnt + f(fr - 1, sc - 10 - tsc, tsc, None)) % m
        return cnt
    else:
        return f(fr - 1, sc - n1 - n2, None, None)

t = int(sys.stdin.readline())

for i in range(t):
    n, k = map(int, sys.stdin.readline().split(' '))
    print f(n, k, None, None)
    
