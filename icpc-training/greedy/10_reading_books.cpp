// CSES 1631 - Reading Books
// Link: https://cses.fi/problemset/task/1631
// Answer = max(sum, 2 * longest book).
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long sum = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        long long t;
        cin >> t;
        sum += t;
        mx = max(mx, t);
    }
    cout << max(sum, 2 * mx) << '\n';
    return 0;
}
