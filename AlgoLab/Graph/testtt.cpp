#include <bits/stdc++.h>
using namespace std;

bool dfs(vector<vector<int>>& graph, vector<bool>& visited, int node, int parent) {
    visited[node] = true;
    for (int i = 0; i < graph[node].size(); i++) {
        int neighbor = graph[node][i];
        if (!visited[neighbor]) {
            if (dfs(graph, visited, neighbor, node)) {
                return true;
            }
        } else if (neighbor != parent) {
            return true;
        }
    }
    return false;
}

bool hasCycle(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfs(graph, visited, i, -1)) {
                return true;
            }
        }
    }
    return false;
}

bool bfs(vector<vector<int>>& graph, vector<bool>& visited, int node) {
    queue<pair<int, int>> q;
    q.push({node, -1});
    visited[node] = true;
    while (!q.empty()) {
        int curr = q.front().first;
        int parent = q.front().second;
        q.pop();
        for (int i = 0; i < graph[curr].size(); i++) {
            int neighbor = graph[curr][i];
            if (!visited[neighbor]) {
                q.push({neighbor, curr});
                visited[neighbor] = true;
            } else if (neighbor != parent) {
                return true;
            }
        }
    }
    return false;
}

bool 

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    if (hasCycle(graph)) {
        cout << "The graph has a cycle." << endl;
    } else {
        cout << "The graph does not have a cycle." << endl;
    }
    return 0;
}
