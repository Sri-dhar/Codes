#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:

    vector<bool> soe(int n)
    {
        vector<bool> prime(n + 1, true);
        prime[0] = prime[1] = false;
        for (int p = 2; p * p <= n; p++)
        {
            if (prime[p] == true)
            {
                for (int i = p * p; i <= n; i += p)
                    prime[i] = false;
            }
        }
        return prime;
    }

    vector<int> closestPrimes(int left, int right)
    {
        if(left == right) return {-1,-1};
        vector<bool> primes = soe(right);
        vector<int> primeNumbers;
        for (int i = left; i <= right; i++)
        {
            if (primes[i])
            {
                primeNumbers.push_back(i);
            }
        }

        vector<int> res;
        int minDiff = INT_MAX;
        int minPrime1 = -1, minPrime2 = -1;
        for (int i = 0; i < primeNumbers.size() - 1; i++)
        {
            int diff = primeNumbers[i+1] - primeNumbers[i];
            if (diff < minDiff)
            {
                minDiff = diff;
                minPrime1 = primeNumbers[i];
                minPrime2 = primeNumbers[i+1];
            }
        }
        if (minPrime1 != -1 && minPrime2 != -1) {
            res.push_back(minPrime1);
            res.push_back(minPrime2);
        }
        return res;
    }
};

int main()
{
    Solution s;
    vector<int> res = s.closestPrimes(4,6);
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << " ";
}