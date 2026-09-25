// ICPC 2014-15 Kharagpur Online Re-contest - The last cracker (ACM14KG2)
// After M passes the spark sits M steps clockwise of a: work 0-indexed mod N.
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long n, a, m;
        cin >> n >> a >> m;
        cout << (a - 1 + m) % n + 1 << '\n';
    }
    return 0;
}
