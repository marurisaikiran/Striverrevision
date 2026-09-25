// Codeforces 2252A - Boss Fight
// If the most frequent value v fits (f <= others + 1) we can play everything
// with no equal neighbours. Otherwise the best we can do is
//   v x v x ... v v   -> all others plus (others + 2) copies of v.
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

long long maxDamage(const vector<int>& a) {
    map<int, int> freq;
    long long total = 0;
    for (int x : a) { freq[x]++; total += x; }
    int v = 0, f = 0;
    for (auto [val, cnt] : freq)
        if (cnt > f) { f = cnt; v = val; }
    int others = (int)a.size() - f;
    if (f <= others + 1) return total;               // perfect alternation
    long long restSum = total - 1LL * v * f;
    return restSum + 1LL * min(f, others + 2) * v;   // alternate, then trigger
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int& x : a) cin >> x;
        cout << maxDamage(a) << '\n';
    }
    return 0;
}
