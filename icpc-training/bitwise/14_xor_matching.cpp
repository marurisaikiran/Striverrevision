// AtCoder ABC126 F - XOR Matching
// Link: https://atcoder.jp/contests/abc126/tasks/abc126_f
// For M >= 2 and K < 2^M:  0 1 .. (2^M-1 without K)  K  (reverse)  K
// Between the two copies of v != K lie all numbers except v, plus K:
// xor of all of 0..2^M-1 is 0, so that block xors to K.
#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M;
    long long K;
    cin >> M >> K;
    if (M == 0) { cout << (K == 0 ? "0 0" : "-1") << '\n'; return 0; }
    if (M == 1) { cout << (K == 0 ? "0 0 1 1" : "-1") << '\n'; return 0; }
    if (K >= (1LL << M)) { cout << -1 << '\n'; return 0; }
    int top = (1 << M) - 1;
    string out;
    for (int v = 0; v <= top; v++) if (v != K) out += to_string(v) + ' ';
    out += to_string(K) + ' ';
    for (int v = top; v >= 0; v--) if (v != K) out += to_string(v) + ' ';
    out += to_string(K) + '\n';
    cout << out;
    return 0;
}
