// ICPC 2010-11 Kanpur Online - A New Number System
// Blocks of '0': length 1 -> flag = 1, length 2 -> flag = 0,
// length n > 2 -> append (n - 2) copies of flag. Building a binary number
// bit by bit is value = 2 * value + bit.
#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string tok;
    long long value = 0;
    int flag = 0;
    while (cin >> tok) {
        if (tok[0] == '~') break;                  // end of input
        if (tok == "#") {                          // end of one number
            cout << value << '\n';
            value = 0;
            flag = 0;
            continue;
        }
        int len = tok.size();
        if (len == 1) flag = 1;
        else if (len == 2) flag = 0;
        else
            for (int k = 0; k < len - 2; k++) value = 2 * value + flag;
    }
    return 0;
}
