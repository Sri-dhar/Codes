#include <bits/stdc++.h>
using namespace std;
#define IOS                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

void solve()
{
    int n ;
    cin >> n;
    cout<< (n+1)/2 << endl;
    for(int i=0; i<(n+1)/2; i++)
        cout<< 3*i+1 <<" "<< 3*(n-i) << endl;
}

int main()
{
    IOS 
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}