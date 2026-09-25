// CSES 1713 - Counting Divisors
// Divisor-count sieve: every d contributes 1 to each of its multiples.
// Total work sum_{d <= V} V / d = O(V log V).
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int V = 1'000'000;
    vector<int> tau(V + 1, 0);
    for (int d = 1; d <= V; d++)
        for (int m = d; m <= V; m += d) tau[m]++;
    int n;
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        cout << tau[x] << '\n';
    }
    return 0;
}
