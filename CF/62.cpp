// #include<bits/stdc++.h>
// using namespace std;

// // Helper function to find lower bound
// int getLowerBound(int num, const vector<int>& nums) {
//     int lower = 0;
//     for(int x : nums) {
//         if(x < num && x > lower) {
//             lower = x;
//         }
//     }
//     return lower;
// }

// // Main function to calculate sum of lower bounds of factors
// int findLowerBound(int N, vector<int> nums) {
//     // Find all factors of N
//     vector<int> factors;    
//     for(int i = 1; i * i <= N; i++) {
//         if(N % i == 0) {
//             factors.push_back(i);
//             if(i != N/i) {  // Avoid duplicates for perfect squares
//                 factors.push_back(N/i);
//             }
//         }
//     }
    
//     // Calculate sum of lower bounds for all factors
//     int total = 0;
//     for(int factor : factors) {
//         total += getLowerBound(factor, nums);
//     }
//     return total;
// }

// int main() {
//     int N;
//     cin >> N;  // Input N
    
//     int m;
//     cin >> m;  // Input array length
    
//     vector<int> nums(m);
//     for(int i = 0; i < m; i++) {
//         cin >> nums[i];  // Input array elements
//     }
    
//     int result = findLowerBound(N, nums);
//     cout << result << endl;
    
//     return 0;
// }

#include<bits/stdc++.h>
using namespace std;

// Helper function to find lower bound
int getLowerBound(int num, const vector<int>& nums) {
    int lower = 0;
    for(int x : nums) {
        if(x < num && x > lower) {
            lower = x;
        }
    }
    return lower;
}

int findLowerBound(int N, vector<int> nums) {
    vector<int> factors;    
    for(long long i = 1; i * i <= N; i++) {  // Changed to long long
        if(N % i == 0) {
            factors.push_back(i);
            if(i != N/i) {  // Avoid duplicates for perfect squares
                factors.push_back(N/i);
            }
        }
    }
    
    long long total = 0;  // Changed to long long
    for(int factor : factors) {
        total += getLowerBound(factor, nums);
    }
    return total;
}

int main() {
    int N;
    cin >> N;
    
    int m;
    cin >> m;
    
    vector<int> nums(m);
    for(int i = 0; i < m; i++) {
        cin >> nums[i];
    }
    
    int result = findLowerBound(N, nums);
    cout << result << endl;
    
    return 0;
}