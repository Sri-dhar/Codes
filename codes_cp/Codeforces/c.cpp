#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
string winner;

void dfs(int v, int a, int b, int c) {
    visited[v] = true;

    if (v == a && v != b && v != c) {
        winner = "A";
        return;
    }

    if (v == b && v != a && v != c) {
        winner = "B";
        return;
    }

    if (v == c && v != a && v != b) {
        winner = "C";
        return;
    }

    bool allVisited = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs(u, a, b, c);
            allVisited = false;
        }
    }

    if (allVisited && visited[a] && visited[b] && visited[c]) {
        winner = "DRAW";
    }
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        int a, b, c;
        cin >> a >> b >> c;

        adj.clear();
        adj.resize(N + 1);
        visited.clear();
        visited.resize(N + 1, false);

        for (int i = 0; i < N - 1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        winner = "";

        dfs(a, a, b, c);

        cout << winner << endl;
    }

    return 0;
}
