#include <bits/stdc++.h>
using namespace std;
#define IOS                     \
  ios_base::sync_with_stdio(0); \
  cin.tie(0);                   \
  cout.tie(0);
#define int long long

string getBinary(int n) {
  string s = "";
  while (n > 0) {
    s += to_string(n % 2);
    n /= 2;
  }
  reverse(s.begin(), s.end());
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
  for (int i = 1; i <= n; i++) {
    string s = getBinary(i);
    res.append(s);
    res = llToString(stoll(res) % mod); 
  }
  int ans = stoi(res) % mod;
  cout << ans << endl;
}

signed main() {
  IOS
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
        