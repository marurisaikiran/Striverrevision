// ICPC 2014-15 Amritapuri Online - ISRO Digit Sum (run-length encoded N)
// Link: https://github.com/m-e-r-l-i-n/icpc-india/blob/main/src/2014amrita_online.pdf
// Standard digit sum-of-sums, scanning digits of N from the left. At a digit d
// with k digits after it and prefix digit-sum ps, the numbers that branch off
// with a smaller digit c < d contribute
//      d*10^k*ps + 10^k*d(d-1)/2 + d*k*45*10^(k-1).
// A run of `len` equal digits is summed in closed form with geometric series
//      G0 = sum 10^j,  G1 = sum j*10^j  over j = k_min .. k_max.
// Finally add digitsum(N) itself.
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;
using i128 = __int128;
const ll MOD = 1'000'000'007LL;

ll power(ll b, ll e) {               // e >= 0, may be ~1e18
    ll r = 1;
    b %= MOD;
    if (b < 0) b += MOD;
    while (e > 0) {
        if (e & 1) r = (i128)r * b % MOD;
        b = (i128)b * b % MOD;
        e >>= 1;
    }
    return r;
}
ll inv(ll x) { return power(x, MOD - 2); }

// sum_{i=0}^{n-1} 10^i  and  sum_{i=0}^{n-1} i*10^i   (mod p)
ll geo0(ll n) { return (power(10, n) - 1 + MOD) % MOD * inv(9) % MOD; }
ll geo1(ll n) {
    // r (1 - n r^{n-1} + (n-1) r^n) / (1-r)^2 with r = 10
    ll nm = n % MOD, rn1 = power(10, n - 1), rn = power(10, n);
    ll inner = (1 - (i128)nm * rn1 % MOD + (i128)((nm - 1 + MOD) % MOD) * rn % MOD) % MOD;
    inner = (inner + 2 * MOD) % MOD;
    return (i128)10 * inner % MOD * inv(81) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const ll INV10 = inv(10);
    int T;
    cin >> T;
    while (T--) {
        int m;
        cin >> m;
        vector<ll> len(m);
        vector<int> dig(m);
        ll total = 0;                         // total number of digits of N
        for (int i = 0; i < m; i++) { cin >> len[i] >> dig[i]; total += len[i]; }
        ll ans = 0, ps = 0, used = 0;         // ps = digit sum of prefix (mod p)
        for (int i = 0; i < m; i++) {
            ll d = dig[i], n = len[i];
            ll kmax = total - used - 1, kmin = kmax - n + 1;
            // G0 = sum_{j=kmin}^{kmax} 10^j, G1 = sum j 10^j
            ll base = power(10, kmin), g0n = geo0(n), g1n = geo1(n);
            ll G0 = (i128)base * g0n % MOD;
            ll G1 = (i128)base * (((i128)(kmin % MOD) * g0n + g1n) % MOD) % MOD;
            // sum over t of t*10^k with k = kmax - t :  kmax*G0 - G1
            ll T1 = ((i128)(kmax % MOD) * G0 % MOD - G1 + MOD) % MOD;
            ll part = ((i128)ps * G0 + (i128)d * T1) % MOD;       // prefix sums
            part = (i128)part * d % MOD;
            part = (part + (i128)G0 * (d * (d - 1) / 2)) % MOD;    // smaller digits
            part = (part + (i128)d * 45 % MOD * G1 % MOD * INV10) % MOD;  // free tail
            ans = (ans + part) % MOD;
            ps = (ps + (i128)d * (n % MOD)) % MOD;
            used += n;
        }
        ans = (ans + ps) % MOD;               // N itself
        cout << ans << '\n';
    }
    return 0;
}
