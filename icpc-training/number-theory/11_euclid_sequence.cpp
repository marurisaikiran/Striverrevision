// Codeforces 2234A - Euclid, Sequence and Two Numbers
// a_1 >= a_2 > a_3 > ... (each remainder is below its divisor and must stay
// positive), so the only candidate order is "sorted descending". Verify it.
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> b(n);
        for (auto& x : b) cin >> x;
        sort(b.begin(), b.end(), greater<>());
        bool ok = true;
        for (int i = 0; i + 2 < n && ok; i++)
            if (b[i] % b[i + 1] != b[i + 2]) ok = false;
        if (ok) cout << b[0] << ' ' << b[1] << '\n';
        else cout << -1 << '\n';
    }
    return 0;
}
