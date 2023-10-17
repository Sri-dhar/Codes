    #include<iostream>
    #include<vector>
    using namespace std;

    int BinarySearch(vector<int> &arr, int low, int high) {
        if (low == high) return arr[low];

        int mid = low + (high - low) /2;

        if (arr[mid] > arr[mid + 1] && arr[mid] > arr[mid - 1]) 
            return arr[mid];

        if(arr[mid+1] < arr[low])
            return BinarySearch(arr, low , mid);
        else 
            return BinarySearch(arr , mid , high);
    }

    int main() {
        vector<int> arr;
        cout << "Enter the values of the array:" << endl;
        cout << "Enter -1 to stop" << endl;
        int t = 0;
        while (1) {
            cin >> t;
            if (t == -1) break;
            arr.push_back(t);
        }

        int a = BinarySearch(arr, 0, arr.size() - 1);

        if (a == -1) {
            cout << "Element not found";
        } else {
            cout << "Maximum element is : " << a;
        }

        return 0;
    }
