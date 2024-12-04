#include <iostream>
#include <cmath>

using namespace std;

const int MOD = 998244353;

int main() {
    int t;
    cin >> t;

    while (t--) {
        long long n;
        cin >> n;

        long long result = 0, base = 1;
        for (long long i = 1; i <= n; i++) {
            long long bits = floor(log2(i)) + 1;
            long long mask = 1LL << bits;

            // Iterate over the bits of the current number
            while (mask > 0) {
                result = (result * 10 + (i & mask) ? 1 : 0) % MOD;
                mask >>= 1;
                base = (base * 10) % MOD;
            }
        }

        cout << result << endl;
    }

    return 0;
}   