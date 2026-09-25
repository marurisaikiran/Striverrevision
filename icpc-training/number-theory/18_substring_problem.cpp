// ICPC 2013-14 Kharagpur Online - Substring Problem
// Sum of N <= 1e6, so build "123...N" (under 7e6 chars in total) and count
// (overlapping) occurrences of the digits of K with KMP.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

long long countOccurrences(const string& text, const string& pat) {
    int m = pat.size();
    vector<int> fail(m, 0);
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && pat[i] != pat[j]) j = fail[j - 1];
        if (pat[i] == pat[j]) j++;
        fail[i] = j;
    }
    long long cnt = 0;
    for (int i = 0, j = 0; i < (int)text.size(); i++) {
        while (j > 0 && text[i] != pat[j]) j = fail[j - 1];
        if (text[i] == pat[j]) j++;
        if (j == m) { cnt++; j = fail[j - 1]; }   // allow overlaps
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string text;
        for (int x = 1; x <= n; x++) text += to_string(x);
        cout << countOccurrences(text, to_string(k)) << '\n';
    }
    return 0;
}
