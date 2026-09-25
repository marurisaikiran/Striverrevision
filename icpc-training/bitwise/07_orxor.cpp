// AtCoder ABC197 C - ORXOR
// N <= 20: enumerate the 2^(N-1) ways to cut between neighbours.
// Bit i of mask set <=> cut after position i.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    int best = (1 << 30) + 5;
    for (int mask = 0; mask < (1 << (n - 1)); mask++) {
        int xr = 0, orv = 0;
        for (int i = 0; i < n; i++) {
            orv |= a[i];
            if (i == n - 1 || (mask >> i & 1)) {   // close the current block
                xr ^= orv;
                orv = 0;
            }
        }
        best = min(best, xr);
    }
    cout << best << '\n';
    return 0;
}
