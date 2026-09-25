// Codeforces 2153B - Bitwise Reversion
// Link: https://codeforces.com/problemset/problem/2153/B
// Bits are independent. If a bit is set in two of x, y, z (say x = a&b and
// y = b&c), then a, b, c all have it, so the third AND has it too.
// => impossible exactly when some bit is set in exactly two of x, y, z.
#include <iostream>
using namespace std;

bool possible(long long x, long long y, long long z) {
    long long exactlyTwo = (x & y & ~z) | (x & z & ~y) | (y & z & ~x);
    return exactlyTwo == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long x, y, z;
        cin >> x >> y >> z;
        cout << (possible(x, y, z) ? "YES" : "NO") << '\n';
    }
    return 0;
}
