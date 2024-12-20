#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int src, dest, weight;
};

struct TreeNode {
    int parent;
    int unionSizeParameter;
};

struct Graph {
    int V, E;
    Edge* edge;
};

Graph* createGraph(int V, int E) {
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

int find(TreeNode tree[], int i) {
    if (tree[i].parent != i)
        tree[i].parent = find(tree, tree[i].parent);

    return tree[i].parent;
}

void Union(TreeNode tree[], int branch1, int branch2) {
    int leftRoot = find(tree, branch1);
    int rightRoot = find(tree, branch2);

    if (tree[leftRoot].unionSizeParameter < tree[rightRoot].unionSizeParameter)
        tree[leftRoot].parent = rightRoot;
    else if (tree[leftRoot].unionSizeParameter > tree[rightRoot].unionSizeParameter)
        tree[rightRoot].parent = leftRoot;
    else {
        tree[rightRoot].parent = leftRoot;
        tree[leftRoot].unionSizeParameter++;
    }
}

bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

void KruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V];
    int e = 0;
    int i = 0;

    sort(graph->edge, graph->edge + graph->E, compareEdges);

    TreeNode tree[V];

    for (int v = 0; v < V; ++v) {
        tree[v].parent = v;
        tree[v].unionSizeParameter = 0;
    }

    while (e < V - 1 && i < graph->E) {
        Edge nextEdge = graph->edge[i++];

        int branch1 = find(tree, nextEdge.src);
        int branch2 = find(tree, nextEdge.dest);

        if (branch1 != branch2) {
            result[e++] = nextEdge;
            Union(tree, branch1, branch2);
        }
    }

    cout << "\n\nMST Edges\n";
    int minimumCost = 0;
    for (i = 0; i < e; ++i) {
        cout << result[i].src << "<==>" << result[i].dest << " Weight: " << result[i].weight << endl;
        minimumCost += result[i].weight;
    }
    cout << "\nMinimum Cost Spanning Tree: " << minimumCost << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int v;
    cout << "Enter the number of vertices: ";
    cin >> v;
    int e;
    cout << "Enter the number of edges: ";
    cin >> e;
    Graph* graph = createGraph(v, e);

    for(int i=0; i<e; i++)
    {
        cout << "Enter the source, destination and weight of edge " << i+1 << ": ";
        int s, d, w;
        cin >> s >> d >> w;
        graph->edge[i].src = s;
        graph->edge[i].dest = d;
        graph->edge[i].weight = w;
    }

    KruskalMST(graph);

    return 0;
}

