int binarysearch(vector<int> arr , int target)
{
    int high = arr.size()-1;
    int low = 0;
    while(1)
    {
        int mid = low + (high - low)/2;
        if(arr[mid] == target) return mid ; 
        if(arr[mid] > target) low = mid+1;
        if(arr[mid] < target) high = mid-1;
    }
    return -1;
}