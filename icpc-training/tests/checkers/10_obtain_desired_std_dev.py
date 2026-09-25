import math
def check(inp, expected, got):
    it = iter(inp.split()); t = int(next(it)); lines = got.strip().split("\n")
    if len(lines) != t: return False
    for line in lines:
        n, s = int(next(it)), int(next(it)); v = list(map(float, line.split()))
        if v == [-1.0] and n == 1: 
            if s == 0: return False
            continue
        if v == [-1.0] and n > 1: return False
        if len(v) != n or any(abs(x) > 1e8 for x in v): return False
        mu = sum(v) / n
        if abs(math.sqrt(sum((x - mu) ** 2 for x in v) / n) - s) > 1e-2: return False
    return True
