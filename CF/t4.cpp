#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <string>
#include <sstream>
#include <climits>  // Added for LLONG_MAX

using namespace std;

// Function to calculate combinations (n choose k)
long long comb(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    k = min(k, n - k);  // Take advantage of symmetry
    
    long long c = 1;
    for (int i = 0; i < k; ++i) {
        // Prevent integer overflow
        if (c > LLONG_MAX / (n - i)) {
            return -1; // Indicate overflow
        }
        c *= (n - i);
        c /= (i + 1);
    }
    return c;
}

// Bell number calculation using dynamic programming
long long bell(int n) {
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1;
    
    vector<long long> b(n + 1, 0);
    b[0] = 1;
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            // Check for potential overflow
            if (b[j] == -1 || comb(i - 1, j) == -1) {
                return -1;
            }
            
            long long product = b[j] * comb(i - 1, j);
            if (product < 0 || (b[i] > 0 && b[i] > LLONG_MAX - product)) {
                return -1; // Indicate overflow
            }
            b[i] += product;
        }
    }
    return b[n];
}

int main() {
    try {
        // Read the entire line of input
        string line;
        getline(cin, line);
        
        // Create stringstream for parsing numbers
        stringstream ss(line);
        set<int> unique_elements;
        int num;
        
        // Read numbers from the stringstream
        while (ss >> num) {
            if (num < 0) {
                cerr << "Error: Negative numbers are not allowed." << endl;
                return 1;
            }
            unique_elements.insert(num);
        }
        
        // Check if we have any input
        if (unique_elements.empty()) {
            cerr << "Error: No input provided." << endl;
            return 1;
        }
        
        // Calculate the size of the unique elements set
        int unique_count = unique_elements.size();
        
        // Calculate and print the result based on the unique count
        if (unique_count > 1) {
            long long result = bell(unique_count) - 1;
            if (result == -1) {
                cerr << "Error: Result too large to compute." << endl;
                return 1;
            }
            cout << result << endl;
        } else {
            cout << 0 << endl;
        }
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}   