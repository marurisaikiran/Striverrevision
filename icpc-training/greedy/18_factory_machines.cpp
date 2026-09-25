// CSES 1620 - Factory Machines
// Link: https://cses.fi/problemset/task/1620
// Binary search the answer T: in T seconds machine i makes floor(T / k_i).
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool enough(const vector<long long>& k, long long T, long long t) {
    long long made = 0;
    for (long long v : k) {
        made += T / v;
        if (made >= t) return true;        // stop early, avoids overflow
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long t;
    cin >> n >> t;
    vector<long long> k(n);
    for (auto& v : k) cin >> v;
    long long lo = 0, hi = *min_element(k.begin(), k.end()) * t;  // hi works
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (enough(k, mid, t)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << '\n';
    return 0;
}
