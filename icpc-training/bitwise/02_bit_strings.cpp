// CSES 1617 - Bit Strings
// Link: https://cses.fi/problemset/task/1617
// Each of the n positions is independently 0 or 1: 2^n strings.
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
    long long n;
    cin >> n;
    cout << power(2, n, MOD) << '\n';
    return 0;
}
