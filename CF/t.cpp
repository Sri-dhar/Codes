#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

vector<int> cacheContents(vector<vector<int>> calllogs) {
    sort(calllogs.begin(), calllogs.end());
    
    map<int, int> priority;  
    map<int, bool> inCache;  
    
    map<pair<int, int>, int> accessCount;
    for (const auto& log : calllogs) {
        int timestamp = log[0];
        int item_id = log[1];
        accessCount[{timestamp, item_id}]++;
    }
    
    int lastTime = calllogs.back()[0];
    
    set<int> items;
    for (const auto& log : calllogs) {
        items.insert(log[1]);
    }
    
    for (int time = 1; time <= lastTime; time++) {
        for (int item : items) {
            if (priority.find(item) == priority.end()) {
                priority[item] = 0;
            }
            
            if (accessCount.find({time, item}) != accessCount.end()) {
                priority[item] += 2 * accessCount[{time, item}];
            } else {
                priority[item] = max(0, priority[item] - 1);
            }
            
            if (priority[item] > 5) {
                inCache[item] = true;
            } else if (priority[item] <= 3) {
                inCache[item] = false;
            }
            
        }
    }
    
    vector<int> result;
    for (const auto& item : items) {
        if (inCache[item]) {
            result.push_back(item);
        }
    }
    
    if (result.empty()) {
        return {-1};
    }
    
    sort(result.begin(), result.end());
    return result;
}

int main() {
    // Test case from the problem
    vector<vector<int>> logs = {
        {1, 1},
        {2, 1},
        {3, 1},
        {4, 2},
        {5, 2},
        {6, 2}
    };
    
    cout << "Processing cache simulation with the following logs:" << endl;
    for (const auto& log : logs) {
        cout << "Time: " << log[0] << ", Item: " << log[1] << endl;
    }
    cout << "\nSimulation results:" << endl;
    
    vector<int> result = cacheContents(logs);
    
    cout << "\nFinal cache contents: ";
    if (result[0] == -1) {  
        cout << "Cache is empty" << endl;
    } else {
        for (int item : result) {
            cout << item << " ";
        }
        cout << endl;
    }           
    
    return 0;
}