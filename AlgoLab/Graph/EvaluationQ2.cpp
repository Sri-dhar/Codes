#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PairOfInt;

void addEdge(vector<PairOfInt> adj[], int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

void primMST(vector<PairOfInt> adj[], int V) {
    vector<int> key(V, INT_MAX);
    list<int> cuts(V, -1);
    vector<bool> inMST(V, false);

    key[0] = 0;
    cuts.push_front(0);

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
                auto it = cuts.begin();
                advance(it, v);
                *it = u;
            }
        }
    }

    for (int i = 1; i < V; ++i) {
        auto it = cuts.begin();
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
    vector<PairOfInt> adj[v];
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
        addEdge(adj, edge.second.first, edge.second.second, edge.first);
    }
    cout << endl;
    primMST(adj, v);

    return 0;
}

//input
// 4
// 5
// 0 1 2
// 0 2 3
// 1 2 1 
// 1 3 4 
// 2 3 5

//expected output
// Enter the number of vertices: Enter the number of edges: Enter the source, destination and weight of edge 1: Enter the source, destination and weight of edge 2: Enter the source, destination and weight of edge 3: Enter the source, destination and weight of edge 4: Enter the source, destination and weight of edge 5: 
// 0 <==> 1
// 1 <==> 2
// 1 <==> 3
