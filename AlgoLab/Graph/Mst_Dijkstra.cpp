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

    bool operator>(const Edge &other) const
    {
        return weight > other.weight;
    }
};

void MSTprims(const vector<list<pair<int, int>>> &adjList)
{
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    vector<bool> visited(adjList.size(), false);
    visited[0] = true;

    for (auto &edge : adjList[0])
    {
        Edge e;
        e.u = 0;
        e.v = edge.first;
        e.weight = edge.second;
        pq.push(e);
    }

    vector<Edge> MSTedges;

    while (!pq.empty())
    {
        Edge currentEdge = pq.top();
        pq.pop();

        int u = currentEdge.v;
        if (visited[u]) continue;

        visited[u] = true;
        MSTedges.push_back(currentEdge);

        for (auto &edge : adjList[u])
        {
            int v = edge.first;
            int weight = edge.second;
            if (!visited[v])
            {
                Edge e;
                e.u = u;
                e.v = v;
                e.weight = weight;
                pq.push(e);
                //if we want to write code as per the given algo
                //we can do it in less time using the following
                // struct Edge {
                //     int u, v, weight;
                //     bool deleted; // Flag to mark if the edge is deleted
                // };                
            }
        }
    }

    cout << "Minimum Spanning Tree Edges Using Prims Algorithm:" << endl;
    for (const auto &edge : MSTedges)
    {
        cout << edge.u << " - " << edge.v << " with weight: " << edge.weight <<endl;
    }
}

int findParent(int node, vector<int>& parent) {
    if (parent[node] == -1) return node;
    return findParent(parent[node], parent);
}

void MSTkruskal(const vector<list<pair<int, int>>> &adjList) {
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    
    vector<int> nodeParent(adjList.size(), -1);

    for (int u = 0; u < adjList.size(); ++u) {
        for (const auto& edge : adjList[u]) {
            Edge e;
            e.u = u;
            e.v = edge.first;
            e.weight = edge.second;
            pq.push(e);
        }
    }

    vector<Edge> MSTedges;

    while (!pq.empty()) {
        Edge currentEdge = pq.top();
        pq.pop();
        int u = currentEdge.u;
        int v = currentEdge.v;
        int weight = currentEdge.weight;

        int parentU = findParent(u, nodeParent);
        int parentV = findParent(v, nodeParent);

        if (parentU != parentV) {
            MSTedges.push_back(currentEdge);
            nodeParent[parentU] = parentV;
        }
    }

    cout << "Minimum Spanning Tree Edges Using Kruskal Algorithm:" << endl;
    for (const auto& edge : MSTedges) {
        cout << edge.u << " - " << edge.v << " with weight: " << edge.weight << endl;
    }
}

void Dijkstra(const vector<list<pair<int, int>>> &adjList)

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
    MSTprims(adjList);
    cout << endl;
    cout << endl;
    MSTkruskal(adjList);
    cout<<endl;

    return 0;
}
// 7
// 2
// 2 1 4 2
// 2 
// 2 7 3 1
// 1
// 4 6
// 2 
// 4 5 5 2
// 1 
// 6 4
// 1
// 6 3
// 0 testcase