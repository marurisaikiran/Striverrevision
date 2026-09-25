// ICPC 2014-15 Kharagpur Online Re-contest - Jai Hanuman (ACM14KG4)
// Link: https://www.codechef.com/problems/ACM14KG4
// Person N moves last, so nobody can take anything from them: they get their
// ideal triple. Person N-1 gets the ideal triple among what N does not want,
// and so on -> assign greedily from N down to 1.
// A "start" s is available while s, s+1, s+2 are all untaken.
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> P(n);
        for (int& x : P) cin >> x;
        int total = 5 * n;
        set<int> starts;                          // valid triple starts
        for (int s = 1; s + 2 <= total; s++) starts.insert(starts.end(), s);
        vector<int> ans(n);
        for (int i = n - 1; i >= 0; i--) {
            auto it = starts.lower_bound(P[i]);   // least start >= P[i]
            if (it == starts.end()) it = starts.begin();   // fall back: least
            int s = *it;
            ans[i] = s;
            for (int d = -2; d <= 2; d++) starts.erase(s + d);  // overlap s..s+2
        }
        string out;
        for (int i = 0; i < n; i++) out += to_string(ans[i]) + (i + 1 < n ? " " : "\n");
        cout << out;
    }
    return 0;
}
