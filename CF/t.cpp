#include <bits/stdc++.h>
using namespace std;

bool allSame(vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] != v[0])
            return false;
    }
    return true;
}

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    int maxi = *max_element(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++)
        v[i] = maxi - v[i];

    int generation = 1;

    while (allSame(v) == false && generation <= 10)
    {
        if (generation & 1)
        {
            for (int i = 0; i < v.size(); i++)
            {
                if (v[i] != 2 and v[i] != 0)
                {
                    v[i] -= 1;
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < v.size(); i++)
            {
                if (v[i] != 0)
                    if (v[i] != 1)
                    {
                        v[i] -= 2;
                        break;
                    }
            }
        }

        // for (int i = 0; i < v.size(); i++)
        //     cout << v[i] << " ";
        // cout << endl;
        generation++;
    }

    cout << generation-1 << endl;
    return 0;
}
