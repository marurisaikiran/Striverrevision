// CSES 1081 - Common Divisors
// Link: https://cses.fi/problemset/task/1081
// The answer is the largest d that divides at least two array elements:
// such a pair has gcd >= d, and the best pair's gcd itself is such a d.
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int V = 1'000'000;
    int n;
    cin >> n;
    vector<int> cnt(V + 1, 0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    for (int d = V; d >= 1; d--) {
        int multiples = 0;
        for (int m = d; m <= V && multiples < 2; m += d) multiples += cnt[m];
        if (multiples >= 2) { cout << d << '\n'; break; }
    }
    return 0;
}
