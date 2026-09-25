// ICPC 2017-18 Online Preliminary - Modulo Equality (EQUALMOD)
// Link: https://www.codechef.com/problems/EQUALMOD
// Target remainder r < min B. Cost(r) = sum (r - c_i) + sum_{c_i > r} B_i
// with c_i = A_i mod B_i. Between two c-values the cost only grows with r,
// so the optimum is r = 0 or r = some c_i (< min B). Sweeping the sorted
// candidates keeps the "first c_i > r" pointer monotone.
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> A(n), B(n);
        for (auto& x : A) cin >> x;
        for (auto& x : B) cin >> x;
        vector<pair<long long, long long>> cb(n);   // (c_i, B_i)
        long long minB = B[0], sumC = 0;
        for (int i = 0; i < n; i++) {
            cb[i] = {A[i] % B[i], B[i]};
            minB = min(minB, B[i]);
            sumC += cb[i].first;
        }
        sort(cb.begin(), cb.end());
        vector<long long> sufB(n + 1, 0);           // sum of B over cb[i..]
        for (int i = n - 1; i >= 0; i--) sufB[i] = sufB[i + 1] + cb[i].second;
        // cost(r) = n*r - sumC + (sum of B_i with c_i > r)
        auto cost = [&](long long r, int firstAbove) {
            return 1LL * n * r - sumC + sufB[firstAbove];
        };
        int idx = 0;                                // first index with c > 0
        while (idx < n && cb[idx].first <= 0) idx++;
        long long best = cost(0, idx);
        for (int i = 0; i < n; i++) {               // candidates in sorted order
            long long r = cb[i].first;
            if (r >= minB) break;
            while (idx < n && cb[idx].first <= r) idx++;   // idx only moves right
            best = min(best, cost(r, idx));
        }
        cout << best << '\n';
    }
    return 0;
}
