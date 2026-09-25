// ICPC 2017-18 Online Preliminary - Ordering teams (ORDTEAMS)
// Sort by total score; any valid chain must be in increasing-sum order,
// so we only need to check consecutive pairs of that order.
#include <algorithm>
#include <array>
#include <iostream>
using namespace std;

using Person = array<int, 3>;

bool strictlyBetter(const Person& x, const Person& y) {   // x better than y
    bool some = false;
    for (int k = 0; k < 3; k++) {
        if (x[k] < y[k]) return false;
        if (x[k] > y[k]) some = true;
    }
    return some;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        array<Person, 3> p;
        for (auto& q : p) cin >> q[0] >> q[1] >> q[2];
        sort(p.begin(), p.end(), [](const Person& a, const Person& b) {
            return a[0] + a[1] + a[2] < b[0] + b[1] + b[2];
        });
        bool ok = strictlyBetter(p[1], p[0]) && strictlyBetter(p[2], p[1]);
        cout << (ok ? "yes" : "no") << '\n';
    }
    return 0;
}
