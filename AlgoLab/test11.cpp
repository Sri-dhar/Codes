class Solution {
public:
    int minGroupsForValidAssignment(vector<int>& nums) {
        unordered_map<int, int> freqMap;
        for (int num : nums) {
            freqMap[num]++;
        }
        
        vector<int> f;
        for (const auto& pair : freqMap) {
            f.push_back(pair.second);
        }
        
        sort(f.rbegin(), f.rend());
        
        int groups = 0;
        for (int frequency : f) {
            if (frequency == 0) continue;
            if (groups == 0) groups = 1;
            else if (frequency >= groups) groups = frequency + 1;
            else groups = groups + 1;
        }
        
        return groups;
    }
};
