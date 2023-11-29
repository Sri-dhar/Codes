#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//trying github copilot
//trying github copilot
// Define a structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Define a structure to represent a node in the doubly linked list
struct Node {
    int data;
    Node* prev;
    Node* next;
};

// Define a function to create a new node in the doubly linked list
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Define a function to insert a node at the beginning of the doubly linked list
void insertAtBeginning(Node** headRef, int data) {
    Node* newNode = createNode(data);
    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        newNode->next = *headRef;
        (*headRef)->prev = newNode;
        *headRef = newNode;
    }
}

// Define a function to find the parent of a node in the disjoint set
int findParent(int node, vector<Node*>& disjointSet) {
    Node* curr = disjointSet[node];
    while (curr->prev != NULL) {
        curr = curr->prev;
    }
    return curr->data;
}

// Define a function to merge two disjoint sets
void mergeSets(int node1, int node2, vector<Node*>& disjointSet) {
    int parent1 = findParent(node1, disjointSet);
    int parent2 = findParent(node2, disjointSet);
    if (parent1 != parent2) {
        Node* tail1 = disjointSet[parent1];
        Node* tail2 = disjointSet[parent2];
        tail1->next = tail2;
        tail2->prev = tail1;
        disjointSet[parent2] = tail1;
    }
}

// Define a function to compare two edges based on their weights
bool compareEdges(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

// Define a function to implement Kruskal's algorithm using a doubly linked list
void kruskal(vector<Edge>& edges, int numVertices) {
    // Sort the edges in non-decreasing order of their weights
    sort(edges.begin(), edges.end(), compareEdges);

    // Initialize the disjoint set
    vector<Node*> disjointSet(numVertices);
    for (int i = 0; i < numVertices; i++) {
        disjointSet[i] = createNode(i);
    }

    // Initialize the minimum spanning tree
    vector<Edge> mst;

    // Iterate over the sorted edges and add them to the minimum spanning tree if they do not form a cycle
    for (int i = 0; i < edges.size(); i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;
        int weight = edges[i].weight;
        if (findParent(src, disjointSet) != findParent(dest, disjointSet)) {
            mst.push_back(edges[i]);
            mergeSets(src, dest, disjointSet);
        }
    }

    // Print the minimum spanning tree
    cout << "Minimum Spanning Tree:" << endl;
    for (int i = 0; i < mst.size(); i++) {
        cout << mst[i].src << " -- " << mst[i].dest << " : " << mst[i].weight << endl;
    }
}

// Driver code
int main() {
    // Create a graph with 4 vertices and 5 edges
    int numVertices = 4;
    vector<Edge> edges = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};

    // Find the minimum spanning tree using Kruskal's algorithm
    kruskal(edges, numVertices);

    return 0;
}

