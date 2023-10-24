#include <bits/stdc++.h>
using namespace std;
#define IOS                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

void solve()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++)
        if (a[i] == 1)
            a[i]++;

    for (int i = 0; i < n - 1; i++)
    {
        if (a[i + 1] % a[i] == 0)
            a[i + 1]++;
    }

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

int main()
{
    IOS int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}