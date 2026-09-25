// CSES 1629 - Movie Festival
// Link: https://cses.fi/problemset/task/1629
// Classic interval scheduling: always take the movie that ends first.
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> mv(n);          // (end, start)
    for (auto& [e, s] : mv) cin >> s >> e;
    sort(mv.begin(), mv.end());
    int watched = 0, freeAt = 0;
    for (auto [e, s] : mv)
        if (s >= freeAt) { watched++; freeAt = e; }
    cout << watched << '\n';
    return 0;
}
