#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define IOS                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
#define MOD 1e9 + 7
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

void solve()
{
    int n;
    cin>>n;
    int a[n];
    for (int i=0; i<n; i++)
    {
        cin>>a[i];
    }
    sort(a,a+n);
    int m;
    cin>>m;
    while(m--)
    {
        int x;
        cin>>x;
        cout<<upper_bound(a,a+n,x)-a;
        cout<<endl;
    }
}

int main()
{
    IOS int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
