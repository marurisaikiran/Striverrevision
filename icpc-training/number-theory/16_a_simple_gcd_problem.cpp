// Codeforces 2210C1 - A Simple GCD Problem (Easy Version)
// Link: https://codeforces.com/problemset/problem/2210/C1
// gcd of a subarray (length >= 2) = gcd of its adjacent-pair gcds, so the
// condition is: every g_i = gcd(a_i, a_{i+1}) is preserved. a'_i must be a
// multiple of L_i = lcm(g_{i-1}, g_i); setting a'_i = L_i everywhere keeps
// all g_i, so index i can change iff L_i < a_i.
#include <iostream>
#include <numeric>
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
        vector<long long> a(n), b(n);
        for (auto& x : a) cin >> x;
        for (auto& x : b) cin >> x;              // b_i = a_i in this version
        vector<long long> g(n - 1);
        for (int i = 0; i + 1 < n; i++) g[i] = gcd(a[i], a[i + 1]);
        int ops = 0;
        for (int i = 0; i < n; i++) {
            long long L = 1;
            if (i > 0) L = lcm(L, g[i - 1]);
            if (i + 1 < n) L = lcm(L, g[i]);
            if (L < a[i]) ops++;                 // L divides a_i, so L <= a_i
        }
        cout << ops << '\n';
    }
    return 0;
}
