// CSES 1074 - Stick Lengths
// Link: https://cses.fi/problemset/task/1074
// sum |p_i - x| is minimised at a median of p.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> p(n);
    for (auto& x : p) cin >> x;
    nth_element(p.begin(), p.begin() + n / 2, p.end());
    long long med = p[n / 2], cost = 0;
    for (long long x : p) cost += (x > med ? x - med : med - x);
    cout << cost << '\n';
    return 0;
}
