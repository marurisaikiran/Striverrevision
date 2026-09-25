// AtCoder AGC018 C - Coins
// Link: https://atcoder.jp/contests/agc018/tasks/agc018_c
// Subtract C_i: everyone gives bronze by default, then pick X people for
// a = A - C and Y people for b = B - C. Sorted by a - b (desc), all gold
// people come before all silver people, so try every split point.
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int X, Y, Z;
    cin >> X >> Y >> Z;
    int n = X + Y + Z;
    vector<long long> a(n), b(n);
    long long base = 0;
    for (int i = 0; i < n; i++) {
        long long A, B, C;
        cin >> A >> B >> C;
        a[i] = A - C; b[i] = B - C; base += C;
    }
    vector<int> id(n);
    for (int i = 0; i < n; i++) id[i] = i;
    sort(id.begin(), id.end(), [&](int p, int q) { return a[p] - b[p] > a[q] - b[q]; });

    // left[k] = best sum of X values of a among the first k people
    vector<long long> left(n + 1, 0), right(n + 1, 0);
    priority_queue<long long, vector<long long>, greater<>> pq;
    long long s = 0;
    for (int k = 1; k <= n; k++) {
        pq.push(a[id[k - 1]]); s += a[id[k - 1]];
        if ((int)pq.size() > X) { s -= pq.top(); pq.pop(); }
        left[k] = s;
    }
    // right[k] = best sum of Y values of b among people k..n-1
    priority_queue<long long, vector<long long>, greater<>> qq;
    s = 0;
    for (int k = n - 1; k >= 0; k--) {
        qq.push(b[id[k]]); s += b[id[k]];
        if ((int)qq.size() > Y) { s -= qq.top(); qq.pop(); }
        right[k] = s;
    }
    long long best = -(1LL << 62);
    for (int k = X; k <= n - Y; k++) best = max(best, left[k] + right[k]);
    cout << base + best << '\n';
    return 0;
}
