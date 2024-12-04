#include <iostream>
#include <string>
using namespace std;

string toBinary(int n)
{
    if (n <= 0)
        return "0";

    string binary = "";
    while (n > 0)
    {
        binary = (n % 2 ? "1" : "0") + binary;
        n /= 2;
    }
    return binary;
}

void solve()
{
    const int MOD = 998244353;
    int n;
    cin >> n;

    if (n <= 0)     
    {
        cout << "0\n";
        return;
    }

    string result = "";
    for (int i = 1; i <= n; i++)
    {
        result += toBinary(i);

        if (result.length() > 18)
        {
            long long num = stoll(result.substr(max(0, (int)result.length() - 18)));
            result = to_string(num % MOD);
        }
    }

    long long finalNum = 0;
    finalNum = stoll(result);           

    cout << finalNum % MOD << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    cin >> t;

    while (t--)
    {
        solve();
    }
    return 0;
}
