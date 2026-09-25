// Codeforces 2156C - Maximum GCD on Whiteboard
// Link: https://codeforces.com/problemset/problem/2156/C
// For a candidate d: a multiple of d is fine; a non-multiple x can be split
// into multiples of d iff x >= 4d (x = d + x2 + t*d with d <= x2 <= t*d).
// So d needs #{x < 4d, d !| x} <= k erasures. Take the largest such d.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> cnt(n + 1, 0), pre(n + 1, 0);
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            cnt[x]++;
        }
        for (int v = 1; v <= n; v++) pre[v] = pre[v - 1] + cnt[v];
        int ans = 1;
        for (int d = n; d >= 1; d--) {
            long long lim = min<long long>(4LL * d - 1, n);
            int below = pre[lim];                          // values < 4d
            int good = 0;
            for (int m = d; m <= lim; m += d) good += cnt[m];   // d, 2d, 3d
            if (below - good <= k) { ans = d; break; }
        }
        cout << ans << '\n';
    }
    return 0;
}
