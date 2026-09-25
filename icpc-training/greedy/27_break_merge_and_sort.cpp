// ICPC 2020-21 Amritapuri Preliminary - Break, Merge and Sort
// (statement reconstructed from the official solution slides; see the book)
// Cost model: splitting an array costs the length of the shorter part,
// merging two sorted arrays costs the sum of their lengths.
// Answer = (n - longest sorted run) + Huffman cost of the run lengths.
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

long long minCost(const vector<long long>& a) {
    vector<long long> runs;
    long long cur = 1;
    for (size_t i = 1; i < a.size(); i++) {
        if (a[i] < a[i - 1]) { runs.push_back(cur); cur = 1; }
        else cur++;
    }
    runs.push_back(cur);
    long long cost = (long long)a.size() - *max_element(runs.begin(), runs.end());
    priority_queue<long long, vector<long long>, greater<>> pq(runs.begin(), runs.end());
    while (pq.size() > 1) {                    // Huffman merging
        long long x = pq.top(); pq.pop();
        long long y = pq.top(); pq.pop();
        cost += x + y;
        pq.push(x + y);
    }
    return cost;
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
        cout << minCost(a) << '\n';
    }
    return 0;
}
