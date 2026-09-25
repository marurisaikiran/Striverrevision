// ICPC 2017-18 Online Preliminary - Obtain Desired Standard Deviation (STDDEV)
// N even : N/2 copies of +s and N/2 of -s  -> mean 0, every deviation s.
// N odd  : one 0 and (N-1)/2 pairs of +-c with (N-1) c^2 / N = s^2.
// N = 1  : the deviation is always 0.
#include <cmath>
#include <cstdio>
using namespace std;

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        long long n, s;
        scanf("%lld %lld", &n, &s);
        if (n == 1) {
            puts(s == 0 ? "0" : "-1");
            continue;
        }
        double c = (n % 2 == 0) ? (double)s : s * sqrt((double)n / (n - 1));
        for (long long i = 0; i < n; i++) {
            double v;
            if (n % 2 == 1 && i == n - 1) v = 0.0;          // the extra zero
            else v = (i % 2 == 0) ? c : -c;
            printf("%.9f%c", v, i + 1 < n ? ' ' : '\n');
        }
    }
    return 0;
}
