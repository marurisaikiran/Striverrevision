// CSES 1141 - Playlist
// Link: https://cses.fi/problemset/task/1141
// Two pointers: the window [l, r] never contains a repeated song.
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> k(n);
    for (auto& v : k) cin >> v;
    unordered_map<int, int> last;       // song -> last index seen
    last.reserve(2 * n);
    int best = 0, l = 0;
    for (int r = 0; r < n; r++) {
        auto it = last.find(k[r]);
        if (it != last.end() && it->second >= l) l = it->second + 1;
        last[k[r]] = r;
        best = max(best, r - l + 1);
    }
    cout << best << '\n';
    return 0;
}
