// CSES 2183 - Missing Coin Sum
// Link: https://cses.fi/problemset/task/2183
// Invariant: after the first i sorted coins, every sum in [0, reach) is
// makeable. A coin x <= reach extends it to reach + x; x > reach leaves a gap.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> x(n);
    for (auto& v : x) cin >> v;
    sort(x.begin(), x.end());
    long long reach = 1;               // smallest sum not yet makeable
    for (long long v : x) {
        if (v > reach) break;
        reach += v;
    }
    cout << reach << '\n';
    return 0;
}
