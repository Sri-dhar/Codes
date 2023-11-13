#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <queue>

using namespace std;

void addEdge(vector<list<pair<int, int>>>& adjList, int u, int v, int w) {
    adjList[u].push_back(make_pair(v, w));
    adjList[v].push_back(make_pair(u, w));
}

void BFS(vector<list<pair<int, int>>>& adjList, int V, int start) {
    vector<bool> visited(V, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++) {
            int v = i->first;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

// DFS traversal of the graph
void DFSUtil(vector<list<pair<int, int>>>& adjList, vector<bool>& visited, int u) {
    visited[u] = true;
    cout << u << " ";

    for (auto i = adjList[u].begin(); i != adjList[u].end(); i++) {
        int v = i->first;
        if (!visited[v]) {
            DFSUtil(adjList, visited, v);
        }
    }
}

void DFS(vector<list<pair<int, int>>>& adjList, int V, int start) {
    vector<bool> visited(V, false);
    DFSUtil(adjList, visited, start);
}

bool hasCycle(vector<list<pair<int, int>>>& adjList, vector<bool>& visited, int u, int parent) {

    //u is starting node
    visited[u] = true;

    for (auto i = adjList[u].begin(); i != adjList[u].end(); i++) {
        int v = i->first;
        if (!visited[v]) {
            if (hasCycle(adjList, visited, v, u)) {
                return true;
            }
        } else if (v != parent) {
            return true;
        }
    }

    return false;
}

void PrimsMinimumSpanningTree(vector<list<pair<int, int>>>& adjList, int V) {
    vector<bool> visited(V, false);
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);

    key[0] = 0;

    for (int i = 0; i < V - 1; i++) {
        int u = -1;
        int min = INT_MAX;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        visited[u] = true;

        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++) {
            int v = i->first;
            int weight = i->second;
            if (!visited[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < V; i++) {
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
        parent = new int[n+1];
        rnk = new int[n+1];

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

void KruskalMinimumSpanningTree(vector<list<pair<int, int>>>& adjList, int V) {
    vector<pair<int, pair<int, int>>> edges;
    DisjointSets ds(V);

    for (int u = 0; u < V; u++) {
        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++) {
            int v = i->first;
            int weight = i->second;
            edges.push_back(make_pair(weight, make_pair(u, v)));
        }
    }

    sort(edges.begin(), edges.end());

    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].second.first;
        int v = edges[i].second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v) {
            cout << u << " - " << v << endl;
            ds.merge(set_u, set_v);
        }
    }
}

vector<int> DijkstraShortestDistanceOfAllNodesFromSource(vector<list<pair<int, int>>>& adjList, int V, int start) {
    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        visited[u] = true;

        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++) {
            int v = i->first;
            int weight = i->second;

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}


int main() {
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

    if (cycle) {
        cout << "Graph contains cycle" << endl;
    } else {
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
