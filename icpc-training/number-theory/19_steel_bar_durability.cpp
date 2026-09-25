// ICPC 2014-15 Amritapuri Online - Steel Bar Segment Durability
// Link: https://github.com/m-e-r-l-i-n/icpc-india/blob/main/src/2014amrita_online.pdf
// cnt[r] = number of segments ending at the current block with value = r
// (mod M). Extending every segment by digit d maps r -> (10 r + d) mod M,
// and the new one-block segment adds d mod M. O(|S| * M) per query.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

long long countSegments(const string& s, int M, int L) {
    vector<long long> cnt(M, 0), nxt(M, 0);
    long long total = 0;
    for (char ch : s) {
        int d = ch - '0';
        fill(nxt.begin(), nxt.end(), 0);
        for (int r = 0; r < M; r++)
            if (cnt[r]) nxt[(r * 10 + d) % M] += cnt[r];
        nxt[d % M]++;
        cnt.swap(nxt);
        total += cnt[L];
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int q;
    cin >> s >> q;
    while (q--) {
        int M, L;
        cin >> M >> L;
        cout << countSegments(s, M, L) << '\n';
    }
    return 0;
}
