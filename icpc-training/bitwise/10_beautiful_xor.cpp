// Codeforces 2162C - Beautiful XOR
// Every reachable value stays below 2^(hb(a)+1), so b with a higher top bit
// is impossible. Otherwise: 0 moves if a = b, 1 move if a^b <= a, else two:
//   x1 = a ^ ones  (a becomes all-ones below its top bit), x2 = ones ^ b.
#include <iostream>
using namespace std;

int highBit(long long v) { return 63 - __builtin_clzll(v); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long a, b;
        cin >> a >> b;
        if (highBit(b) > highBit(a)) { cout << -1 << '\n'; continue; }
        if (a == b) { cout << 0 << "\n\n"; continue; }
        if ((a ^ b) <= a) { cout << 1 << '\n' << (a ^ b) << '\n'; continue; }
        long long ones = (1LL << (highBit(a) + 1)) - 1;
        cout << 2 << '\n' << (a ^ ones) << ' ' << (ones ^ b) << '\n';
    }
    return 0;
}
