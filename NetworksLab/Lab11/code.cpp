#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <string>
#include <iomanip>

using namespace std;

const int INF = numeric_limits<int>::max();

unordered_map<string, int> initializeDistanceVector(const vector<string>& nodes, 
                                                    const unordered_map<string, unordered_map<string, int>>& links, 
                                                    const string& source) {
    unordered_map<string, int> distanceVector;
    for (const string& node : nodes) {
        distanceVector[node] = INF;
    }
    distanceVector[source] = 0;
    if (links.find(source) != links.end()) {
        for (const auto& neighbor : links.at(source)) {
            distanceVector[neighbor.first] = neighbor.second;
        }
    }
    return distanceVector;
}

unordered_map<string, unordered_map<string, int>> exchangeAndUpdate(const vector<string>& nodes, 
                                                                    const unordered_map<string, unordered_map<string, int>>& links, 
                                                                    const unordered_map<string, unordered_map<string, int>>& distanceVectors) {
    unordered_map<string, unordered_map<string, int>> newVectors = distanceVectors;
    for (const string& node : nodes) {
        if (links.find(node) != links.end()) {
            for (const auto& neighbor : links.at(node)) {
                for (const string& target : nodes) {
                    if (distanceVectors.at(node).at(target) < INF && distanceVectors.at(node).at(target) + links.at(node).at(neighbor.first) < newVectors[neighbor.first][target]) {
                        newVectors[neighbor.first][target] = distanceVectors.at(node).at(target) + links.at(node).at(neighbor.first);
                    }
                }
            }
        }
    }
    return newVectors;
}

void printDistanceVector(const string& source, const unordered_map<string, int>& distanceVector) {
    cout << "Distance vector of " << source << ":\n";
    for (const auto& dv : distanceVector) {
        cout << "  " << dv.first << " : " << (dv.second == INF ? "INF" : to_string(dv.second)) << "\n";
    }
    cout << endl;
}

void simulateDistanceVectorProtocol(const vector<string>& nodes, 
                                    const unordered_map<string, unordered_map<string, int>>& links, 
                                    const string& source) {
    unordered_map<string, unordered_map<string, int>> distanceVectors;
    for (const string& node : nodes) {
        distanceVectors[node] = initializeDistanceVector(nodes, links, node);
    }
    
    cout << "Initial ";
    printDistanceVector(source, distanceVectors[source]);
    
    int iterations = 0;
    while (true) {
        auto newVectors = exchangeAndUpdate(nodes, links, distanceVectors);
        
        bool unchanged = true;
        for (const string& node : nodes) {
            if (newVectors[node] != distanceVectors[node]) {
                unchanged = false;
                break;
            }
        }
        
        if (unchanged) break;
        
        distanceVectors = newVectors;
        iterations++;
        
        cout << "After iteration " << iterations << ":\n";
        printDistanceVector(source, distanceVectors[source]);
    }
    
    cout << "Final ";
    printDistanceVector(source, distanceVectors[source]);
}

int main() {
    vector<string> nodes = {"A", "B", "C", "D", "E", "F", "G"};
    
    unordered_map<string, unordered_map<string, int>> links = {
        {"A", {{"B", 1}, {"C", 1}, {"E", 1}, {"F", 1}}},            
        {"B", {{"A", 1}, {"C", 1}}},
        {"C", {{"A", 1}, {"B", 1}, {"D", 1}}},
        {"D", {{"C", 1}, {"G", 1}}},
        {"E", {{"A", 1}}},
        {"F", {{"A", 1}, {"G", 1}}},
        {"G", {{"D", 1}, {"F", 1}}}
    };
    
    simulateDistanceVectorProtocol(nodes, links, "A");
    
    return 0;
}
