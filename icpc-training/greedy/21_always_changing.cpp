// Codeforces 2252B - Always Changing
// Link: https://codeforces.com/problemset/problem/2252/B
// Forced deletions: L-1 from every run. If the 0/1 counts differ by more
// than 1, the deficient type can only be topped up by deleting a whole
// run of that type sitting at an end of the string (at most two).
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

long long minOps(const string& s) {
    int n = s.size();
    long long z = 0, o = 0;                  // forced 0- and 1-deletions
    for (int i = 1; i < n; i++)
        if (s[i] == s[i - 1]) (s[i] == '0' ? z : o)++;
    if (llabs(z - o) <= 1) return z + o;
    long long need = llabs(z - o) - 1;
    char deficient = (z > o) ? '1' : '0';
    int cap = (s[0] == deficient) + (s[n - 1] == deficient);
    // s[0] and s[n-1] lie in different runs whenever both equal
    // the deficient type (the excess type must appear somewhere).
    return need <= cap ? z + o + need : -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        cout << minOps(s) << '\n';
    }
    return 0;
}
