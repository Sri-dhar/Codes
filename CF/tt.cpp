#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    const int MOD = 1000000007;
    
    // Helper function to check if array forms a wave
    bool isWave(const vector<int>& arr) {
        bool shouldBeGreater = arr[0] < arr[1];
        
        for(int i = 1; i < arr.size() - 1; i++) {
            if(shouldBeGreater) {
                if(arr[i] <= arr[i+1]) return false;
            } else {
                if(arr[i] >= arr[i+1]) return false;
            }
            shouldBeGreater = !shouldBeGreater;     
        }
        return true;
    }
    
    // Recursive function to generate all possible combinations
    long long generateWaves(vector<int>& arr, int m, int pos) {
        // Base case: if we've filled all positions, check if it's a valid wave
        if(pos >= arr.size()) {
            // Check both possible wave patterns
            bool pattern1 = true;  // a1 > a2 < a3 > a4 ...
            bool pattern2 = true;  // a1 < a2 > a3 < a4 ...
            
            for(int i = 0; i < arr.size()-1; i++) {
                if(i % 2 == 0) {
                    if(pattern1 && arr[i] <= arr[i+1]) pattern1 = false;
                    if(pattern2 && arr[i] >= arr[i+1]) pattern2 = false;
                } else {
                    if(pattern1 && arr[i] >= arr[i+1]) pattern1 = false;
                    if(pattern2 && arr[i] <= arr[i+1]) pattern2 = false;
                }
            }
            
            return (pattern1 || pattern2) ? 1 : 0;
        }
        
        // If current position is not -1, move to next position
        if(arr[pos] != -1) {
            return generateWaves(arr, m, pos + 1);
        }
        
        // Try all possible values for current position
        long long ways = 0;
        for(int i = 1; i <= m; i++) {
            arr[pos] = i;
            ways = (ways + generateWaves(arr, m, pos + 1)) % MOD;
        }
        arr[pos] = -1;  // Backtrack
        
        return ways;
    }

public:
    int countWaysToCreateWave(vector<int> arr, int m) {
        return generateWaves(arr, m, 0);
    }
};

int main() {
    Solution sol;
    
    // Test case 1: Example from the problem
    vector<int> arr1 = {-1, 3, -1};
    int m1 = 3;
    cout << "Test case 1 result: " << sol.countWaysToCreateWave(arr1, m1) << endl;
    // Expected output: 4
    
    // Test case 2: Longer array
    vector<int> arr2 = {-1, 2, -1, 4, -1};
    int m2 = 4;
    cout << "Test case 2 result: " << sol.countWaysToCreateWave(arr2, m2) << endl;
    
    // Test case 3: All -1s
    vector<int> arr3 = {-1, -1, -1, -1};
    int m3 = 2;
    cout << "Test case 3 result: " << sol.countWaysToCreateWave(arr3, m3) << endl;
    
    // Test case 4: No -1s
    vector<int> arr4 = {1, 3, 2, 4};
    int m4 = 4;
    cout << "Test case 4 result: " << sol.countWaysToCreateWave(arr4, m4) << endl;
    
    return 0;
}