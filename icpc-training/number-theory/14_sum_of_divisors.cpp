// CSES 1082 - Sum of Divisors
// sum_{i<=n} sigma(i) = sum_{d<=n} d * floor(n/d). floor(n/d) takes only
// O(sqrt n) distinct values; for each block [l, r] with the same q add
// q * (l + ... + r).
#include <iostream>
using namespace std;

const long long MOD = 1'000'000'007LL;
const long long INV2 = (MOD + 1) / 2;

long long rangeSum(long long l, long long r) {        // (l + ... + r) mod p
    long long cnt = (r - l + 1) % MOD, ends = (l + r) % MOD;
    return cnt * ends % MOD * INV2 % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    cin >> n;
    long long ans = 0;
    for (long long l = 1; l <= n;) {
        long long q = n / l, r = n / q;               // largest r with n/r = q
        ans = (ans + q % MOD * rangeSum(l, r)) % MOD;
        l = r + 1;
    }
    cout << ans << '\n';
    return 0;
}
