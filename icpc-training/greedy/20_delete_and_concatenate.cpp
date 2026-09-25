// Codeforces 2245B - Delete and Concatenate
// Base: remove everything singly -> sum(a) - n*c. Pairing x <= y instead
// gains c - x. Pair the k smallest with the k largest while a_(i) < c.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

long long bestScore(vector<long long> a, long long c) {
    int n = a.size();
    long long score = -1LL * n * c;
    for (long long v : a) score += v;
    sort(a.begin(), a.end());
    for (int i = 0; i < n / 2 && a[i] < c; i++) score += c - a[i];
    return score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        long long c;
        cin >> n >> c;
        vector<long long> a(n);
        for (auto& v : a) cin >> v;
        cout << bestScore(a, c) << '\n';
    }
    return 0;
}
