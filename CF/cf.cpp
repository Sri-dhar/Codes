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
#define vc vector<char>
#define pii pair<int, int>
#define all(x) x.begin(), x.end()
#define vvi vector<vector<int>>
#define vpi vector<pair<int, int>>
#define NO puts("NO")
#define YES puts("YES")

long long result = 0;

int isodd(int n) { return n % 2; }
int iseven(int n) { return !isodd(n); }

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

template <typename T>
vector<T> rv(int n)
{
    vector<T> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    return v;
}

vvi rvm(int n, int m)
{ // readvectormatrix
    vvi v(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> v[i][j];
    return v;
}

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

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}

// int min(int a, int b)
// {
//     if (a < b)
//         return a;
//     return b;
// }

// long long int findBitwiseOR(long long int L, long long int R) {
// 	long long int ans = 0;
// 	for(int i = 62; i >= 0; i--) {
// 		if((L & (1LL << i)) == (R & (1LL << i))) {
// 			ans += (L & (1LL << i));
// 		} else {
// 			ans += (1LL << (i+1)) - 1;
// 			break;
// 		}
// 	}
// 	return ans;
// }
vi countOfOnePrefix;
vi summationPrefix;

bool check(vector<int> &c, int l, int r)
{
    int noOfOne = countOfOnePrefix[r-1] ;//- ((l == 1) ? 0 : countOfOnePrefix[l - 1]);
    if(l > 1) noOfOne -= countOfOnePrefix[l-1];
    if (noOfOne == 0)
        return true;
    int sumLtoR = summationPrefix[r-1];// - (l ==1 ? 0 : summationPrefix[l-1]);
    if(l > 1) sumLtoR -= summationPrefix[l-1];
    int sum = sumLtoR - (r-l+1);
    return sum >= noOfOne;
}

void solve()
{
    int n = read();
    int q = read();
    vi c = rv(n);
    vpi queries(q);
    for (int i = 0; i < q; i++)
    {
        queries[i].first = read();
        queries[i].second = read();
    }

    int temp = 0;
    int summation = 0;
    summationPrefix.pb(c[0]);
    for(int i=0; i<n; i++)
    {
        if(c[i] == 1) countOfOnePrefix.pb(++temp);
        else countOfOnePrefix.pb(temp);
        if(i > 0){
            summationPrefix.pb(summationPrefix[i-1] + c[i]);
        }
    }
  

    for (auto x : queries)
    {
        if (x.first == x.second)
        {
            NO;
            continue;
        }
        else if (check(c, x.first, x.second))
        {
            YES;
        }
        else
        {
            NO;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = read();
    while (t--)
    {
        solve();
    }

    return 0;
}