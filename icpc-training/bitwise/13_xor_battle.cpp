// AtCoder AGC045 A - Xor Battle
// Scan from the last round. Keep a linear (xor) basis of person 0's later
// numbers. If person 1 owns an A_i that the basis cannot produce, person 1
// wins: whatever x is later, 0 cannot undo that bit pattern.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct XorBasis {
    unsigned long long b[61] = {};
    // returns true if v was independent (and inserts it)
    bool insert(unsigned long long v) {
        for (int i = 60; i >= 0; i--) {
            if (!(v >> i & 1)) continue;
            if (!b[i]) { b[i] = v; return true; }
            v ^= b[i];
        }
        return false;
    }
    bool representable(unsigned long long v) const {
        for (int i = 60; i >= 0; i--)
            if (v >> i & 1) {
                if (!b[i]) return false;
                v ^= b[i];
            }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<unsigned long long> a(n);
        for (auto& v : a) cin >> v;
        string s;
        cin >> s;
        XorBasis basis;
        int result = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '0') basis.insert(a[i]);
            else if (!basis.representable(a[i])) { result = 1; break; }
        }
        cout << result << '\n';
    }
    return 0;
}
