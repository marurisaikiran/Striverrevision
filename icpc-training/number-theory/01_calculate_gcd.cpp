// AtCoder Math & Algorithm 015 - Calculate GCD
// Euclid: gcd(a, b) = gcd(b, a mod b), gcd(a, 0) = a.
#include <iostream>
using namespace std;

long long gcdEuclid(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, b;
    cin >> a >> b;
    cout << gcdEuclid(a, b) << '\n';
    return 0;
}
