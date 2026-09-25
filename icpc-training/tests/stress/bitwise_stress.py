#!/usr/bin/env python3
"""Random / exhaustive stress tests for the bitwise chapter (build first)."""
import itertools, os, random, subprocess, sys
from collections import deque
from functools import lru_cache
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
B = os.path.join(ROOT, ".build"); R = random.Random(7)
sys.path.insert(0, os.path.join(ROOT, "checkers"))

def run(name, inp):
    return subprocess.run([os.path.join(B, "bitwise_" + name)], input=inp,
                          capture_output=True, text=True).stdout

def report(name, bad, tot):
    print(f"{name:36s} {tot - bad}/{tot}"); return bad

bad = 0
# 04 new number system: random binary -> encode -> decode
cases = []; exp = []
for _ in range(300):
    bits = [R.randint(0, 1) for _ in range(R.randint(1, 30))]
    toks = []; flag = None; i = 0
    while i < len(bits):
        j = i
        while j < len(bits) and bits[j] == bits[i]: j += 1
        if flag != bits[i]: toks.append("0" if bits[i] else "00"); flag = bits[i]
        toks.append("0" * (j - i + 2)); i = j
    cases.append(" ".join(toks) + " #"); exp.append(int("".join(map(str, bits)), 2))
got = run("04_new_number_system", "\n".join(cases) + "\n~\n").split()
bad += report("04_new_number_system", sum(g != str(e) for g, e in zip(got, exp)) + abs(len(got) - len(exp)), 300)

# 05 bitwise reversion: brute over a,b,c < 16
ach = {(a & b, b & c, a & c) for a in range(16) for b in range(16) for c in range(16)}
qs = [(x, y, z) for x in range(16) for y in range(16) for z in range(16)]
got = run("05_bitwise_reversion", f"{len(qs)}\n" + "".join(f"{x} {y} {z}\n" for x, y, z in qs)).split()
bad += report("05_bitwise_reversion", sum((g == "YES") != (q in ach) for g, q in zip(got, qs)), len(qs))

# 06 deletion sort: exhaustive game on small arrays
def ds(a):
    @lru_cache(None)
    def go(t):
        if all(t[i] <= t[i + 1] for i in range(len(t) - 1)): return len(t)
        return min(go(t[:i] + t[i + 1:]) for i in range(len(t)))
    return go(tuple(a))
arrs = [[R.randint(1, 5) for _ in range(R.randint(1, 7))] for _ in range(300)]
got = run("06_deletion_sort", f"{len(arrs)}\n" + "".join(f"{len(a)}\n{' '.join(map(str, a))}\n" for a in arrs)).split()
bad += report("06_deletion_sort", sum(g != str(ds(a)) for g, a in zip(got, arrs)), len(arrs))

# 08 jackpot: brute over all splits, N <= 3000
def f(v): return v.bit_length() - 1 + bin(v).count("1") - 1
Ns = list(range(2, 3001))
got = run("08_jackpot", f"{len(Ns)}\n" + "\n".join(map(str, Ns)) + "\n").split()
bad += report("08_jackpot", sum(g != str(min(max(f(a), f(N - a)) for a in range(1, N))) for g, N in zip(got, Ns)), len(Ns))

# 09 express the number: DP over odd powers of two
LIM = 1500; pw = [2 ** k for k in range(1, 12, 2)]; dp = [0] + [10 ** 9] * LIM
for v in range(1, LIM + 1):
    dp[v] = min([dp[v - p] + 1 for p in pw if p <= v] + [10 ** 9])
qs = [(n, x) for n in range(1, LIM + 1) for x in (0, 1, 2, 3, 5, 9, 17, 40, 100)]
def ref(n, x):
    b = min(dp[n - a] for a in range(0, min(x, n) + 1)); return -1 if b >= 10 ** 9 else b + 1
got = run("09_express_the_number", f"{len(qs)}\n" + "".join(f"{n} {x}\n" for n, x in qs)).split()
bad += report("09_express_the_number", sum(g != str(ref(n, x)) for g, (n, x) in zip(got, qs)), len(qs))

