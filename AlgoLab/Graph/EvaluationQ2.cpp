#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PairOfInt;

class Graph {
    int V;
    list< PairOfInt > *adj;

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void primMST();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<PairOfInt> [V];
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

void Graph::primMST() {
    vector<int> key(V, INT_MAX);
    list<int> parent(V, -1);
    vector<bool> inMST(V, false);

    key[0] = 0;
    parent.push_front(0);

    for (int count = 0; count < V-1; count++) {
        int min = INT_MAX, u;

        for (int v = 0; v < V; v++)
            if (inMST[v] == false && key[v] < min)
                min = key[v], u = v;

        inMST[u] = true;

        for (auto i: adj[u]) {
            int v = i.first;
            int weight = i.second;

            if (inMST[v] == false && key[v] > weight) {
                key[v] = weight;
                auto it = parent.begin();
                advance(it, v);
                *it = u;
            }
        }
    }

    for (int i = 1; i < V; ++i) {
        auto it = parent.begin();
        advance(it, i);
        cout << *it << " <==> " << i << endl;
    }
}

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int v;
    cout << "Enter the number of vertices: ";
    cin >> v;
    Graph g(v);
    cout << "Enter the number of edges: ";
    int e;
    cin >> e;
    list<pair<int, PairOfInt>> edges;
    for(int i=0; i<e; i++)
    {
        cout << "Enter the source, destination and weight of edge " << i+1 << ": ";
        int s, d, w;
        cin >> s >> d >> w;
        edges.push_back(make_pair(w, make_pair(s, d)));
    }

    edges.sort();

    for(auto edge: edges)
    {
        g.addEdge(edge.second.first, edge.second.second, edge.first);
    }
    cout << endl;
    g.primMST();

    return 0;
}