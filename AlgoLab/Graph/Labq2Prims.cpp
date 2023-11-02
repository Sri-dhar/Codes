#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 1e5 + 5;

vector<pii> adj[MAXN];
bool visited[MAXN];
list<pii> cut;

void prim(int start) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        pii curr = pq.top();
        pq.pop();

        int u = curr.second;
        if (visited[u]) continue;
        visited[u] = true;

        if (curr.first != 0) {
            cut.push_back({u, curr.first});
        }

        for (auto v : adj[u]) {
            if (!visited[v.first]) {
                pq.push({v.second, v.first});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    prim(1);

    int mst_weight = 0;
    for (auto edge : cut) {
        mst_weight += edge.second;
    }

    cout << "MST weight: " << mst_weight << endl;
    cout << "MST edges: ";
    for (auto edge : cut) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    cout << endl;

    return 0;
}
