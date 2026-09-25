// AtCoder ABC103 A - Task Scheduling Problem
// Greedy: visiting values in sorted order costs exactly max - min.
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, b, c;
    cin >> a >> b >> c;
    int hi = max({a, b, c}), lo = min({a, b, c});
    cout << hi - lo << '\n';   // any walk must span [lo, hi]
    return 0;
}
