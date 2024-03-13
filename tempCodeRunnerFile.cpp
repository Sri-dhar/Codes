#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define MOD 1000000007
#define ll long long
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define vi vector<int>
#define vll vector<ll>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) x.begin(), x.end()
#define vvi vector<vector<int>>
// #define int long long

vi rv(int n) { //readvector
    vector<int> v(n);
    for(int i = 0; i < n; i++)
        cin >> v[i];
    return v;
}

vvi rvm(int n, int m) { //readvectormatrix
    vvi v(n, vector<int>(m));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> v[i][j];
    return v;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n+1, vector<int>(m+1, 0));
    vector<vector<int>> s(n+1, vector<int>(m+1, 0));
    int sum = 0;
    int minn = INT_MAX;
    char x;
    
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++){
            cin >> x;
            a[i][j] = bool(x-'0');
            s[i-1][j-1] += a[i][j];
            s[i-1][j] += a[i][j];
            s[i][j-1] += a[i][j];
            s[i][j] += a[i][j];
            sum += a[i][j];
        }
    

    for(int i=1; i<n; i++)
        for(int j=1; j<m; j++)
            minn = min(s[i][j], minn);
        
    if(minn == 4) cout << 1 + (sum - 3) << endl;
    else if(minn == 3) cout << 1 + (sum - 2) << endl;
    else cout << sum << endl;
}

int main() {
    IOS
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}