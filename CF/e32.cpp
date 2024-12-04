#include <iostream>
#include <string>
using namespace std;

string addOne(string binary) {
    int n = binary.length();
    for (int i = n - 1; i >= 0; i--) {
        if (binary[i] == '0') {
            binary[i] = '1';
            return binary;
        } else {
            binary[i] = '0';
        }
    }
    return "1" + binary;
}
        

void solve() {
    const int MOD = 998244353;
    int n;
    cin >> n;

    if (n <= 0) {
        cout << "0\n";
        return;
    }

    string prevBin = "";
    string result = "";

    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            prevBin = "1"; // Binary of 1
            result += prevBin;
        } else {
            prevBin = addOne(prevBin); // Add 1 to the previous binary
            result += prevBin;
        }

        if (result.length() > 18) {
            // Reduce result length to prevent overflow
            long long num = stoll(result.substr(max(0, (int)result.length() - 18)));
            result = to_string(num % MOD);
        }
    }

    long long finalNum = stoll(result);           
    cout << finalNum % MOD << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    cin >> t;

    while (t--) {
        solve();    
    }
    return 0;
}
