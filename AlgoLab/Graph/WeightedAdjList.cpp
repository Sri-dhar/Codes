#include <bits/stdc++.h>

using namespace std;

void printList(const vector<list<pair<int, int>>> &adjList)
{
    cout << "Your Adjacenct List is : " << endl;
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
    cout << endl;
}

struct Edge
{
    int u, v, weight;
};

void betterPrims(const vector<list<pair<int, int>>> &adjList)
{
    int numNodes = adjList.size();
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    vector<Edge> MSTedges;

    pq.push({0, 0, 0});
    vector<bool> isInMST(numNodes, false);

    while (!pq.empty() && MSTedges.size() < numNodes - 1)
    {
        Edge edge = pq.top();
        pq.pop();
        int u = edge.u;
        int v = edge.v;
        int weight = edge.weight;

        if (isInMST[v])
        {
            continue;
        }

        MSTedges.push_back({u, v, weight});
        isInMST[v] = true;

        for (auto &neighbor : adjList[v])
        {
            int node = neighbor.first;
            int edgeWeight = neighbor.second;
            if (!isInMST[node])
            {
                pq.push({v, node, edgeWeight});
            }
        }
    }

    for (const auto &edge : MSTedges)
    {
        cout << "Edge: " << edge.u << " - " << edge.v << " Weight: " << edge.weight << endl;
    }
}

void findMSTprims2(const vector<list<pair<int, int>>> &adjList)
{
    vector<pair<int, pair<int, int>>> vec;

    for (int i = 0; i < adjList.size(); i++)
    {
        for (auto &edge : adjList[i])
        {
            int node = edge.first;
            int weight = edge.second;
            vec.push_back(make_pair(weight, make_pair(i, node)));
        }
    }

    sort(vec.begin(), vec.end());

    vector<bool> isInMST(adjList.size(), false);
    int MSTweight = 0;
    vector<Edge> MSTedges;

    while (vec.size() > 0)
    {
        pair<int, pair<int, int>> edge = vec[0];
        vec.erase(vec.begin());

        int u = edge.second.first;
        int v = edge.second.second;
        int weight = edge.first;

        if (!isInMST[u] || !isInMST[v])
        {
            MSTweight += weight;
            isInMST[u] = true;
            isInMST[v] = true;
            MSTedges.push_back({u, v, weight});
        }
    }

    cout << "Edges of Minimum Spanning Tree: " << endl;
    for (const auto &edge : MSTedges)
    {
        cout << "Edge: " << edge.u << " - " << edge.v << " Weight: " << edge.weight << endl;
    }
}

void findMSTprims(const vector<list<pair<int, int>>> &adjList)
{
    map<int, pair<int, int>> mp; // map contains the pair and their weights
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
        greater<std::pair<int, std::pair<int, int>>>>
        minHeap;

    for (auto &pair : mp)
    {
        int weight = pair.first;
        int node1 = pair.second.first;
        int node2 = pair.second.second;
        minHeap.push(make_pair(weight, make_pair(node1, node2)));
    } // all elements of the map are now in the tree

    vector<pair<int, std::pair<int, int>>> tree;

    tree.push_back(minHeap.top());
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
    findMSTprims2(adjList);

    return 0;
}
