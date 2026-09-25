// ICPC 2018-19 Online Preliminary - Reduction Game (REDCGAME)
// Work with excesses e_i = a_i - k (> 0 only). The process stops when at
// most one excess is positive, so keep the largest as the survivor and
// cancel the others among themselves as much as possible.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

long long maxFinalSum(const vector<long long>& a, long long k) {
    long long total = 0;
    vector<long long> e;
    for (long long x : a) {
        total += x;
        if (x > k) e.push_back(x - k);
    }
    if (e.size() <= 1) return total;           // no move is possible
    sort(e.begin(), e.end());
    e.pop_back();                              // survivor = largest excess
    long long R = 0;
    for (long long x : e) R += x;
    long long m = e.back();                    // largest non-survivor
    long long survivorLoss = max(2 * m - R, R % 2);
    return total - R - survivorLoss;           // every unit removed costs 1
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        long long k;
        cin >> n >> k;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        cout << maxFinalSum(a, k) << '\n';
    }
    return 0;
}