# 10 beautiful xor: BFS reachability for a, b < 64, verified by checker
import importlib
chk = importlib.import_module("10_beautiful_xor").check
def reach(a):
    seen = {a}; q = deque([a])
    while q:
        u = q.popleft()
        for x in range(u + 1):
            if u ^ x not in seen: seen.add(u ^ x); q.append(u ^ x)
    return seen
qs = [(a, b) for a in range(1, 64) for b in range(1, 64)]
R_ = {a: reach(a) for a in range(1, 64)}
inp = f"{len(qs)}\n" + "".join(f"{a} {b}\n" for a, b in qs)
exp = "".join(("1\n0\n" if b in R_[a] else "-1\n") for a, b in qs)  # only -1 vs possible matters
got = run("10_beautiful_xor", inp)
bad += report("10_beautiful_xor", 0 if chk(inp, exp, got) else 1, 1)

# 11 67th xor: simulate every removal order
def sim(a):
    best = 0
    for order in itertools.permutations(range(len(a)), len(a) - 1):
        arr = dict(enumerate(a))
        for i in order:
            x = arr.pop(i)
            for j in arr: arr[j] ^= x
        best = max(best, *arr.values())
    return best
arrs = [[R.randint(0, 31) for _ in range(R.randint(2, 5))] for _ in range(200)]
got = run("11_the_67th_xor_problem", f"{len(arrs)}\n" + "".join(f"{len(a)}\n{' '.join(map(str, a))}\n" for a in arrs)).split()
bad += report("11_the_67th_xor_problem", sum(g != str(sim(a)) for g, a in zip(got, arrs)), len(arrs))

# 12 maximize xor: try every k
qs = [(x, y) for x in range(0, 64) for y in range(0, 64)]
def mx(x, y):
    best = max(((x - k) ^ (y + k), -k) for k in range(x + 1)); return f"{best[0]} {-best[1]}"
got = run("12_maximize_xor_minimize_operations", f"{len(qs)}\n" + "".join(f"{x} {y}\n" for x, y in qs)).strip().split("\n")
bad += report("12_maximize_xor_minimize_operations", sum(g.split() != mx(x, y).split() for g, (x, y) in zip(got, qs)), len(qs))

# 13 xor battle: full minimax
def battle(a, s):
    @lru_cache(None)
    def go(i, x):
        if i == len(a): return x != 0
        opts = [go(i + 1, x), go(i + 1, x ^ a[i])]
        return any(opts) if s[i] == "1" else all(opts)
    return 1 if go(0, 0) else 0
cs = []
for _ in range(300):
    n = R.randint(1, 8); cs.append(([R.randint(1, 15) for _ in range(n)], "".join(R.choice("01") for _ in range(n))))
got = run("13_xor_battle", f"{len(cs)}\n" + "".join(f"{len(a)}\n{' '.join(map(str, a))}\n{s}\n" for a, s in cs)).split()
bad += report("13_xor_battle", sum(g != str(battle(a, s)) for g, (a, s) in zip(got, cs)), len(cs))

# 14 xor matching: all M <= 4, K < 40; existence decided by the known characterisation
chk = importlib.import_module("14_xor_matching").check
def exists(M, K):  # brute force for M <= 2, formula otherwise
    if M <= 2:
        vals = [v for v in range(1 << M) for _ in range(2)]
        for p in set(itertools.permutations(vals)):
            if chk(f"{M} {K}", "x", " ".join(map(str, p))): return True
        return False
    return K < (1 << M)
b14 = t14 = 0
for M in range(0, 5):
    for K in range(0, 40):
        t14 += 1; e = exists(M, K)
        if not chk(f"{M} {K}", "0 0" if e else "-1", run("14_xor_matching", f"{M} {K}\n")): b14 += 1
bad += report("14_xor_matching", b14, t14)
sys.exit(1 if bad else 0)
