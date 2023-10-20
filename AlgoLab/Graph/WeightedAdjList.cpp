#include <bits/stdc++.h>

using namespace std;

void printList(const vector<list<pair<int, int>>> &adjList)
{
    int n = adjList.size();
    for (int i = 0; i < n; i++)
    {
        cout << "Node " << i << " is connected to: ";
        for (const auto &edge : adjList[i])
        {
            cout << edge.first << " (weight: " << edge.second << ") ";
        }
        cout << endl;
    }
}

void findMSTprims(const vector<list<pair<int, int>>> &adjList)
{
    map<int,pair<int,int>> mp; // map contains the pair and their weights
    for (int i = 0; i < adjList.size(); i++)
    {
        for (auto &edge : adjList[i])
        {
            int node = edge.first;
            int weight = edge.second;
            mp[weight] = make_pair(i, node);
        }
    }

    /////////FOR PRINTING SORTED WEIGHTED EDGES//////////////
    //
    // for (auto &pair : mp)
    // {
    //     int node1 = pair.second.first;
    //     int node2 = pair.second.second;
    //     int weight = pair.first;
    //     cout << "Edge: " << node1 << " - " << node2 << " Weight: " << weight << endl;
    // }
    priority_queue<
        pair<int, std::pair<int, int>>,  
        vector<std::pair<int, std::pair<int, int>>>,  
        greater<std::pair<int, std::pair<int, int>>>  
    > minHeap;
}

int main()
{
    cout << "Enter the number of nodes: ";
    int n;
    cin >> n;
    cout << "\nThe code uses zero-based indexing\n";
    cout << "Enter an edge only one time\n\n";

    vector<list<pair<int, int>>> adjList(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Enter the number of neighbors for node " << i << ": ";
        int t;
        cin >> t;

        cout << "Enter neighbors and corresponding edge weights for node " << i << " separated by space: ";
        for (int j = 0; j < t; j++)
        {
            int neighbor, weight;
            cin >> neighbor >> weight;
            adjList[i].push_back(make_pair(neighbor, weight));
            adjList[neighbor].push_back(make_pair(i, weight));
        }
    }

    printList(adjList);

    return 0;
}
