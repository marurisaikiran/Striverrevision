// Codeforces 2200B - Deletion Sort
// A sorted array ends the game at once (answer n). Otherwise keep some
// inversion pair alive while deleting everything else: answer 1.
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int& x : a) cin >> x;
        bool sorted = true;
        for (int i = 0; i + 1 < n; i++)
            if (a[i] > a[i + 1]) sorted = false;
        cout << (sorted ? n : 1) << '\n';
    }
    return 0;
}
