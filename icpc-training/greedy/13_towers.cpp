// CSES 1073 - Towers
// Link: https://cses.fi/problemset/task/1073
// Put each cube on the tower with the smallest top strictly greater than it.
#include <iostream>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    multiset<int> tops;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        auto it = tops.upper_bound(k);
        if (it != tops.end()) tops.erase(it);   // place k on that tower
        tops.insert(k);
    }
    cout << tops.size() << '\n';
    return 0;
}
