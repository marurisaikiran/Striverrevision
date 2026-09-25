def check(inp, expected, got):
    it = list(map(int, inp.split())); n = it[0]
    iv = [(it[1 + 2 * i], it[2 + 2 * i]) for i in range(n)]
    g = list(map(int, got.split()))
    k = g[0]; rooms = g[1:]
    if k != int(expected.split()[0]) or len(rooms) != n:
        return False
    if any(r < 1 or r > k for r in rooms):
        return False
    by = {}
    for (a, b), r in zip(iv, rooms):
        by.setdefault(r, []).append((a, b))
    for lst in by.values():
        lst.sort()
        if any(lst[i][1] >= lst[i + 1][0] for i in range(len(lst) - 1)):
            return False
    return True
