// CSES 2182 - Divisor Analysis
// n = prod x_i^k_i.
//   count   = prod (k_i + 1)
//   sum     = prod (x_i^(k_i+1) - 1) / (x_i - 1)
//   product = built incrementally: adding x^k to a number with c divisors
//             and divisor-product P gives P^(k+1) * (x^(k(k+1)/2))^c.
// Exponents are reduced mod p - 1 (Fermat), so c is kept mod p - 1 as well.
#include <iostream>
using namespace std;

const long long MOD = 1'000'000'007LL;

long long power(long long b, long long e, long long m) {
    long long r = 1 % m;
    b %= m;
    while (e > 0) {
        if (e & 1) r = r * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long cnt = 1, cntPhi = 1, sum = 1, prod = 1;   // cntPhi = count mod (p-1)
    for (int i = 0; i < n; i++) {
        long long x, k;
        cin >> x >> k;
        // product first: it needs the divisor count *before* this prime
        long long tri = (__int128)k * (k + 1) / 2 % (MOD - 1);   // k(k+1)/2
        prod = power(prod, (k + 1) % (MOD - 1), MOD) *
               power(power(x, tri, MOD), cntPhi, MOD) % MOD;
        cnt = cnt * ((k + 1) % MOD) % MOD;
        cntPhi = cntPhi * ((k + 1) % (MOD - 1)) % (MOD - 1);
        long long geo = (power(x, k + 1, MOD) - 1 + MOD) % MOD *
                        power(x - 1, MOD - 2, MOD) % MOD;
        sum = sum * geo % MOD;
    }
    cout << cnt << ' ' << sum << ' ' << prod << '\n';
    return 0;
}
