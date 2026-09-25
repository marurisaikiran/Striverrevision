// ICPC 2013-14 Amritapuri Online - Creating a Wormhole
// Polygon exists iff longest side < sum of the others. For a fixed longest
// stick a[j] (sorted) it is best to take every shorter stick too.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int maxSticks(vector<long long> a) {
    sort(a.begin(), a.end());
    long long prefix = 0;           // sum of a[0..j-1]
    int best = -1;
    for (int j = 0; j < (int)a.size(); j++) {
        if (j >= 2 && prefix > a[j]) best = j + 1;
        prefix += a[j];
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        cout << maxSticks(a) << '\n';
    }
    return 0;
}
