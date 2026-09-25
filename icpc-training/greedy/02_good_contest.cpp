// Codeforces 2266A - Good Contest
// Link: https://codeforces.com/problemset/problem/2266/A
// Stack every "miss" of every problem on the same people:
// the weak count is forced to be at least n - a_i for each problem i.
#include <algorithm>
#include <iostream>
using namespace std;

int minWeak(int n, int a1, int a2, int a3) {
    return max({n - a1, n - a2, n - a3});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, a1, a2, a3;
        cin >> n >> a1 >> a2 >> a3;
        cout << minWeak(n, a1, a2, a3) << '\n';
    }
    return 0;
}
