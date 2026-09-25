// Codeforces 2260C - Maximize XOR, Minimize Operations
// Link: https://codeforces.com/problemset/problem/2260/C
// x + y = s never changes and u xor v <= u + v, with equality iff u & v = 0.
// u = 0 already gives s, so the maximum is s. Equality needs u to be a
// submask of s; the fewest moves use the LARGEST submask of s that is <= x.
#include <iostream>
using namespace std;

long long largestSubmaskAtMost(long long s, long long x) {
    long long u = 0;
    for (int b = 30; b >= 0; b--)
        if ((s >> b & 1) && (u | (1LL << b)) <= x) u |= 1LL << b;
    return u;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long x, y;
        cin >> x >> y;
        long long s = x + y;
        cout << s << ' ' << x - largestSubmaskAtMost(s, x) << '\n';
    }
    return 0;
}
