#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 998244353;

// Function to compute modular exponentiation
ll modExp(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}
int binaryLength(ll num) {
    if (num == 0) return 1;
    return 64 - __builtin_clzll(num);
}
ll binToDecMod(const string& bin) {
    ll result = 0;
    for (char c : bin) {
        result = ((result * 10) % MOD + (c - '0')) % MOD;
    }
    return result;
}

void solve() {
    int t;
    cin >> t;
    
    while (t--) {
        ll n;
        cin >> n;
        
        string binaryString = "";
        for (ll i = 1; i <= n; ++i) {
            bitset<64> bs(i);
            string curr = bs.to_string();
            binaryString += curr.substr(64 - binaryLength(i));
        }
        cout << binToDecMod(binaryString) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}