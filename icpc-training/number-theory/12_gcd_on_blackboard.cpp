// AtCoder ABC125 C - GCD on Blackboard
// Link: https://atcoder.jp/contests/abc125/tasks/abc125_c
// Replacing A_i by the gcd of all others is optimal, so the answer is
// max_i gcd(prefix[i-1], suffix[i+1]).
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n), pre(n + 1, 0), suf(n + 2, 0);
    for (auto& x : a) cin >> x;
    for (int i = 0; i < n; i++) pre[i + 1] = gcd(pre[i], a[i]);   // gcd(0,x) = x
    for (int i = n - 1; i >= 0; i--) suf[i] = gcd(suf[i + 1], a[i]);
    long long best = 0;
    for (int i = 0; i < n; i++) best = max(best, gcd(pre[i], suf[i + 1]));
    cout << best << '\n';
    return 0;
}
