#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxRuntime(vector<int>& api_times, int applications) {
    // If number of applications is greater than available APIs,
    // we need to reuse APIs, so we can get maximum runtime
    // by distributing APIs evenly among applications
    
    int total_apis = api_times.size();
    
    // Sort APIs in descending order to optimize distribution
    sort(api_times.begin(), api_times.end(), greater<int>());
    
    // If we have more or equal APIs than applications,
    // we can simply take the M largest API times
    if (total_apis >= applications) {
        return api_times[applications - 1];
    }
    
    // If we have fewer APIs than applications,
    // we need to reuse APIs to cover all applications
    // The maximum runtime will be when we distribute the APIs evenly
    vector<int> assigned_times(applications, 0);
    
    // First, distribute all available APIs
    for (int i = 0; i < total_apis; i++) {
        assigned_times[i] = api_times[i];
    }
    
    // Then, for remaining applications, assign the largest available API times
    for (int i = total_apis; i < applications; i++) {
        int max_api_time = *max_element(api_times.begin(), api_times.end());
        assigned_times[i] = max_api_time;
    }
    
    // The result will be the minimum time among all assigned times
    // as all applications need to run simultaneously
    return *min_element(assigned_times.begin(), assigned_times.end());
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