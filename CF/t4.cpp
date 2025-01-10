#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    class DSU {
        vector<int> parent;
        public:
        DSU(int n) : parent(n+1, -1) {}
        int findParent(int x) {
            if(parent[x] == -1) return x;
            return parent[x] = findParent(parent[x]);
        }
        bool join(int x, int y) {
            int X = findParent(x);
            int Y = findParent(y);
            if(X==Y) return false;
            parent[X] = Y;
            return true;
        }
    };
    
    int countComponents(vector<int>& nums, int threshold) {
        DSU dsu(threshold);
        int n = nums.size();
        int ans = 0;

        for(int i=0; i<nums.size(); i++) {
            if(nums[i] <= threshold) {
                for(int j=nums[i]; j <= threshold; j+=nums[i]) {
                    dsu.join(nums[i], j);
                }
            }
        }

        set<int> st; 
        for(int i=0; i<nums.size(); i++) {
            if(nums[i] > threshold) ans++; 
            else st.insert(dsu.findParent(nums[i]));
        }

        ans += st.size(); 
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> nums = {2, 4, 8, 3, 9};
    cout << s.countComponents(nums, 5); // Output: 4
    return 0;
}
