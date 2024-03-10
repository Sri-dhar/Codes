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
#define int long long

vector<int> rv(int n) { //readvector
    vector<int> v(n);
    for(int i = 0; i < n; i++)
        cin >> v[i];
    return v;
}

vector<int> pf(vector<int>& arr) {
    int n = arr.size();
    vi prefix(n);
    prefix[0] = arr[0];
    for(int i = 1; i < n; i++) {
        prefix[i] = prefix[i-1] + arr[i];
    }
    return prefix;
}

void solve() {
    int n{} , q{};
    cin >> n >> q;
    vi stdiff = rv(n);
    sort(all(stdiff));
    vi stp = pf(stdiff);
    vi ques = rv(q);

    for(int i = 0 ; i < ques.size(); i++)
    {
        int idx = upper_bound(all(stdiff), ques[i]) - stdiff.begin();
        if(idx != 0) {
            cout << stp[idx-1] << " ";
        } else {
            cout << 0 << " ";
        }
    }
    cout << endl;
}

main() {
    IOS
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}