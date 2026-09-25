def check(inp, expected, got):
    M, K = map(int, inp.split()); g = list(map(int, got.split()))
    if expected.split() == ["-1"] or g == [-1]:
        return expected.split() == ["-1"] and g == [-1]
    if len(g) != 1 << (M + 1): return False
    pos = {}
    for i, v in enumerate(g): pos.setdefault(v, []).append(i)
    if sorted(pos) != list(range(1 << M)) or any(len(p) != 2 for p in pos.values()): return False
    px = [0]
    for v in g: px.append(px[-1] ^ v)
    return all(px[j + 1] ^ px[i] == K for i, j in pos.values())
