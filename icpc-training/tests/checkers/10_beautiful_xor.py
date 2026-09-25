def check(inp, expected, got):
    it = iter(map(int, inp.split())); t = next(it)
    exp = expected.split(); g = list(map(int, got.split())); gi = ei = 0
    for _ in range(t):
        a, b = next(it), next(it)
        e0 = int(exp[ei]); ei += 1 + max(e0, 0)
        k = g[gi]; gi += 1
        if (k == -1) != (e0 == -1): return False
        if k == -1: continue
        if not 0 <= k <= 100: return False
        for x in g[gi:gi + k]:
            if not 0 <= x <= a: return False
            a ^= x
        gi += k
        if a != b: return False
    return gi == len(g)
