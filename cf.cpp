#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define MOD 1e9+7
#define ll long long

void solve()
{
    int n ; 
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int ans = 0;

    for(int i=0; i<n-1; i++)
    {
        if(a[i] > a[i+1])
        {
            ans += a[i] - a[i+1];
            a[i+1] = a[i];
        }
    }
    cout << ans << endl;
}

int main() {
    IOS
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}