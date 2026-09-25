// AtCoder ABC213 A - Bitwise Exclusive Or
// Link: https://atcoder.jp/contests/abc213/tasks/abc213_a
// A xor C = B  <=>  C = A xor B   (xor both sides with A; A xor A = 0).
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, b;
    cin >> a >> b;
    cout << (a ^ b) << '\n';
    return 0;
}
