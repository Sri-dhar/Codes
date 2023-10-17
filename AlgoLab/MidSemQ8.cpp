#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>

using namespace std;

vector<int> path;
int maxi = INT_MIN;

void printMatrix(vector<vector<int>> &matrix)
{   
    cout<<endl;
    for(int i=0; i<matrix.size(); i++)
    {
        for(int j=0; j<matrix[0].size(); j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }        
}

void printpath(vector<vector<int>> &matrix, vector<vector<int>> &grid, pair<int, int> add, int len)
{
	cout<<"\naddress of max element : "<<add.first<<" "<<add.second;
    while (len > 0)
    {
        path.push_back(matrix[add.first][add.second]);

        if (add.second < grid[0].size()-1 && grid[add.first][add.second] == grid[add.first][add.second + 1] + 1)
        {
            add.second++;
            
            cout<<" "<<add.first<<" "<<add.second<<"loop1"<<endl;

        }
        else if (add.first < grid.size() && grid[add.first][add.second] == grid[add.first + 1][add.second] + 1)
        {
            add.first++;
            
            cout<<" "<<add.first<<" "<<add.second<<"loop2"<<endl;
        }
        len--;
    }

}



int LIS (vector<vector<int>> &matrix)
{
	// std::cout<<" matrix.size() "<<matrix.size() <<" matrix[0].size() "<< matrix[0].size()<<endl;
    pair<int,int> maxAdd;

    vector<vector<int>> grid (matrix.size(),vector<int>(matrix[0].size(),1));
    for(int i =matrix.size()-2; i>=0; i--)
    {
        for(int j=matrix[0].size()-2; j>=0; j--)
        {
            if(matrix[i][j] > matrix[i+1][j] && matrix[i][j] > matrix[i][j+1])
            {
                grid[i][j] = max(grid[i][j+1], grid[i+1][j])+1;
            }
            else if (matrix[i][j] > matrix[i+1][j] && !(matrix[i][j] > matrix[i][j+1]))
            {
                grid[i][j] = 1 + grid[i+1][j];
            }
            else if (!(matrix[i][j] > matrix[i+1][j]) && (matrix[i][j] > matrix[i][j+1]))
            {
                grid[i][j] = 1 + grid[i][j+1];
            }
            else
            {
                grid[i][j] = 0;
            }

            int oldmax = maxi;
            maxi = max(maxi , grid[i][j]);
            if(maxi != oldmax) {
            	maxAdd.first = i;
            	maxAdd.second = j;
            }
            

        }
    }
    printMatrix(grid);
    printpath(matrix,grid,maxAdd,maxi);
    return maxi;
}

int main()
{   
    cout<<"Enter the dimensions of the matrix : "<<endl;
    int m, n;
    cin>>m>>n;

    vector<vector<int>> input(m,vector<int>(n,1));

    cout<<"Enter the elements of the matrix : "<<endl;
    
    for(int i=0; i<m ; i++)
        for(int j=0; j<n ;j++)
        {
            int temp;
            cin>>temp;
            input[i][j] = temp;
        }
        

    int length = LIS(input);
    cout<<"\nLength : "<< length << endl;
    cout<<"The Path is : ";
    for(int i=0; i<path.size(); i++)
        cout<<" "<<path[i];
}
