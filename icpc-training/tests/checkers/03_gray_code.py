def check(inp, expected, got):
    n = int(inp.split()[0]); rows = got.split()
    if len(rows) != 1 << n or len(set(rows)) != 1 << n: return False
    if any(len(r) != n or set(r) - set("01") for r in rows): return False
    return all(sum(a != b for a, b in zip(rows[i], rows[i + 1])) == 1 for i in range(len(rows) - 1))
