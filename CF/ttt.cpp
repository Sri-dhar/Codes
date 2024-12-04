#include <iostream>
#include <vector>
using namespace std;

// Function to calculate Bell Numbers up to n using DP
int countValidPartitions(int n) {
    // Base case for small sets
    if (n <= 1) return 0; // No valid partitions for sets of size 1

    // DP table to store Bell numbers up to B[n]
    vector<vector<int>> bell(n + 1, vector<int>(n + 1, 0));
    
    // Base cases
    bell[0][0] = 1;

    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        // First element in the row is the last element from the previous row
        bell[i][0] = bell[i - 1][i - 1];
        
        for (int j = 1; j <= i; j++) {
            // Bell triangle relation
            bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
        }
    }
    
    // The nth Bell number is found at bell[n][0]
    int totalPartitions = bell[n][0];
    
    // Exclude the partition that only includes the entire set as a single subset
    return totalPartitions - 1;
}

int main() {
    int n;
    cin >> n;
    cout << countValidPartitions(n) << endl;
    return 0;
}
