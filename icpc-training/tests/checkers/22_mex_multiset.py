def mex(s):
    m = 0
    while m in s:
        m += 1
    return m

def check(inp, expected, got):
    it = iter(inp.split()); t = int(next(it))
    exp = expected.split(); out = got.split(); ei = oi = 0
    for _ in range(t):
        n = int(next(it)); a = [int(next(it)) for _ in range(n)]
        want = exp[ei].upper(); ei += 1 + (want == "YES")
        if oi >= len(out) or out[oi].upper() != want:
            return False
        oi += 1
        if want == "YES":
            s = out[oi].upper(); oi += 1
            if len(s) != n or set(s) - set("ABC"):
                return False
            ms = [mex({a[i] for i in range(n) if s[i] == c}) for c in "ABC"]
            if sum(ms) < 2 * max(ms):
                return False
    return oi == len(out)
