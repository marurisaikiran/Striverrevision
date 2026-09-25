// Codeforces 2236B - Tatar TV Show
// Positions with equal index mod k form a chain; a move flips two adjacent
// chain cells, so a chain can be cleared iff it holds an even number of 1s.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool canClear(int n, int k, const string& s) {
    vector<int> ones(k, 0);
    for (int i = 0; i < n; i++)
        if (s[i] == '1') ones[i % k]++;
    for (int c : ones)
        if (c % 2) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        string s;
        cin >> n >> k >> s;
        cout << (canClear(n, k, s) ? "YES" : "NO") << '\n';
    }
    return 0;
}
