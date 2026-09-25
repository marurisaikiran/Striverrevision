#!/usr/bin/env python3
"""Random stress tests for the number-theory chapter (build first)."""
import builtins, functools
print = functools.partial(builtins.print, flush=True)
import itertools, math, os, random, subprocess, sys, importlib
from functools import lru_cache
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
B = os.path.join(ROOT, ".build"); R = random.Random(11); P = 10 ** 9 + 7
sys.path.insert(0, os.path.join(ROOT, "checkers"))

def run(name, inp):
    return subprocess.run([os.path.join(B, "number-theory_" + name)], input=inp,
                          capture_output=True, text=True).stdout.split()

def cmp(name, inp, want):
    got = run(name, inp); want = [str(w) for w in want]
    bad = sum(g != w for g, w in zip(got, want)) + abs(len(got) - len(want))
    print(f"{name:32s} {len(want) - min(bad, len(want))}/{len(want)}"); return bad

bad = 0
q = [(R.randint(0, 20), R.randint(0, 6), R.randint(0, 3)) for _ in range(500)] + [(0, 0, 0), (0, 0, 5), (0, 3, 0), (5, 0, 0)]
bad += cmp("05_exponentiation_ii", f"{len(q)}\n" + "".join(f"{a} {b} {c}\n" for a, b, c in q),
           [pow(a, b ** c, P) for a, b, c in q])
xs = [R.randint(1, 10 ** 6) for _ in range(300)] + [1, 720720, 999983]
bad += cmp("06_counting_divisors", f"{len(xs)}\n" + "\n".join(map(str, xs)) + "\n",
           [sum(1 for d in range(1, int(x ** .5) + 1) if x % d == 0 for _ in ((0,) if d * d == x else (0, 1))) for x in xs])
w = []; ins = []
for _ in range(100):
    a = [R.randint(1, 60) for _ in range(R.randint(2, 8))]
    ins.append(a); w.append(max(math.gcd(x, y) for x, y in itertools.combinations(a, 2)))
fails = 0
for a, want in zip(ins, w):
    fails += run("07_common_divisors", f"{len(a)}\n{' '.join(map(str, a))}\n") != [str(want)]
print(f"{'07_common_divisors':32s} {100 - fails}/100"); bad += fails
def _sieve(n):
    s = bytearray([1]) * (n + 1); s[0] = s[1] = 0
    for i in range(2, int(n ** .5) + 1):
        if s[i]: s[i * i::i] = bytearray(len(s[i * i::i]))
    return [i for i in range(n + 1) if s[i]]
SMALL = _sieve(10 ** 6 + 100)
def isp(n):  # trial division by primes <= sqrt(n)
    if n < 2: return False
    for q in SMALL:
        if q * q > n: return True
        if n % q == 0: return n == q
    return True
ns = [R.randint(1, 10 ** 6) for _ in range(10)] + [R.randint(10 ** 11, 10 ** 12) for _ in range(6)] + [10 ** 12, 999999999989]
def nxt(n):
    p = n + 1
    while not isp(p): p += 1
    return p
bad += cmp("08_next_prime", f"{len(ns)}\n" + "\n".join(map(str, ns)) + "\n", [nxt(n) for n in ns])
cs = []; ws = []
for _ in range(300):
    n = R.randint(1, 5); A = [R.randint(0, 30) for _ in range(n)]; Bv = [R.randint(1, 12) for _ in range(n)]
    best = min(sum((r - a) % b for a, b in zip(A, Bv)) for r in range(min(Bv)))
    cs.append(f"{n}\n{' '.join(map(str, A))}\n{' '.join(map(str, Bv))}\n"); ws.append(best)
bad += cmp("09_modulo_equality", f"{len(cs)}\n" + "".join(cs), ws)
chk = importlib.import_module("10_obtain_desired_std_dev").check
qs = [(n, s) for n in range(1, 12) for s in (0, 1, 2, 7, 100000)]
inp = f"{len(qs)}\n" + "".join(f"{n} {s}\n" for n, s in qs)
out = subprocess.run([os.path.join(B, "number-theory_10_obtain_desired_std_dev")], input=inp, capture_output=True, text=True).stdout
ok = chk(inp, "", out); print(f"{'10_obtain_desired_std_dev':32s} {'all' if ok else 'FAIL'}"); bad += not ok
cs = []; ws = []
for _ in range(300):
    if R.random() < .5:
        x = R.randint(1, 60); y = R.randint(1, x); seq = [x, y]
        while len(seq) < R.randint(2, 6) and seq[-2] % seq[-1]: seq.append(seq[-2] % seq[-1])
        R.shuffle(seq)
    else:
        seq = [R.randint(1, 20) for _ in range(R.randint(2, 5))]
    ans = None
    for p in itertools.permutations(seq):
        if p[0] >= p[1] and all(p[i] % p[i + 1] == p[i + 2] for i in range(len(p) - 2)): ans = (p[0], p[1]); break
    cs.append(f"{len(seq)}\n{' '.join(map(str, seq))}\n"); ws += list(ans) if ans else [-1]
bad += cmp("11_euclid_sequence", f"{len(cs)}\n" + "".join(cs), ws)
fails = 0
for _ in range(150):
    a = [R.randint(1, 30) for _ in range(R.randint(2, 5))]
    want = max(math.gcd(*(a[:i] + [v] + a[i + 1:])) if len(a) > 1 else v for i in range(len(a)) for v in range(1, 61))
    fails += run("12_gcd_on_blackboard", f"{len(a)}\n{' '.join(map(str, a))}\n") != [str(want)]
