#!/usr/bin/env python3
"""Random stress tests: each greedy solution vs an exhaustive Python reference.
Run tests/run_tests.py first (it builds the binaries into tests/.build)."""
import heapq, itertools, os, random, subprocess, sys
from collections import Counter
B = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), ".build")
R = random.Random(2026)

def run(name, inp):
    return subprocess.run([os.path.join(B, "greedy_" + name)], input=inp,
                          capture_output=True, text=True).stdout.split()

# ---------- exhaustive references ----------
def boss(a):
    best = 0
    for p in set(itertools.permutations(a)):
        s = p[0]
        for i in range(1, len(p)):
            s += p[i]
            if p[i] == p[i - 1]: break
        best = max(best, s)
    return best

def wormhole(a):
    best = -1
    for k in range(3, len(a) + 1):
        for c in itertools.combinations(a, k):
            if 2 * max(c) < sum(c): best = max(best, k)
    return best

def towers(k):  # exact via DP over all placements (small n)
    best = [len(k)]
    def go(i, tops):
        if len(tops) >= best[0]: return
        if i == len(k): best[0] = len(tops); return
        for j, t in enumerate(tops):
            if k[i] < t: go(i + 1, tops[:j] + [k[i]] + tops[j + 1:])
        go(i + 1, tops + [k[i]])
    go(0, []); return best[0]

def coin(x):
    sums = {sum(c) for r in range(len(x) + 1) for c in itertools.combinations(x, r)}
    s = 1
    while s in sums: s += 1
    return s

def tasks(t):
    best = None
    for p in itertools.permutations(t):
        now = rew = 0
        for a, d in p: now += a; rew += d - now
        best = rew if best is None else max(best, rew)
    return best

def delcat(a, c):
    from functools import lru_cache
    @lru_cache(None)
    def go(t):
        if not t: return 0
        best = None
        for i in range(len(t)):
            v = t[i] - c + go(t[:i] + t[i + 1:]); best = v if best is None else max(best, v)
            if i + 1 < len(t):
                v = max(t[i], t[i + 1]) - c + go(t[:i] + t[i + 2:]); best = max(best, v)
        return best
    return go(tuple(a))

def reduction(a, k):
    from functools import lru_cache
    @lru_cache(None)
    def go(t):
        best = None
        for i in range(len(t)):
            for j in range(i + 1, len(t)):
                if min(t[i], t[j]) > k:
                    u = list(t); u[i] -= 1; u[j] -= 1; v = go(tuple(sorted(u)))
                    best = v if best is None else max(best, v)
        return sum(t) if best is None else best
    return go(tuple(sorted(a)))

def crackers(n, m, shops):
    out = []
    for i in range(1, n + 1):
        best = None
        for j in range(1, i + 1):
            for k in range(i, n + 1):
                if len(set().union(*shops[j - 1:k])) == m:
                    key = (k - j, j)
                    if best is None or key < best: best = key
                    break
        out += [best[1], best[1] + best[0]]
    return out

def bms(a):  # Dijkstra over collections of arrays (reconstructed cost model)
    srt = lambda x: all(x[i] <= x[i + 1] for i in range(len(x) - 1))
    start = (tuple(a),); dist = {start: 0}; pq = [(0, start)]
    while pq:
        d, st = heapq.heappop(pq)
        if d > dist[st]: continue
        if len(st) == 1 and srt(st[0]): return d
        L = list(st); moves = []
        for i, x in enumerate(L):
            for c in range(1, len(x)):
                moves.append((min(c, len(x) - c), L[:i] + L[i + 1:] + [x[:c], x[c:]]))
        for i in range(len(L)):
            for j in range(i + 1, len(L)):
                if srt(L[i]) and srt(L[j]):
                    rest = [L[q] for q in range(len(L)) if q not in (i, j)]
                    moves.append((len(L[i]) + len(L[j]), rest + [tuple(sorted(L[i] + L[j]))]))
        for w, ns in moves:
            ns = tuple(sorted(ns))
            if d + w < dist.get(ns, 1 << 60): dist[ns] = d + w; heapq.heappush(pq, (d + w, ns))

def mst(n, A, edges):  # Prim on the complete graph
    INF = 1 << 60
    w = [[abs(A[i] - A[j]) for j in range(n)] for i in range(n)]
    for u, v in edges: w[u - 1][v - 1] = w[v - 1][u - 1] = 0
    used = [False] * n; d = [INF] * n; d[0] = 0; tot = 0
    for _ in range(n):
        u = min((i for i in range(n) if not used[i]), key=lambda i: d[i])
        used[u] = True; tot += d[u]
        for v in range(n):
            if not used[v]: d[v] = min(d[v], w[u][v])
    return tot

def coins(X, Y, Z, P):
    best = 0; n = X + Y + Z
    for g in itertools.combinations(range(n), X):
        rest = [i for i in range(n) if i not in g]
        for s in itertools.combinations(rest, Y):
            b = [i for i in rest if i not in s]
            best = max(best, sum(P[i][0] for i in g) + sum(P[i][1] for i in s) + sum(P[i][2] for i in b))
    return best

