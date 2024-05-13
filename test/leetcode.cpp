class Solution
{
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int ans{};
        int temp{};
        int n = gas.size();
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            cost[i] = gas[i] - cost[i];
            sum += cost[i];
            ans += cost[i];
            if (sum < 0)
            {
                sum = 0;
                temp = i + 1;
            }
        }
        if (ans < 0) return -1;
        return temp;
    }
};