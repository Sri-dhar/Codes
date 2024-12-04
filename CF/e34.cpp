#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string addOne(string s) {
    int n = s.length();
    bool carry = true;
    
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == '1') {
            s[i] = '0';
        } else {
            s[i] = '1';
            carry = false;
            break;
        }
    }
    
    if (carry) {
        s = "1" + s;
    }
    return s;
}

string llToString(long long a) {
    string s = "";
    while (a > 0) {
        s += to_string(a % 10);
        a /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

void solve() {
    int mod = 998244353;
    int n;
    cin >> n;
    string res = "";
    string binary = "1";
    
    for (int i = 1; i <= n; i++) {
        res.append(binary);
        res = llToString(stoll(res) % mod);
        binary = addOne(binary);
    }
    
    int ans = stoi(res) % mod;
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
    