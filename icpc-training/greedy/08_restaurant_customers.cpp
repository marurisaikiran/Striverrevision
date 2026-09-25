// CSES 1619 - Restaurant Customers
// Sweep line over +1 (arrival) / -1 (leave) events.
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
    vector<pair<int, int>> ev;
    ev.reserve(2 * n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        ev.push_back({a, +1});
        ev.push_back({b, -1});
    }
    sort(ev.begin(), ev.end());           // all times are distinct
    int cur = 0, best = 0;
    for (auto [t, d] : ev) best = max(best, cur += d);
    cout << best << '\n';
    return 0;
}
