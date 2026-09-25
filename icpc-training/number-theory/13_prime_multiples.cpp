// CSES 2185 - Prime Multiples
// Inclusion-exclusion over the 2^k subsets of primes. A subset whose product
// exceeds n contributes 0 (and stops the multiplication before overflow).
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    int k;
    cin >> n >> k;
    vector<long long> a(k);
    for (auto& x : a) cin >> x;
    long long total = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        long long prod = 1;
        bool tooBig = false;
        for (int i = 0; i < k; i++) {
            if (!(mask >> i & 1)) continue;
            if (prod > n / a[i]) { tooBig = true; break; }
            prod *= a[i];
        }
        if (tooBig) continue;
        long long cnt = n / prod;
        total += (__builtin_popcount(mask) & 1) ? cnt : -cnt;
    }
    cout << total << '\n';
    return 0;
}
