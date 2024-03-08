#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define IOS                         \
    ios_base::sync_with_stdio(0);   \
    cin.tie(0);                     \
    cout.tie(0);
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

void solve(){
	int n,k;
	cin>>n>>k;
    vector<int> s(k);
	for(int i=0;i<k;++i) cin>>s[i];
	vector<int>a;

	for(int i=1;i<k;++i) a.push_back(s[i]-s[i-1]);

	for(int i=1;i<a.size();++i){
		if(a[i]<a[i-1]){
			cout<<"NO\n";
			return;
		}
	}

	if(k==1)
    {
		cout<<"YES\n";
        return;
	}

	int t = n-k+1;
	if(t*a[0]<s[0]) cout<<"NO\n";
	else cout<<"YES\n";
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
