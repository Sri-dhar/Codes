#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <queue>
#include <algorithm>

using namespace std;

void addEdge(vector<list<pair<int, int>>> &adjList, int u, int v, int w)
{
    adjList[u].push_back(make_pair(v, w));
    adjList[v].push_back(make_pair(u, w));
}

void BFS(vector<list<pair<int, int>>> &adjList, int V, int start)
{
    vector<bool> visited(V, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        cout << u << " ";

        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
        {
            int v = i->first;
            if (!visited[v])
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

// DFS traversal of the graph
void DFSUtil(vector<list<pair<int, int>>> &adjList, vector<bool> &visited, int u)
{
    visited[u] = true;
    cout << u << " ";

    for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
    {
        int v = i->first;
        if (!visited[v])
        {
            DFSUtil(adjList, visited, v);
        }
    }
}

void DFS(vector<list<pair<int, int>>> &adjList, int V, int start)
{
    vector<bool> visited(V, false);
    DFSUtil(adjList, visited, start);
}

bool hasCycle(vector<list<pair<int, int>>> &adjList, vector<bool> &visited, int u, int parent)
{

    // u is starting node
    visited[u] = true;

    for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
    {
        int v = i->first;
        if (!visited[v])
        {
            if (hasCycle(adjList, visited, v, u))
            {
                return true;
            }
        }
        else if (v != parent)
        {
            return true;
        }
    }

    return false;
}

void PrimsMinimumSpanningTree(vector<list<pair<int, int>>> &adjList, int V)
{
    vector<bool> visited(V, false);
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);

    key[0] = 0;

    for (int i = 0; i < V - 1; i++)
    {
        int u = -1;
        int min = INT_MAX;

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && key[v] < min)
            {
                min = key[v];
                u = v;
            }
        }

        visited[u] = true;

        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
        {
            int v = i->first;
            int weight = i->second;
            if (!visited[v] && weight < key[v])
            {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < V; i++)
    {
        cout << parent[i] << " - " << i << endl;
    }
}

struct DisjointSets
{
    int *parent, *rnk;
    int n;

    DisjointSets(int n)
    {
        this->n = n;
        parent = new int[n + 1];
        rnk = new int[n + 1];

        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
            parent[i] = i;
        }
    }

    int find(int u)
    {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void merge(int x, int y)
    {
        x = find(x), y = find(y);

        if (rnk[x] > rnk[y])
            parent[y] = x;
        else
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

void KruskalMinimumSpanningTree(vector<list<pair<int, int>>> &adjList, int V)
{
    vector<pair<int, pair<int, int>>> edges;
    DisjointSets ds(V);

    for (int u = 0; u < V; u++)
    {
        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
        {
            int v = i->first;
            int weight = i->second;
            edges.push_back(make_pair(weight, make_pair(u, v)));
        }
    }

    sort(edges.begin(), edges.end());

    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].second.first;
        int v = edges[i].second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v)
        {
            cout << u << " - " << v << endl;
            ds.merge(set_u, set_v);
        }
    }
}

vector<int> DijkstraShortestDistanceOfAllNodesFromSource(vector<list<pair<int, int>>> &adjList, int V, int start)
{
    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push(make_pair(0, start));

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        visited[u] = true;

        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
        {
            int v = i->first;
            int weight = i->second;

            if (!visited[v] && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

vector<int> TopologicalSort(vector<list<pair<int, int>>> &adjList, int V)
{
    vector<int> inDegree(V, 0);
    vector<int> topologicalOrder;
    queue<int> q;

    for (int u = 0; u < V; u++)
    {
        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
        {
            int v = i->first;
            inDegree[v]++;
        }
    }

    for (int u = 0; u < V; u++)
    {
        if (inDegree[u] == 0)
        {
            q.push(u);
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topologicalOrder.push_back(u);

        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
        {
            int v = i->first;
            inDegree[v]--;
            if (inDegree[v] == 0)
            {
                q.push(v);
            }
        }
    }

    return topologicalOrder;
}

///////////////////////////////////////////////////////////

void DFSUtil2(vector<list<pair<int, int>>> &adjList, vector<bool> &visited, vector<int> &finishTime, int &time, int u)
{
    visited[u] = true;

    for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
    {
        int v = i->first;

        if (!visited[v])
        {
            DFSUtil2(adjList, visited, finishTime, time, v);
        }
    }

    finishTime[u] = time++;
}

vector<int> SortByFinishTimeDFS(vector<list<pair<int, int>>> &adjList, int V)
{
    vector<bool> visited(V, false);
    vector<int> finishTime(V, 0);
    vector<int> topologicalOrder;

    int time = 0;

    for (int u = 0; u < V; u++)
    {
        if (!visited[u])
        {
            DFSUtil2(adjList, visited, finishTime, time, u);
        }
    }

    for (int i = 0; i < V; i++)
    {
        topologicalOrder.push_back(i);
    }

    sort(topologicalOrder.begin(), topologicalOrder.end(), [&](int a, int b)
         { return finishTime[a] > finishTime[b]; });

    return topologicalOrder;
}

//////////////////////////////////////////

vector<vector<int>> shortestPathFromAllNodes(vector<list<pair<int, int>>> &adjList, int V)
{
    vector<vector<int>> dist(V, vector<int>(V, INT_MAX));

    for (int u = 0; u < V; u++)
    {
        dist[u][u] = 0;
        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
        {
            int v = i->first;
            int weight = i->second;
            dist[u][v] = weight;
        }
    }

    for (int k = 0; k < V; k++)
    {
        for (int u = 0; u < V; u++)
        {
            for (int v = 0; v < V; v++)
            {
                if (dist[u][k] != INT_MAX && dist[k][v] != INT_MAX && dist[u][k] + dist[k][v] < dist[u][v])
                {
                    dist[u][v] = dist[u][k] + dist[k][v];
                }
            }
        }
    }

    return dist;
}

//////////////////////////////////////////

int KosarajuNoOfStronglyConnectedComponents(vector<list<pair<int, int>>> &adjList, int V)
{
    vector<bool> visited(V, false);
    vector<int> topologicalOrder = SortByFinishTimeDFS(adjList, V);

    vector<list<pair<int, int>>> reverseAdjList(V);

    for (int u = 0; u < V; u++)
    {
        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
        {
            int v = i->first;
            int weight = i->second;
            reverseAdjList[v].push_back(make_pair(u, weight));
        }
    }

    int count = 0;

    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }

    for (int i = 0; i < V; i++)
    {
        int u = topologicalOrder[i];
        if (!visited[u])
        {
            DFSUtil(reverseAdjList, visited, u);
            count++;
        }
    }

    return count;
}
///////////////////////////////////////////

void DFSUtilWithPrint(vector<list<pair<int, int>>>& adjList, vector<bool>& visited, int u) {
    visited[u] = true;
    cout << u << " ";

    for (auto i = adjList[u].begin(); i != adjList[u].end(); i++) {
        int v = i->first;
        if (!visited[v]) {
            DFSUtilWithPrint(adjList, visited, v);
        }
    }
}

int Kosaraju2NoOfStronglyConnectedComponents(vector<list<pair<int, int>>> &adjList, int V)
{
    vector<bool> visited(V, false);
    vector<int> topologicalOrder = SortByFinishTimeDFS(adjList, V);

    vector<list<pair<int, int>>> reverseAdjList(V);

    for (int u = 0; u < V; u++)
    {
        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
        {
            int v = i->first;
            int weight = i->second;
            reverseAdjList[v].push_back(make_pair(u, weight));
        }
    }

    int count = 0;

    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }

    for (int i = 0; i < V; i++)
    {
        int u = topologicalOrder[i];
        if (!visited[u])
        {
            cout << "Strongly Connected Component " << count+1 << ": ";
            DFSUtilWithPrint(reverseAdjList, visited, u);
            cout << endl;
            count++;
        }
    }

    return count;
}

////////////////////////////////////////////////////////////////////////////////////

bool IsBipartite(vector<list<pair<int, int>>> &adjList, vector<int> &color, int u)
{
    color[u] = 1;

    queue<int> q;
    q.push(u);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
        {
            int v = i->first;
            if (color[v] == -1)
            {
                color[v] = 1 - color[u];
                q.push(v);
            }
            else if (color[v] == color[u])
            {
                return false;
            }
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////

bool negativeCycle = false;
//detects negative cycle and finds shortest distance in case of negative cycle
vector<int> bellmanFord(vector<list<pair<int, int>>>& adjList, int V, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (auto edge : adjList[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    for (int u = 0; u < V; u++) {
        for (auto edge : adjList[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                negativeCycle = true;
                // Print the negative cycle if needed
                cout << "Negative Cycle Found!" << endl;
                return dist; // Returning the shortest distance array even if negative cycle found
            }
        }
    }

    negativeCycle = false;
    return dist;
}

////////////////////////////////////////////////////////////////////////////////////

// The Floyd-Warshall algorithm is a dynamic programming algorithm
//  that is used for finding the shortest paths between
//  all pairs of vertices in a weighted graph, 
//  including negative weight edges.

void FloydWarshall(vector<list<pair<int, int>>>& adjList, int V) {
    vector<vector<int>> dist(V, vector<int>(V, INT_MAX));
    //output is a matrix showing the path distance of ith node with jth node
    for (int i = 0; i < V; i++) {
        dist[i][i] = 0;
        for (auto edge : adjList[i]) {
            int j = edge.first;
            int weight = edge.second;
            dist[i][j] = weight;
        }
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    cout << "The shortest path matrix is:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INT_MAX)
                cout << "No Path ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////

int main() {
    int V = 4;
    vector<list<pair<int, int>>> adjList(V);
    adjList[0].push_back({1, 5});
    adjList[0].push_back({3, 10});
    adjList[1].push_back({2, 3});
    adjList[2].push_back({3, 1});

    FloydWarshall(adjList, V);
    return 0;
}

int main2()
{
    int V = 5;
    vector<list<pair<int, int>>> adjList(V);

    addEdge(adjList, 0, 1, 4);
    addEdge(adjList, 0, 2, 1);
    addEdge(adjList, 1, 3, 1);
    addEdge(adjList, 1, 4, 3);
    addEdge(adjList, 2, 1, 2);
    addEdge(adjList, 2, 3, 5);
    addEdge(adjList, 3, 4, 1);

    vector<bool> visited(V, false);
    bool cycle = hasCycle(adjList, visited, 0, -1);

    if (cycle)
    {
        cout << "Graph contains cycle" << endl;
    }
    else
    {
        cout << "Graph does not contain cycle" << endl;
    }

    cout << "BFS traversal starting from vertex 0: ";
    BFS(adjList, V, 0);
    cout << endl;

    cout << "DFS traversal starting from vertex 0: ";
    DFS(adjList, V, 0);
    cout << endl;

    return 0;
}
