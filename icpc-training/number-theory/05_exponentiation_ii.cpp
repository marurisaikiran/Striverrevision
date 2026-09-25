// CSES 1712 - Exponentiation II
// Fermat: for p prime and p !| a, a^E = a^(E mod (p-1)) (mod p).
// Here 0 <= a < p, so only a = 0 needs care: 0^E = 1 iff E = b^c = 0.
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
    while (n--) {
        long long a, b, c;
        cin >> a >> b >> c;
        long long ans;
        if (a == 0) {
            bool expIsZero = (b == 0 && c > 0);   // b^c = 0 only for b = 0, c >= 1
            ans = expIsZero ? 1 : 0;
        } else {
            ans = power(a, power(b, c, MOD - 1), MOD);
        }
        cout << ans << '\n';
    }
    return 0;
}
