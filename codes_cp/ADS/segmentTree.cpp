#include<bits/stdc++.h>
using namespace std;

int segTreeBuilder(vector<int>& tree, vector<int>& arr, int ss, int se, int si)
{
    if(ss == se) 
    {
        tree[si] = arr[ss];
        return arr[ss];
    }

    int mid = (ss + se) / 2;

    tree[si] = segTreeBuilder(tree, arr, ss, mid, 2*si+1) + segTreeBuilder(tree, arr, mid+1, se, 2*si+2);
    return tree[si];
}

int getSumRec(vector<int>& tree, vector<int>& arr, int qs, int qe, int ss, int se, int si)
{
    if( se < qs || ss > qe ) return 0;
    if( qs <= ss && qe >= se ) return tree[si];
    int mid = (ss + se) / 2;

    return getSumRec(tree, arr, qs, qe, ss, mid, 2*si+1) + getSumRec(tree, arr, qs, qe, mid+1, se, 2*si+2);
}

void updateQuery(vector<int>& tree, vector<int>& arr, int ss, int se, int i, int si, int diff)
{
    if(i < ss || i > se) return;
    tree[si] = tree[si] + diff;
    if(se > ss)
    {
        int mid = (ss+se)/2;
        updateQuery(tree, arr, ss, mid, i, 2*si+1, diff);
        updateQuery(tree, arr, mid+1, se, i, 2*si+2, diff);
    }
}

int main()
{
    cout << "Size : ";
    int n;
    cout << endl;
    cin >> n;
    vector<int> arr(n);
    vector<int> tree(2*n-1); 
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    segTreeBuilder(tree, arr, 0, n-1, 0);

    for(int i = 0; i < 2*n-1; i++) 
    {
        cout << tree[i] << endl;
    }

    int qs, qe;
    cin >> qs >> qe;
    int sum = getSumRec(tree, arr, qs, qe, 0, n-1, 0);
    cout << "\nThe sum is " << sum;

    int index, newValue;
    cout << "\nEnter index and new value to update: ";
    cin >> index >> newValue;
    int diff = newValue - arr[index];
    updateQuery(tree, arr, 0, n-1, index, 0, diff);

    cout<<"\n\nThe updated Tree is : "<<endl;
    for(int i = 0; i < 2*n-1; i++) 
    {
        cout << tree[i] << endl;
    }

    return 0;
}
