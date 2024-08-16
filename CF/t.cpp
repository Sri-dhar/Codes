#include<bits/stdc++.h>
using namespace std;    

class Solution {
public:
    int minDays(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> visited(m, vector<int>(n, 0));
        map<pair<int,int>,int> onesInGrid;
        bool foundMoreThanOne = false;
        int componentCount = 0;
        
        for(int i = 0; i < m && !foundMoreThanOne; ++i) {
            for(int j = 0; j < n && !foundMoreThanOne; ++j) {
                if(grid[i][j]) {
                    ++onesInGrid[{i,j}];
                }
                if(grid[i][j] && !visited[i][j]) {
                    if (componentCount > 0) {
                        foundMoreThanOne = true;
                    } else {
                        dfs(grid, visited, i, j);
                        ++componentCount;
                    }
                }
            }
        }
        
        return foundMoreThanOne ? 2 : componentCount;
    }

    void dfs(const vector<vector<int>>& grid, vector<vector<int>>& visited, int x, int y) {
        int m = grid.size();
        int n = grid[0].size();
        
        vector<int> directions = {-1, 0, 1, 0, 0, -1, 0, 1};
        
        visited[x][y] = 1;
        
        for(int d = 0; d < 4; ++d) {
            int newX = x + directions[d*2];
            int newY = y + directions[d*2 + 1];
            
            if(newX >= 0 && newX < m && newY >= 0 && newY < n && grid[newX][newY] && !visited[newX][newY]) {
                dfs(grid, visited, newX, newY);
            }
        }
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = {{1,1},{1,1}};
    cout << s.minDays(grid) << endl;
    return 0;
}