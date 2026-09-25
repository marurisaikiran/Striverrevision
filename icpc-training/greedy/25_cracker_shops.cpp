// ICPC 2014-15 Kharagpur Online Re-contest - Cracker shops (ACM14KG1)
// Link: https://www.codechef.com/problems/ACM14KG1
// Step 1 (two pointers): e[j] = least k such that shops j..k cover all M types.
// Step 2: for shop i the best window starting at j is [j, max(e[j], i)].
//   * starts j with e[j] < i form a prefix; the best of them is the last one.
//   * starts j in [p, i] (e[j] >= i) are scored by (e[j] - j, j): keep them in
//     an ordered set that slides right as i grows.
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> shop(n + 1);
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            shop[i].resize(x);
            for (int& c : shop[i]) cin >> c;
        }
        // ---- step 1: minimal right end for every left end ----
        vector<int> e(n + 2, INF), have(m + 1, 0);
        int distinct = 0, r = 0;
        for (int j = 1; j <= n; j++) {
            while (r < n && distinct < m) {
                ++r;
                for (int c : shop[r]) if (have[c]++ == 0) distinct++;
            }
            if (distinct == m) e[j] = r;
            for (int c : shop[j]) if (--have[c] == 0) distinct--;
        }
        // ---- step 2: sweep i = 1..n ----
        set<pair<int, int>> open;           // (e[j] - j, j) with e[j] >= i
        int p = 1;                          // first j with e[j] >= i
        string out;
        for (int i = 1; i <= n; i++) {
            if (e[i] != INF) open.insert({e[i] - i, i});
            while (p <= i && e[p] < i) {    // e[p] < i: window no longer spans i
                open.erase({e[p] - p, p});
                p++;
            }
            int bestLen = INF, bestJ = 0, bestK = 0;
            if (!open.empty()) {
                auto [len, j] = *open.begin();
                bestLen = len; bestJ = j; bestK = e[j];
            }
            if (p > 1) {                    // candidate: j = p - 1, window [j, i]
                int j = p - 1, len = i - j;
                if (len < bestLen || (len == bestLen && j < bestJ)) {
                    bestLen = len; bestJ = j; bestK = i;
                }
            }
            out += to_string(bestJ) + ' ' + to_string(bestK) + '\n';
        }
        cout << out;
    }
    return 0;
}
