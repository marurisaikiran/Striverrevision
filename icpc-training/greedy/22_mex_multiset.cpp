// Codeforces 2259D - MEX Multiset
// Only the number of zeros matters:
//   no zero   -> every MEX is 0, 0 + 0 >= 0 holds;
//   one zero  -> exactly one set has MEX >= 1 while the other two are 0: NO;
//   >= 2 zeros -> A = {0, all values >= 2}, B = {0}, C = {all 1s}
//                gives MEX 1, 1, 0 and 1 + 0 >= 1.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool build(const vector<long long>& a, string& out) {
    int n = a.size(), zeros = 0;
    for (long long v : a) zeros += (v == 0);
    out.assign(n, 'A');
    if (zeros == 0) return true;
    if (zeros == 1) return false;
    bool gaveB = false;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0 && !gaveB) { out[i] = 'B'; gaveB = true; }
        else if (a[i] == 1) out[i] = 'C';
        // every other element (extra zeros, values >= 2) stays in A
    }
    return true;
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
        for (auto& v : a) cin >> v;
        string s;
        if (build(a, s)) cout << "YES\n" << s << '\n';
        else cout << "NO\n";
    }
    return 0;
}
