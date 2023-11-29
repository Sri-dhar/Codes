#include<bits/stdc++.h>
using namespace std;

vector<int> ans;
int len = -1;

int max(int a,int b){
	return (a>b)?a:b;
}

void LISrec(vector<int>arr , int n , int d , int idx , int length,vector<vector<int>>& memo)
{	
	if(memo[idx][arr.size()] != -1)
	{
		len = max(len , memo[idx][arr.size()]);
	}
    if(idx == n) 
    {   
        len = (len >=length) ? len : length;
        memo[idx][arr.size()] = len;
        return;
    }
    if(idx == 0) {
        ans.push_back(arr[idx]);
        LISrec(arr,n,d,idx+1 , length+1,memo);
        ans.pop_back();
        LISrec(arr,n,d,idx+1 , length,memo);
    }
    else
    {
        if(arr[idx] - ans[ans.size()-1] >= d)
        {
            ans.push_back(arr[idx]);
            LISrec(arr,n,d,idx+1 , length+1,memo);
            ans.pop_back();
            LISrec(arr,n,d,idx+1 , length,memo);
        }
        else
        {
        	LISrec(arr,n,d,idx+1 , length,memo);
        }
    }
    return;
}

void LISmemo(vector<int> arr, int d)
{
    int n = arr.size();
    vector<vector<int>> memo (n+1, vector<int> (n+1,-1));
    LISrec(arr, n , d , 0 , 0 ,memo);
}

int LIS_dp(vector<int> arr,  int d)
{
	int maxi = 1;
	int n = arr.size();
	vector<int> memo(arr.size(),1);
	for(int i=0; i<arr.size(); i++)
	{
		for(int j =0; j<i; j++)
		{
			if(arr[i] - arr[j] >= d)
			{
			memo[i] = max(memo[i] , memo[j]+1 );
			maxi = max(maxi, memo[i]);
			}
		}
	}
	return maxi;
}


int main()
{
    cout<<"Enter the array :"<<endl;
    cout<<"Press -1 to stop "<<endl;
    vector<int> arr;

    while(1)
    {
        int temp=0;
        cin>>temp;
        if(temp == -1) break;
        arr.push_back(temp);
    }

    cout<<"Enter the value of d : "<<endl;
    int d{};
    cin>>d;

    LISmemo(arr,d);

    cout<<" "<<endl;

    for(size_t i=0; i<ans.size(); i++)
    {
        cout<<ans[i]<<" ";
    }

    std::cout<<"Length is : "<<len <<"\nLength using DP :" <<LIS_dp(arr,d);
}
