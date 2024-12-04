#include <iostream>
#include <string>
using namespace std;

// Function to add 1 to a binary number represented as a string
string addOne(string binary) {
    int carry = 1;
    for (int i = binary.length() - 1; i >= 0 && carry; i--) {
        if (binary[i] == '0') {
            binary[i] = '1';
            carry = 0;
        } else {
            binary[i] = '0';
        }
    }
    if (carry) {
        binary = "1" + binary; // Add a new digit if carry is still 1
    }
    return binary;
}

void solve() {
    const int MOD = 998244353;
    int n;
    cin >> n;

    if (n <= 0) {
        cout << "0\n";
        return;
    }

    long long result = 0; // Store the final result as a number
    string prevBin = "1"; // Start with binary of 1
    result = 1; // Initialize the result with the first number

    for (int i = 2; i <= n; i++) {
        prevBin = addOne(prevBin); // Get the binary of the next number
        // Convert binary string to integer and update the result
        long long binaryVal = stoll(prevBin);
        result = (result * (1LL << prevBin.length()) + binaryVal) % MOD; // Shift result and add current binary
    }

    cout << result << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
        