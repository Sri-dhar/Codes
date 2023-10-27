class Solution
{
public:
    vector<int> findDuplicates(vector<int> &nums)
    {
        int n = nums.size();

        vector<int> result;

        for (int i = 0; i < n; i++)
        {
            int x = abs(nums[i]);

            if (nums[x - 1] < 0)
                result.emplace_back(x);

            else
                nums[x - 1] = -abs(nums[x - 1]);
        }

        return result;
    }
};