#include<bits/stdc++.h>
using namespace std;
int main()
{
    // auto add = [](int a, int b)->int
    // {
    //     return a+b;
    // };

    // cout<<add(3,4);

    vector<int> vec{1,3,4,5,4,6,23};
    for_each(vec.begin(),vec.end(),[](int &a){a = a*3;});

    for(auto x:vec)
    cout<<x<<" ";
}