// ICPC 2020-21 Amritapuri Preliminary - Minimum Weight Bi-Partition
// Link: https://github.com/m-e-r-l-i-n/icpc-india/blob/main/src/ICPC%202020%20-%20India%20Prelims%20Solutions.pdf
// (core task reconstructed from the official solution slides; see the book)
// Existing edges are free; a new edge (u, v) costs |A_u - A_v|. A minimum
// spanning tree only ever needs edges between neighbours in sorted-A order.
#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>
using namespace std;

struct DSU {
    vector<int> p, sz;
    explicit DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<long long> A(n);
        for (auto& x : A) cin >> x;
        vector<tuple<long long, int, int>> edges;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            edges.push_back({0, u - 1, v - 1});
        }
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int x, int y) { return A[x] < A[y]; });
        for (int i = 0; i + 1 < n; i++)
            edges.push_back({A[ord[i + 1]] - A[ord[i]], ord[i], ord[i + 1]});
        sort(edges.begin(), edges.end());
        DSU d(n);
        long long cost = 0;
        for (auto [w, u, v] : edges)
            if (d.unite(u, v)) cost += w;
        cout << cost << '\n';
    }
    return 0;
}
