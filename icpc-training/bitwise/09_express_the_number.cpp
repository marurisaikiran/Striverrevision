// ICPC 2020-21 Amritapuri Preliminary - Express the Number
// (statement reconstructed from the official solution slides; see the book)
// Write n = A1 + (odd powers of two), 0 <= A1 <= x, using the fewest terms.
// While n > x remove the top bit 2^k if k is odd, else remove 2^(k-1)
// (2^k = 2^(k-1) + 2^(k-1) with k-1 odd). Odd n with x = 0 is impossible.
#include <iostream>
using namespace std;

int highBit(unsigned long long v) { return 63 - __builtin_clzll(v); }

long long minTerms(unsigned long long n, unsigned long long x) {
    if (x == 0 && (n & 1)) return -1;
    long long terms = 0;
    while (n > x) {
        int k = highBit(n);
        n -= (k & 1) ? (1ULL << k) : (1ULL << (k - 1));
        terms++;
    }
    return terms + 1;                 // + the free part A1 = n
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        unsigned long long n, x;
        cin >> n >> x;
        cout << minTerms(n, x) << '\n';
    }
    return 0;
}
