#include <iostream>
#include <vector>
#include <climits>
#include <map>
using namespace std;
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

void solve()
{
    map<char, int> mp;
    mp['S'] = 1;
    mp['M'] = 2;
    mp['L'] = 3;
    mp['X'] = 0;

    string s1, s2;
    cin >> s1;
    cin >> s2;

    if (s1 == s2)
    {
        cout << "=" << endl;
        return;
    }

    int s11 = 0, s22 = 0;
    for (int i = 0; i < s1.size(); i++)
        s11 += mp[s1[i]];
    for (int i = 0; i < s2.size(); i++)
        s22 += mp[s2[i]];

    if (s11 > s22)
    {
        cout << ">" << endl;
        return;
    }
    else if (s11 < s22)
    {
        cout << "<" << endl;
        return;
    }
    else if (s11 == s22)
    {
        int xs1 = 0, xs2 = 0;
        for (int i = 0; i < s1.size(); i++)
            if (s1[i] == 'X')
                xs1++;
        for (int i = 0; i < s2.size(); i++)
            if (s2[i] == 'X')
                xs2++;
        if (xs1 > xs2)
        {
            cout << "<" << endl;
            return;
        }
        else if (xs1 < xs2)
        {
            cout << ">" << endl;
            return;
        }
        else
        {
            cout << "=" << endl;
        }
    }
}

int main()
{
    IOS
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
