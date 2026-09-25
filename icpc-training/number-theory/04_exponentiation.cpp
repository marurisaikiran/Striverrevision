// CSES 1095 - Exponentiation
// Binary exponentiation: a^b in O(log b) multiplications.
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
        long long a, b;
        cin >> a >> b;
        cout << power(a, b, MOD) << '\n';     // 0^0 = 1 by the loop
    }
    return 0;
}
