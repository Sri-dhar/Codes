#include<iostream>
#include<vector>
#include<climits>

using namespace std;

vector<int> path;
int maxi = INT_MIN;

void printMatrix(vector<vector<int>> &matrix)
{   
    cout << endl;
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[0].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }        
}

int LIS(vector<vector<int>> &matrix)
{
    int m = matrix.size();
    int n = matrix[0].size();
    
    vector<vector<int>> grid(m, vector<int>(n, 1));
    
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int x = 0; x < i; x++)
            {
                for(int y = 0; y < j; y++)
                {
                    if(matrix[i][j] > matrix[x][y])
                    {
                        grid[i][j] = max(grid[i][j], grid[x][y] + 1);
                    }
                }
            }
            
            if(grid[i][j] > maxi)
            {
                maxi = grid[i][j];
                path.clear();
                path.push_back(matrix[i][j]);
            }
        }
    }

    printMatrix(grid);
    return maxi;
}

int main()
{   
    cout << "Enter the dimensions of the matrix: " << endl;
    int m, n;
    cin >> m >> n;

    vector<vector<int>> input(m, vector<int>(n, 0));

    cout << "Enter the elements of the matrix: " << endl;
    
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> input[i][j];
        }
    }

    int length = LIS(input);
    cout << "Length: " << length << endl;
    cout << "The Path is: ";
    for(int i = 0; i < path.size(); i++)
    {
        cout << " " << path[i];
    }
    
    return 0;
}
