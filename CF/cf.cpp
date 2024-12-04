#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define IOS                     \
  ios_base::sync_with_stdio(0); \
  cin.tie(0);                   \
  cout.tie(0);
#define int long long
#define ll long long
#define pb push_back
#define pi pair<int, int>
#define mp make_pair
#define ff first
#define ss second
#define vi vector<int>
#define vc vector<char>
#define pii pair<int, int>
#define all(x) x.begin(), x.end()
#define vvi vector<vector<int>>
#define vpi vector<pair<int, int>>
#define NO cout << "NO\n"
#define YES cout << "YES\n"
#define take(x) \
  int x;        \
  cin >> x

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

template <typename T>
vector<T> pv(vector<T> &v)
{
  for (auto &i : v)
    cout << i << " ";
  cout << endl;
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

vector<int> sf(vector<int> &arr)
{
  int n = arr.size();
  vi suffix(n);
  suffix[n - 1] = arr[n - 1];
  for (int i = n - 2; i >= 0; i--)
    suffix[i] = suffix[i + 1] + arr[i];
  return suffix;
}

int gcd(int a, int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int lcm(int a, int b) { return (a / gcd(a, b)) * b; }

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
void precompute();

unordered_map<int, int> mapp;

signed main()
{
  IOS int t = 1;
  cin >> t;
  while (t--)
  {
    precompute();
    solve();
    fflush(stdin);
    fflush(stdout);
  }
  return 0;
}

void precompute() {}

string getBinary(int n)
{
  string s = "";
  while (n > 0)
  {
    s += to_string(n % 2);
    n /= 2;
  }
  reverse(s.begin(), s.end());
  return s;
}

string llToString(long long a)
{
  string s = "";
  while (a > 0)
  {
    s += to_string(a % 10);
    a /= 10;
  }
  reverse(s.begin(), s.end());
  return s;
}

void solve()
{
  int mod = 998244353;
  int n = read();
  string res = "";
  for (int i = 1; i <= n; i++)
  {
    string s = getBinary(i);
    res.append(s);
    res = llToString(stoll(res) % mod); 
  }
  int ans = stoi(res) % mod;
  cout << ans << endl;
}
                    