print(f"{'12_gcd_on_blackboard':32s} {150 - fails}/150"); bad += fails
PR = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]; fails = 0
for _ in range(150):
    n = R.randint(1, 3000); ps = R.sample(PR, R.randint(1, 5)); ps = [p for p in ps if p <= n] or [2]
    if n < 2: n = 2
    want = sum(1 for x in range(1, n + 1) if any(x % p == 0 for p in ps))
    fails += run("13_prime_multiples", f"{n} {len(ps)}\n{' '.join(map(str, ps))}\n") != [str(want)]
print(f"{'13_prime_multiples':32s} {150 - fails}/150"); bad += fails
fails = 0; sig = [0] * 3001
for d in range(1, 3001):
    for m in range(d, 3001, d): sig[m] += d
pref = list(itertools.accumulate(sig))
for n in list(range(1, 60)) + [R.randint(60, 3000) for _ in range(60)]:
    fails += run("14_sum_of_divisors", f"{n}\n") != [str(pref[n] % P)]
print(f"{'14_sum_of_divisors':32s} {119 - fails}/119"); bad += fails
fails = 0
for _ in range(150):
    fac = {p: R.randint(1, 4) for p in R.sample(PR[:6], R.randint(1, 4))}
    ds = [math.prod(p ** e for p, e in zip(fac, es)) for es in itertools.product(*[range(k + 1) for k in fac.values()])]
    want = [len(ds) % P, sum(ds) % P, math.prod(ds) % P]
    fails += run("15_divisor_analysis", f"{len(fac)}\n" + "".join(f"{p} {k}\n" for p, k in fac.items())) != list(map(str, want))
print(f"{'15_divisor_analysis':32s} {150 - fails}/150"); bad += fails
cs = []; ws = []
for _ in range(200):
    n = R.randint(2, 4); a = [R.randint(1, 12) for _ in range(n)]
    def pg(v): return [math.gcd(v[i], v[i + 1]) for i in range(len(v) - 1)]
    tgt = pg(a); best = 0
    for choice in itertools.product(*[range(1, x + 1) for x in a]):
        if pg(list(choice)) == tgt: best = max(best, sum(c != x for c, x in zip(choice, a)))
    cs.append(f"{n}\n{' '.join(map(str, a))}\n{' '.join(map(str, a))}\n"); ws.append(best)
bad += cmp("16_a_simple_gcd_problem", f"{len(cs)}\n" + "".join(cs), ws)
@lru_cache(None)
def good(x, d):
    if x % d == 0: return True
    for x1 in range(1, x + 1):
        for x2 in range(x1, x + 1):
            x3 = x - x1 - x2
            if x3 < x2: break
            if good(x1, d) and good(x3, d): return True
    return False
cs = []; ws = []
for _ in range(300):
    n = R.randint(1, 12); a = [R.randint(1, n) for _ in range(n)]; k = R.randint(0, n - 1)
    best = max(d for d in range(1, n + 1) if sum(not good(x, d) for x in a) <= k)
    cs.append(f"{n} {k}\n{' '.join(map(str, a))}\n"); ws.append(best)
bad += cmp("17_maximum_gcd_on_whiteboard", f"{len(cs)}\n" + "".join(cs), ws)
qs = [(R.randint(1, 3000), R.randint(1, 3000)) for _ in range(150)]
def occ(n, k):
    s = "".join(map(str, range(1, n + 1))); t = str(k)
    return sum(1 for i in range(len(s)) if s.startswith(t, i))
bad += cmp("18_substring_problem", f"{len(qs)}\n" + "".join(f"{n} {k}\n" for n, k in qs), [occ(n, k) for n, k in qs])
fails = 0
for _ in range(60):
    s = "".join(R.choice("0123456789") for _ in range(R.randint(1, 40)))
    qq = [(m, R.randint(0, m - 1)) for m in (R.randint(1, 60) for _ in range(5))]
    want = [sum(1 for i in range(len(s)) for j in range(i, len(s)) if int(s[i:j + 1]) % m == l) for m, l in qq]
    fails += run("19_steel_bar_durability", f"{s}\n{len(qq)}\n" + "".join(f"{m} {l}\n" for m, l in qq)) != list(map(str, want))
print(f"{'19_steel_bar_durability':32s} {60 - fails}/60"); bad += fails
cs = []; ws = []
dsum_pref = [0]
for x in range(1, 200001): dsum_pref.append(dsum_pref[-1] + sum(map(int, str(x))))
for _ in range(400):
    runs = [(R.randint(1, 3), R.randint(1, 9))] + [(R.randint(1, 2), R.randint(0, 9)) for _ in range(R.randint(0, 2))]
    N = int("".join(str(d) * l for l, d in runs))
    if N > 200000: continue
    cs.append(f"{len(runs)}\n" + "".join(f"{l} {d}\n" for l, d in runs)); ws.append(dsum_pref[N] % P)
# a huge case checked against the closed form  S(10^k - 1) = 45 k 10^(k-1)
k = 10 ** 18; cs.append(f"1\n{k} 9\n"); ws.append(45 * (k % P) * pow(10, k - 1, P) % P)
bad += cmp("20_isro_digit_sum", f"{len(cs)}\n" + "".join(cs), ws)
sys.exit(1 if bad else 0)
