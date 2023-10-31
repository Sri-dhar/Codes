#include <bits/stdc++.h>
using namespace std;

class Edge {
public:
    int src, dest, weight;
    Edge* next;
    Edge* prev;
};

class Graph {
public:
    int V, E;
    Edge* edge;
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
        edge = NULL;
    }
    void addEdge(int src, int dest, int weight);
    void KruskalMST();
};

class Subset {
public:
    int parent;
    int rank;
};

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

void Graph::addEdge(int src, int dest, int weight) {
    Edge* newEdge = new Edge();
    newEdge->src = src;
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = edge;
    newEdge->prev = NULL;
    if (edge != NULL)
        edge->prev = newEdge;
    edge = newEdge;
}

void Graph::KruskalMST() {
    Edge* result = NULL;
    Edge* e = edge;
    Subset* subsets = new Subset[(V * sizeof(Subset))];
    int i = 0;
    while (i < V) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
        i++;
    }
    while (e != NULL) {
        Edge* next_edge = e->next;
        int x = find(subsets, e->src);
        int y = find(subsets, e->dest);
        if (x != y) {
            Union(subsets, x, y);
            e->next = result;
            if (result != NULL)
                result->prev = e;
            result = e;
        }
        e = next_edge;
    }
    while (result != NULL) {
        cout << result->src << " - " << result->dest << " : " << result->weight << endl;
        result = result->prev;
    }
}

int main() {
    int V = 4;
    int E = 5;
    Graph graph(V, E);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 4);
    graph.KruskalMST();
    return 0;
}

