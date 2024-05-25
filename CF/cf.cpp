#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define IOS                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
#define MOD 1000000007
#define ll long long
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define vi vector<int>
#define pii pair<int, int>
#define all(x) x.begin(), x.end()
#define vvi vector<vector<int>>
#define vpi vector<pair<int, int>>
#define int long long

template <typename T>
T read()
{
    T a;
    cin >> a;
    return a;
}

int read()
{
    int a;
    cin >> a;
    return a;
}

vi rv(int n)
{ // readvector
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    return v;
}

// vvi rvm(int n, int m)
// { // readvectormatrix
//     vvi v(n, vector<int>(m));
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < m; j++)
//             cin >> v[i][j];
//     return v;
// }

// vector<int> pf(vector<int> &arr)
// {
//     int n = arr.size();
//     vi prefix(n);
//     prefix[0] = arr[0];
//     for (int i = 1; i < n; i++)
//     {
//         prefix[i] = max(prefix[i - 1], arr[i]);
//     }
//     return prefix;
// }

// int isodd(int n) { return n % 2; }

// int min(int a, int b)
// {
//     if (a < b)
//         return a;
//     return b;
// }
void solve();

signed main()
{
    IOS int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}

void solve()
{
    int n = read();
    vi arr = rv(n);
    vi a, b;
    for(int i=1; i<=n; i++)
    {
        a.pb(i);
        b.pb(i);
    }
    set<int> sa, sb;
    sa.insert(all(a));
    sb.insert(all(b));

    for(int i=0; i<n; i++)
    {
        int goal = arr[i];
        if(sa.find(goal) != sa.end())
        {
            a[i] = goal;
            sa.erase(goal);
        }
        else
        {
            b[i] = goal;
            sb.erase(goal);
        }
    }    
}

