#include <bits/stdc++.h>

using namespace std;

int main()
{
    vector<int> a = {1, 2, 1, 4, 5};
    vector<int> prefixOne;
    int temp = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == 1)
            prefixOne.push_back(++temp);
        else
            prefixOne.push_back(temp);
    }

    for (int i = 0; i < prefixOne.size(); i++)
    {
        cout << prefixOne[i] << " ";
    }
    cout << endl;
    int l = 1, r = 3;
    cout<<"PrefixOne[r-1]: "<<prefixOne[r-1]<<endl; 
    int ans = prefixOne[r-1];
    if (l != 1)
        ans -= prefixOne[l - 1];
    cout << ans << endl;
}