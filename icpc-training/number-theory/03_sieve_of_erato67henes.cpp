// Codeforces 2195A - Sieve of Erato67henes
// 67 is prime and every a_i <= 67, so a product equal to 67 must use a 67
// (all other chosen factors must be 1). Answer: is 67 present?
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        bool has67 = false;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (x == 67) has67 = true;
        }
        cout << (has67 ? "YES" : "NO") << '\n';
    }
    return 0;
}
