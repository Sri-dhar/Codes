#include<bits/stdc++.h>
using namespace std;

void countingSortUnstable(vector<int>&arr)
{
    int maxi = INT_MIN;
    int mini = INT_MAX;
    for(int i: arr) {
        maxi = max(maxi,i);
        mini = min(mini,i);
    }

    vector<int> cumSum(maxi - mini +1,0);

    for(int i=0; i<arr.size(); i++) cumSum[arr[i] - mini]++;

    // cout<<"Printing the cumSum"<<endl;
    // for(auto i: cumSum) cout<<i<<" ";
    arr.clear();
    for(int i=0; i<cumSum.size(); i++)
    {
        while(cumSum[i] != 0)
        {
            arr.push_back(i+mini);
            cumSum[i]--;
        }
    }

    for(auto i: arr) cout<<i<<" ";

}

void countingSortStable(vector<int>& arr)
{
    int maxi = INT_MIN;
    int mini = INT_MAX;
    for(int i: arr) {
        maxi = max(maxi,i);
        mini = min(mini,i);
    }
    vector<int> cumSum(maxi - mini +1,0);
    for(int i=0; i<arr.size(); i++) cumSum[arr[i] - mini]++;
    
    for(int i=1; i<cumSum.size() ; i++) cumSum[i] += cumSum[i-1];
    
    vector<int> sortedArr(arr.size());
    for(int i=arr.size()-1; i>=0; i--)
    {
        sortedArr[cumSum[arr[i] - mini] - 1] = arr[i];
        cumSum[arr[i] - mini]--;
    }
    
    arr = sortedArr;
    
    for(auto i: arr) cout<<i<<" ";
}

int main()
{
    //Counting Sort
    vector<int> arr ;
    cout<<"Enter the elements of the array : "<<endl;
    cout<<"Enter -100 to stop"<<endl;
    while(1)
    {
        int temp;
        cin>>temp;
        if(temp == -100 ) break;
        arr.push_back(temp);
    }
    cout<<"The output of Unstable Counting sort : ";
    countingSortUnstable(arr);
    cout<<endl<<endl;
    cout<<"The output of Stable Counting sort : ";
    countingSortStable(arr);

}