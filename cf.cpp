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
    ll n, m, a, b;
    cin >> n >> m >> a >> b;
    if (b < a * m)
    {
        if (n % m * a < b) cout << n / m * b + n % m * a;
        else cout << n / m * b + b;
    }
    else
        cout << n * a;
}

int main()
{
    IOS int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}