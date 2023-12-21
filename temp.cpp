#include <bits/stdc++.h>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define MOD 1e9+7
#define ll long long
#define initPQ(type, name) priority_queue<type> name
#define initQ(type, name) queue<type> name
#define popQ(name) if (!name.empty()) name.pop()
#define pushQ(name, value) name.push(value)
#define topQ(name) (!name.empty() ? name.top() : -1)
#define emptyQ(name) name.empty()
#define sizeQ(name) name.size()
#define clearQ(name) while (!name.empty()) name.pop()
#define initV(type, name, size) vector<type> name(size)

void solve()
{
    int n;
    cin >> n;
    initV(int, a, n);
    initV(int, b, n);
    vector<pair<int,int>> v(n);
    long long ans = 0, o = 0;

    for(int &x: a) cin >> x;
    for(int &x: b) cin >> x;

    for(int i = 0; i < n; i++) 
        v[i] = {a[i] + b[i], i};

    sort(v.begin(), v.end());

    for(int i = n - 1; i >= 0; i--,o++)
    {
        if (o % 2 == 0) 
            ans += a[v[i].second] - 1;
        else 
            ans -= b[v[i].second] - 1;
    }
    cout << ans << '\n';
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