def jai(n, P):  # brute: game solved by backward induction on "wanted" sets is the claim;
    # independent check: simulate final assignment rule directly on sets of triples
    taken = set(); ans = [0] * n
    for i in range(n - 1, -1, -1):
        cand = [s for s in range(1, 5 * n - 1) if not {s, s + 1, s + 2} & taken]
        good = [s for s in cand if s >= P[i]]
        s = min(good) if good else min(cand)
        ans[i] = s; taken |= {s, s + 1, s + 2}
    return ans

# ---------- drivers ----------
def check(name, cases):
    bad = 0
    for inp, want in cases:
        got = run(name, inp)
        if got != [str(x) for x in want]:
            bad += 1
            if bad <= 3: print("MISMATCH", name, repr(inp), want, got)
    print(f"{name:32s} {len(cases) - bad}/{len(cases)}")
    return bad

bad = 0
C = []
for _ in range(300):
    a = [R.randint(1, 3) for _ in range(R.randint(1, 7))]
    C.append((f"1\n{len(a)}\n{' '.join(map(str, a))}\n", [boss(a)]))
bad += check("03_boss_fight", C)
C = []
for _ in range(300):
    a = [R.randint(1, 20) for _ in range(R.randint(3, 8))]
    C.append((f"1\n{len(a)}\n{' '.join(map(str, a))}\n", [wormhole(a)]))
bad += check("11_creating_a_wormhole", C)
C = []
for _ in range(300):
    k = [R.randint(1, 6) for _ in range(R.randint(1, 8))]
    C.append((f"{len(k)}\n{' '.join(map(str, k))}\n", [towers(k)]))
bad += check("13_towers", C)
C = []
for _ in range(300):
    x = [R.randint(1, 12) for _ in range(R.randint(1, 8))]
    C.append((f"{len(x)}\n{' '.join(map(str, x))}\n", [coin(x)]))
bad += check("14_missing_coin_sum", C)
C = []
for _ in range(200):
    t = [(R.randint(1, 9), R.randint(1, 30)) for _ in range(R.randint(1, 6))]
    C.append((f"{len(t)}\n" + "".join(f"{a} {d}\n" for a, d in t), [tasks(t)]))
bad += check("09_tasks_and_deadlines", C)
C = []
for _ in range(300):
    a = [R.randint(-6, 6) for _ in range(R.randint(1, 7))]; c = R.randint(0, 7)
    C.append((f"1\n{len(a)} {c}\n{' '.join(map(str, a))}\n", [delcat(a, c)]))
bad += check("20_delete_and_concatenate", C)
C = []
for _ in range(300):
    k = R.randint(1, 3); a = [R.randint(1, 7) for _ in range(R.randint(1, 5))]
    C.append((f"1\n{len(a)} {k}\n{' '.join(map(str, a))}\n", [reduction(a, k)]))
bad += check("23_reduction_game", C)
C = []
for _ in range(300):
    n = R.randint(1, 7); m = R.randint(1, 4)
    shops = [set(R.sample(range(1, m + 1), R.randint(0, m))) for _ in range(n)]
    if len(set().union(*shops)) < m: shops[R.randrange(n)] |= set(range(1, m + 1))
    txt = f"1\n{n} {m}\n" + "".join(f"{len(s)} {' '.join(map(str, sorted(s)))}\n" for s in shops)
    C.append((txt, crackers(n, m, shops)))
bad += check("25_cracker_shops", C)
C = []
for _ in range(300):
    n = R.randint(1, 8); P = [R.randint(1, 5 * n) for _ in range(n)]
    C.append((f"1\n{n}\n{' '.join(map(str, P))}\n", jai(n, P)))
bad += check("26_jai_hanuman", C)
C = []
for _ in range(120):
    a = [R.randint(1, 4) for _ in range(R.randint(1, 6))]
    C.append((f"1\n{len(a)}\n{' '.join(map(str, a))}\n", [bms(a)]))
bad += check("27_break_merge_and_sort", C)
C = []
for _ in range(300):
    n = R.randint(1, 7); A = [R.randint(0, 20) for _ in range(n)]
    E = [(R.randint(1, n), R.randint(1, n)) for _ in range(R.randint(0, n))]
    txt = f"1\n{n} {len(E)}\n{' '.join(map(str, A))}\n" + "".join(f"{u} {v}\n" for u, v in E)
    C.append((txt, [mst(n, A, E)]))
bad += check("28_min_weight_bipartition", C)
C = []
for _ in range(150):
    X, Y, Z = R.randint(1, 2), R.randint(1, 2), R.randint(1, 2)
    P = [[R.randint(1, 20) for _ in range(3)] for _ in range(X + Y + Z)]
    C.append((f"{X} {Y} {Z}\n" + "".join(" ".join(map(str, p)) + "\n" for p in P), [coins(X, Y, Z, P)]))
bad += check("29_coins", C)
sys.exit(1 if bad else 0)
