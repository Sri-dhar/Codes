#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
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
    int n = 0;
    cin >> n;
    cout<<n<<" ";
    while(n!=1)
    {
        if(n%2)
        {
            n = n*3+1;
            cout<<n<<" ";
        }
        else
        {
            n /=2;
            cout<<n<<" ";
        }
    }
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