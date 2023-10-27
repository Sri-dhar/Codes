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

    bool operator>(const Edge& other) const
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
        if (visited[u])
            continue;

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
            }
        }
    }

    cout << "Minimum Spanning Tree Edges:" << endl;
    for (const auto &edge : MSTedges)
    {
        cout << edge.u << " - " << edge.v << " (weight: " << edge.weight << ")" << endl;
    }
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
    MSTprims(adjList);

    return 0;
}
