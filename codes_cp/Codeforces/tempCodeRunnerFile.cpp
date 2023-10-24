#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

void solve()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        cin>> arr[i];
    }
    sort(arr.begin(),arr.end());  
    for(int i=0;i<n;i++){
        cout << arr[i];
    }  
}

int main()
{
    IOS 

    solve();
    return 0;
}