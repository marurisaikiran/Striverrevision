// Codeforces 2218E - The 67th XOR Problem
// After removing element i the whole array has been xored with a_i's
// ORIGINAL value (the running masks telescope). So the survivor j ends as
// a_j xor a_last, where "last" is the final removed element:
//   answer = max over pairs i != j of a_i xor a_j   (binary trie).
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

struct Trie {
    vector<array<int, 2>> nxt{{0, 0}};
    void insert(int v) {
        int u = 0;
        for (int b = 29; b >= 0; b--) {
            int c = v >> b & 1;
            if (!nxt[u][c]) { nxt[u][c] = nxt.size(); nxt.push_back({0, 0}); }
            u = nxt[u][c];
        }
    }
    int bestXor(int v) const {            // max v ^ w over inserted w
        int u = 0, r = 0;
        for (int b = 29; b >= 0; b--) {
            int want = (v >> b & 1) ^ 1;
            if (nxt[u][want]) { r |= 1 << b; u = nxt[u][want]; }
            else u = nxt[u][want ^ 1];
        }
        return r;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int& x : a) cin >> x;
        Trie tr;
        tr.insert(a[0]);
        int best = 0;
        for (int i = 1; i < n; i++) {
            best = max(best, tr.bestXor(a[i]));
            tr.insert(a[i]);
        }
        cout << best << '\n';
    }
    return 0;
}
