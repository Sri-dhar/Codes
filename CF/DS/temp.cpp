#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> a {2,3,435,33,34,534,123,3};
    a.erase(remove(a.begin(), a.end(),3),a.end());
    a.erase(a.begin()+3);
    cout<<"The vector"<<endl;
    for(auto x:a)
        cout<<x<<" ";

    a.push_back(324);
    a.push_back(3245);
    a.pop_back();

    cout<<"The vector"<<endl;
    for(auto x:a)
        cout<<x<<" ";

    
}