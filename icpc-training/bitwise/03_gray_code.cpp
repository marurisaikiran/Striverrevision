// CSES 2205 - Gray Code
// Link: https://cses.fi/problemset/task/2205
// g(i) = i xor (i >> 1): consecutive values differ in exactly one bit.
#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string out;
    out.reserve((size_t)(n + 1) << n);
    for (int i = 0; i < (1 << n); i++) {
        int g = i ^ (i >> 1);
        for (int b = n - 1; b >= 0; b--) out += char('0' + ((g >> b) & 1));
        out += '\n';
    }
    cout << out;
    return 0;
}
