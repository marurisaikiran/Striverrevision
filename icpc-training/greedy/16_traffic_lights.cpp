// CSES 1163 - Traffic Lights
// Link: https://cses.fi/problemset/task/1163
// Keep the cut positions in a set and the segment lengths in a multiset.
#include <iostream>
#include <iterator>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, n;
    cin >> x >> n;
    set<int> cuts = {0, x};
    multiset<int> lens = {x};
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        auto hi = cuts.upper_bound(p);
        auto lo = prev(hi);
        lens.erase(lens.find(*hi - *lo));   // split [lo, hi] at p
        lens.insert(p - *lo);
        lens.insert(*hi - p);
        cuts.insert(p);
        cout << *lens.rbegin() << (i + 1 < n ? ' ' : '\n');
    }
    return 0;
}
