// CSES 1630 - Tasks and Deadlines
// Link: https://cses.fi/problemset/task/1630
// Reward = sum d - sum f. sum d is fixed; minimise sum of finishing
// times with Shortest-Processing-Time-first (exchange argument).
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<long long, long long>> t(n);   // (duration, deadline)
    for (auto& [a, d] : t) cin >> a >> d;
    sort(t.begin(), t.end());
    long long now = 0, reward = 0;
    for (auto [a, d] : t) {
        now += a;
        reward += d - now;
    }
    cout << reward << '\n';
    return 0;
}
