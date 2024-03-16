    #include <bits/stdc++.h>
    using namespace std;
     
    int main()
    {
    int t; cin >> t;
    while(t--) {
    int n; cin >> n;
    vector<int> a(n);
    for(int&i : a) cin >> i;
    bool ok = 1;
    for(int i = 1; i <= n - 2; i++)
    ok = ok & (a[i] % __gcd(a[i-1],a[i+1]) == 0);
    cout << (ok ?  "YES\n": "NO\n");
    }
    }