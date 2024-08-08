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

// vvi rvm(int n, int m)
// { // readvectormatrix
//     vvi v(n, vector<int>(m));
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < m; j++)
//             cin >> v[i][j];
//     return v;
// }

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

void solve();

signed main()
{
    IOS int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}

int f(int x) {
    if (x == 0) return 1;
    int length = 0;
    while (x) {
        length++;
        x /= 10;
    }
    return length;
}

void solve()
{
    int n = read();
    vi a = rv(n);
    vi b = rv(n);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    priority_queue<int> qa(a.begin(), a.end());
    priority_queue<int> qb(b.begin(), b.end());
    int ans = 0;
    while (!qa.empty()) {
        if (qa.top() == qb.top()) {
            qa.pop();
            qb.pop();
            continue;
        }
        ++ans;
        if (qa.top() > qb.top()) {
            int newSize = to_string(qa.top()).size();
            qa.pop();
            qa.push(newSize);
        } else {
            int newSize = to_string(qb.top()).size();
            qb.pop();
            qb.push(newSize);
        }
    }
    cout << ans << endl;
}