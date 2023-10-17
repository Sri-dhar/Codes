#include<bits/stdc++.h>

using namespace std;
int mid;

void printGrid(vector<vector<int>> grid)
{
    int n = grid.size();
    for(int i=0; i<n ; i++)
    {
        for(int j=0; j<n ; j++)
        {
            cout << " "<< grid[i][j] << " ";
        }
        cout<<"\n";
    } 
}

int bs(vector<int> grid , int target)
{
    int low = 0;
    int high = grid.size()-1;
    while(high > low)
    {
        mid = low + (high-low)/2;
        if(grid[mid] == target) return mid;
        else if ( grid[mid] > target ) high = mid-1;
        else if ( grid[mid] < target ) low = mid+1;
    }
    return low;
}

int main()
{
    cout<<"Enter the value of n : "<<endl;
    int n; 
    cin>>n;
    vector<vector<int>> grid (n, vector<int> (n));

    for(int i=0; i<n ; i++)
    {
        for(int j=0; j<n ; j++)
        {
            cin>> grid[i][j];
        }
    }    

    cout<<"Enter the target: "<<endl;
    int target{};
    cin>>target;

    vector<int> arr;
    for(int i=0; i<n; i++)
    {   
        arr.push_back(grid[0][i]);
    }
    int xPos = bs(arr,target);
    std::cout<<"Xpost " <<xPos;
    vector<int> arr2;

    for(int i=0; i<n ;i++)
    {
        arr2.push_back(grid[xPos][i]);
    }
    
    int yPos = bs(arr,target);
    std::cout<<"Ypos "<<yPos <<endl;
    if( grid[xPos-1][yPos-1] == target)
    {
        cout<<"The target is found at : "<<xPos<<" "<<yPos<<endl;
    }
    else if(grid[xPos][yPos] == target)
    {
    	cout<<"The target is found at : "<<xPos+1<<" "<<yPos+1<<endl;
    }
    else {
        cout<<"The target is not found";
    }

}