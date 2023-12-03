#include <iostream>
#include <vector>

using namespace std;

void updateBIT(vector<int>& BITree, int index, int val)
{
    index = index + 1;

    while (index <= BITree.size())
    {
        BITree[index] += val;
        index += index & (-index);
    }
}

vector<int> constructBITree(vector<int>& arr)
{
    int n = arr.size();
    vector<int> BITree(n + 1, 0);

    for (int i = 0; i < n; i++)
        updateBIT(BITree, i, arr[i]);

    return BITree;
}

int getSum(vector<int>& BITree, int index)
{
    int sum = 0;
    index = index + 1;

    while (index > 0)
    {
        sum += BITree[index];
        index -= index & (-index);
    }
    return sum;
}

int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> freq(n);
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++)
        cin >> freq[i];

    vector<int> BITree = constructBITree(freq);

    while (true)
    {
        cout << "\n1. Update\n2. Get sum\n3. Print BIT\n4. Exit\n";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            int index, val;
            cout << "Enter the index and value to update: ";
            cin >> index >> val;
            updateBIT(BITree, index, val);
        }
        else if (choice == 2)
        {
            int index;
            cout << "Enter the index to get sum: ";
            cin >> index;
            cout << "Sum: " << getSum(BITree, index) << "\n";
        }
        else if (choice == 3)
        {
            cout << "Binary Indexed Tree:\n";
            for (int i = 1; i <= n; i++)
                cout << " " << BITree[i];
            cout << "\n";
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            cout << "Invalid choice\n";
        }
    }

    return 0;
}