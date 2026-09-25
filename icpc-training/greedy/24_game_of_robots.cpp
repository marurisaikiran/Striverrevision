// ICPC 2018-19 Online Preliminary - A Game of Robots (ROBOGAME)
// Two robots can be made to collide iff their movement ranges share a cell;
// so the grid is safe iff no cell is covered by two ranges.
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isSafe(const string& s) {
    int n = s.size();
    vector<int> diff(n + 1, 0);
    for (int i = 0; i < n; i++) {
        if (s[i] == '.') continue;
        int x = s[i] - '0';
        diff[max(0, i - x)]++;
        diff[min(n - 1, i + x) + 1]--;
    }
    int cover = 0;
    for (int i = 0; i < n; i++) {
        cover += diff[i];
        if (cover >= 2) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        cout << (isSafe(s) ? "safe" : "unsafe") << '\n';
    }
    return 0;
}
