// CSES 3396 - Next Prime
// Prime gaps below 1e12 are tiny (< 600), so test n+1, n+2, ... with a
// deterministic Miller-Rabin (bases 2..37 are exact for 64-bit integers).
#include <cstdint>
#include <iostream>
using namespace std;

using u64 = uint64_t;
using u128 = unsigned __int128;

u64 mulmod(u64 a, u64 b, u64 m) { return (u128)a * b % m; }

u64 powmod(u64 b, u64 e, u64 m) {
    u64 r = 1;
    b %= m;
    while (e) {
        if (e & 1) r = mulmod(r, b, m);
        b = mulmod(b, b, m);
        e >>= 1;
    }
    return r;
}

bool isPrime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
        if (n % p == 0) return n == p;
    u64 d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }
    for (u64 a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        u64 x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mulmod(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        u64 n;
        cin >> n;
        u64 p = n + 1;
        while (!isPrime(p)) p++;
        cout << p << '\n';
    }
    return 0;
}
