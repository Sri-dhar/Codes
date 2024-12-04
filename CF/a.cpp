#include<bits/stdc++.h>
using namespace std;

int read() {
    int t;
    cin >> t;
    return t;   
}

void solve() {
    const int MOD = 998244353;
    int t = read(); // Read number of test cases
    while(t--) {
        int n = read();
        string binary_concat = "";
        
        // Build concatenated binary string
        for(int i = 1; i <= n; i++) {
            // Get binary representation without leading zeros
            string curr_binary = "";
            int num = i;
            while(num > 0) {
                curr_binary = (char)('0' + (num % 2)) + curr_binary;
                num /= 2;
            }
            binary_concat += curr_binary;
        }
        
        // Convert binary string to decimal modulo MOD
        int result = 0;
        for(char digit : binary_concat) {
            result = ((result * 2LL) % MOD + (digit - '0')) % MOD;
        }
        
        cout << result << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();  // Call the solve function
    return 0;
}