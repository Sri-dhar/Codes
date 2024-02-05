#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define MOD 1e9+7
#define ll long long

void solve()
{
    //codeforces 1826A
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i=0; i<n; i++)
        cin>>arr[i];

    int ans = -1;
    for(int j = 0; j<=n ;j++)
    {
        int count = 0;
        for(int i = 0; i<n; i++)
        {
            if(arr[i]>j) count++;
        }
        if(count == j) {
            ans = j;
            break;
        }
    }
    cout<<ans<<endl;

}

int main() {
    IOS
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}