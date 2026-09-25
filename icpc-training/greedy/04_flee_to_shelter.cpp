// ICPC 2013-14 Amritapuri Online - Flee to Shelter
// Carry the maximum M each time: ceil(N / M) round trips of 2T minutes.
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c;
    cin >> c;
    while (c--) {
        long long n, m, t;
        cin >> n >> m >> t;
        long long trips = (n + m - 1) / m;   // ceil(n / m)
        cout << 2 * trips * t << '\n';
    }
    return 0;
}
