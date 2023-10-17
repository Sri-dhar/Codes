#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int ans{};  

void medofmed(std::vector<int> &arr)
{
    if(arr.size() <= 5) {
        std::sort(arr.begin(), arr.end());
        ans = arr[arr.size() / 2];
        return ;
    }

    int n = arr.size();
    int i{};
    int divisions = (n % 5 != 0) ? n / 5 + 1 : n / 5 ;

    for(i = 0; i < divisions-1; i++) std::sort(arr.begin() + i * 5, arr.begin() + (i + 1) * 5);
    std::sort(arr.begin()+5*i, arr.begin()+5*i+n%5);

    std::vector<int> arr2;
    for(int i=2; i<n; i+= 5) arr2.push_back(arr[i]);

    medofmed(arr2);

}

int main()
{
    vector<int> arr;
    cout << "Enter the values of the array:" << endl;
    cout << "Enter -1 to stop" << endl;
    int t = 0;
    while (1) {
        cin >> t;
        if (t == -1) break;
        arr.push_back(t);
    }
    medofmed(arr);

    int count = 0;

    for(int i=0; i<arr.size(); i++)
        if(arr[i] <= ans and count++ < arr.size()/4)
            cout<<arr[i]<<" ";
    std::cout<<" || ";

    count = 0;

    for(int i=0; i<arr.size(); i++)
        if(arr[i] >= ans and count++ < arr.size()/4)
            cout<<arr[i]<<" ";
    
    std::cout<<std::endl;
    sort(arr.begin(), arr.end());
    std::cout<<"The actual median is "<<arr[arr.size()/2];
}