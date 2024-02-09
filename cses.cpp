#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define MOD 1e9+7
#define ll long long

void solve()
{
    //CSES PROBLEM SET
    //Permutations
    int n;
    cin >> n;
    if(n == 1)
    {
        cout << 1 << endl;
        return;
    }
    if(n < 4)
    {
        cout << "NO SOLUTION" << endl;
        return;
    }
    for(int i=2; i<=n; i+=2)
    {
        cout << i << " ";
    }
    for(int i=1; i<=n; i+=2)
    {
        cout << i << " ";
    }
    cout << endl;

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