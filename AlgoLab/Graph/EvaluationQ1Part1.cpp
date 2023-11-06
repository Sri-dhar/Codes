#include <bits/stdc++.h>
using namespace std;

struct Node {
    int parent;
    int rank;
    int data;
    Node* next;
    Node* prev;
};

unordered_map<int, Node*> m;

void makeSet(int data) {
    Node* node = new Node();
    node->parent = data;
    node->rank = 0;
    node->data = data;
    node->next = nullptr;
    node->prev = nullptr;
    m[data] = node;
}

int findSet(int data) {
    Node* node = m[data];
    if (node->parent == data) {
        return data;
    }
    node->parent = findSet(node->parent);
    return node->parent;
}

void unionSet(int data1, int data2) {
    Node* node1 = m[data1];
    Node* node2 = m[data2];

    int parent1 = findSet(data1);
    int parent2 = findSet(data2);

    if (parent1 == parent2) {
        return;
    }

    if (node1->rank >= node2->rank) {
        node2->parent = parent1;
        if (node1->rank == node2->rank) {
            node1->rank++;
        }
        Node* tail = node1;
        while (tail->next != nullptr) {
            tail = tail->next;
        }
        tail->next = node2;
        node2->prev = tail;
    } else {
        node1->parent = parent2;
        Node* tail = node2;
        while (tail->next != nullptr) {
            tail = tail->next;
        }
        tail->next = node1;
        node1->prev = tail;
    }
}

vector<vector<int>> getSets() {
    vector<vector<int>> sets;
    unordered_map<int, bool> visited;
    for (auto it : m) {
        int data = it.first;
        if (!visited[data]) {
            vector<int> set;
            Node* node = m[data];
            while (node != nullptr) {
                set.push_back(node->data);
                visited[node->data] = true;
                node = node->next;
            }
            sets.push_back(set);
        }
    }
    return sets;
}

struct Edge {
    int src, dest, weight;
};

vector<Edge> edges;
int V;

void addEdge(int src, int dest, int weight) {
    Edge edge = {src, dest, weight};
    edges.push_back(edge);
}

vector<Edge> kruskalMST() {
    vector<Edge> result;

    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    for (int i = 0; i < V; i++) {
        makeSet(i);
    }

    for (auto edge : edges) {
        int src = edge.src;
        int dest = edge.dest;

        int parent1 = findSet(src);
        int parent2 = findSet(dest);

        if (parent1 != parent2) {
            result.push_back(edge);
            unionSet(parent1, parent2);
        }
    }

    return result;
}

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int E;
    cin >> V >> E;

    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        addEdge(src, dest, weight);
    }

    vector<Edge> mst = kruskalMST();
    for (auto edge : mst) {
        cout << edge.src << "<==>" << edge.dest << " Weight : " << edge.weight << endl;
    }

    return 0;
}
