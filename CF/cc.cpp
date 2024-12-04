#include <bits/stdc++.h>
using namespace std;
#define ll long long

class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int x) {
        if(parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if(px == py) return;
        
        if(rank[px] < rank[py]) {
            parent[px] = py;
        } else if(rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++; 
        }
    }
};

void solve() {
    int n;
    cin >> n;
    
    vector<ll> x(n), a(n);
    for(int i = 0; i < n; i++) cin >> x[i];
    for(int i = 0; i < n; i++) cin >> a[i];
    
    vector<pair<ll, pair<int,int>>> edges;
    
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            ll dist = abs(x[i] - x[j]);
            ll cost = min(a[i], a[j]) * dist;
            edges.push_back({cost, {i, j}});
        }
    }
    
    sort(edges.begin(), edges.end());
    
    DSU dsu(n);
    ll total_cost = 0;
    int edges_taken = 0;
    
    for(auto &edge : edges) {
        ll cost = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        
        if(dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            total_cost += cost;
            edges_taken++;
            if(edges_taken == n-1) break;
        }
    }
    
    cout << total_cost << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}   