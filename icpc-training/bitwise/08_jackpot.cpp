// ICPC 2013-14 Kharagpur Online - Jackpot
// Link: https://github.com/m-e-r-l-i-n/icpc-india/blob/main/src/Kharagpur_Site_Online_Problems_2013.pdf
// Reaching v from 1 with (+1, x2) takes f(v) = hb(v) + popcount(v) - 1 steps
// (hb = index of the highest set bit). Alice and Bob work in parallel, so
// answer = min over a + b = N of max(f(a), f(b)).
// Digit DP over bits from the top, adding a + b = N with carries:
//   state (carry that this bit must send upward, a started?, b started?, costA)
//   value = minimum costB.
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int INF = 1e9;
const int BITS = 31;          // N <= 1e9 < 2^30
const int MAXC = 2 * BITS + 2;

int solve(long long N) {
    // dp[c][sa][sb][ca] = min cb ; c = carry out of the current bit
    static int dp[2][2][2][MAXC], nd[2][2][2][MAXC];
    auto fill = [](int (*d)[2][2][MAXC]) {
        for (int c = 0; c < 2; c++) for (int x = 0; x < 2; x++)
            for (int y = 0; y < 2; y++) for (int k = 0; k < MAXC; k++) d[c][x][y][k] = INF;
    };
    fill(dp);
    dp[0][0][0][0] = 0;       // nothing may carry out of the top bit
    for (int p = BITS - 1; p >= 0; p--) {
        fill(nd);
        int bit = (N >> p) & 1;
        for (int c = 0; c < 2; c++) for (int sa = 0; sa < 2; sa++)
        for (int sb = 0; sb < 2; sb++) for (int ca = 0; ca < MAXC; ca++) {
            int cb = dp[c][sa][sb][ca];
            if (cb == INF) continue;
            for (int x = 0; x < 2; x++) for (int y = 0; y < 2; y++) for (int cin_ = 0; cin_ < 2; cin_++) {
                if (x + y + cin_ != bit + 2 * c) continue;
                // setting a bit costs 1; the first (highest) one also costs p
                int na = ca + (x ? (sa ? 1 : p + 1) : 0);
                int nb = cb + (y ? (sb ? 1 : p + 1) : 0);
                if (na >= MAXC) continue;
                int& ref = nd[cin_][sa | x][sb | y][na];
                ref = min(ref, nb);
            }
        }
        memcpy(dp, nd, sizeof dp);
    }
    int best = INF;
    for (int ca = 0; ca < MAXC; ca++)          // no carry into bit 0, both >= 1
        if (dp[0][1][1][ca] != INF) best = min(best, max(ca, dp[0][1][1][ca]) - 1);
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        cout << solve(n) << '\n';
    }
    return 0;
}
