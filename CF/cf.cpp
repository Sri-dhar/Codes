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

vector<int> pf(vector<int>& arr) {
    int n = arr.size();
    vi prefix(n);
    prefix[0] = arr[0];
    for(int i = 1; i < n; i++) {
        prefix[i] = max(prefix[i-1], arr[i]);
    }
    return prefix;
}

void solve()
{
    int l;
    cin >> l;
    string s;
    cin >> s;
    unordered_set<size_t> st;
    hash<string> hasher;

    for(int i=0; i<l-1; i++)
    {
        string cpy = s;
        cpy.erase(i, 2);
        st.insert(hasher(cpy));
    }
    cout<<st.size()<<endl;
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