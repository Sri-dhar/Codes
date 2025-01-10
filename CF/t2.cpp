#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxRuntime(vector<int>& api_times, int applications) {
    int n = api_times.size();
    
    if (applications == 1) {
        int sum = 0;
        for (int time : api_times) sum += time;
        return sum;
    }
    
    if (applications >= n) {
        int max_time = 0;
        for (int time : api_times) max_time = max(max_time, time);
        return max_time;
    }
    
    sort(api_times.begin(), api_times.end(), greater<int>());
    
    vector<int> app_times(applications, 0);
    
    for (int api_time : api_times) {
        int min_idx = 0;
        for (int i = 1; i < applications; i++) {
            if (app_times[i] < app_times[min_idx]) {
                min_idx = i;
            }
        }
        app_times[min_idx] += api_time;
    }
    return *max_element(app_times.begin(), app_times.end());
}

int main() {
    int api_size;
    cin >> api_size;
    
    vector<int> api_times(api_size);
    for (int i = 0; i < api_size; i++) {
        cin >> api_times[i];
    }
    
    int applications;
    cin >> applications;
    
    int result = maxRuntime(api_times, applications);
    cout << result << endl;
    
    return 0;
}