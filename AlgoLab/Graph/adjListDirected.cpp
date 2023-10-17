#include <bits/stdc++.h>
using namespace std;

bool checkEdge(const vector<list<int>>& adjList, size_t i, int j) {
    if (i >= adjList.size()) {
        return false;
    }

    const list<int>& l = adjList[i];
    auto it = find(l.begin(), l.end(), j);

    if (it != l.end()) {
        return true;
    } else {
        return false;
    }
}

void addNode(vector<list<int>>& adjList) {
    int n = adjList.size();
    adjList.push_back(list<int>());
    cout << "Enter the connected nodes of " << n << endl;
    cout << "Enter -1 to stop : " << endl;
    while (1) {
        int temp;
        cin >> temp;
        if (temp != -1) {
            adjList[n].push_back(temp);
        } else
            break;
    }
}

void listAllEdges(const vector<list<int>>& adjList) {
    for (long unsigned int i = 0; i < adjList.size(); i++) {
        cout << "Edges connected from node " << i << " : ";
        for (auto j : adjList[i]) {
            cout << i << "->" << j << " ";
        }
        cout << endl;
    }
}

void printAdjList(const vector<list<int>>& adjList) {
    for (long unsigned int i = 0; i < adjList.size(); i++) {
        cout << "Node " << i << " : ";
        for (auto j : adjList[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
}

void insertEdge(vector<list<int>>& adjList, int i, int j) {
    adjList[i].push_back(j);
}

void deleteEdge(vector<list<int>>& adjList, int i, int j) {
    adjList[i].remove(j);
}

vector<vector<int>> convertListToMatrix(const vector<list<int>>& adjList) {
    int n = adjList.size();
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (auto j : adjList[i]) {
            adjMatrix[i][j] = 1;
        }
    }

    return adjMatrix;
}

void BFS(const vector<list<int>>& adjList, int startNode) {
    int n = adjList.size();
    vector<bool> visited(n, false);
    queue<int> q;

    cout << "BFS starting from node " << startNode << ": ";

    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int current = q.front();
        cout << current << " ";
        q.pop();

        for (int neighbor : adjList[current]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }

    cout << "\n"
         << endl;
}

void DFS(const vector<list<int>>& adjList, int startNode) {
    int n = adjList.size();
    vector<bool> visited(n, false);

    cout << "DFS starting from node " << startNode << ": ";
    stack<int> s;
    s.push(startNode);

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        if (!visited[current]) {
            cout << current << " ";
            visited[current] = true;

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }

    cout << "\n"
         << endl;
}

/////////////////////For no. of strongly connected component ///////////////////////////////
// KOSARAJU ALGORITHM

void DFSUtil(const vector<list<int>>& adjList, int startNode, vector<bool>& visited, stack<int>& s) {
    visited[startNode] = true;

    for (int neighbor : adjList[startNode]) {
        if (!visited[neighbor]) {
            DFSUtil(adjList, neighbor, visited, s);
        }
    }

    s.push(startNode);
}

void BFSUtil(const vector<list<int>>& adjList, int startNode, vector<bool>& visited, queue<int>& q) {
    auto n = adjList.size();

    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : adjList[current]) 
        {
            if (!visited[neighbor]) 
            {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

vector<list<int>> Grev(const vector<list<int>>& adjList) {
    int n = adjList.size();
    vector<list<int>> transposedAdjList(n);

    for (int i = 0; i < n; i++) {
        for (int neighbor : adjList[i]) {
            transposedAdjList[neighbor].push_back(i);
        }
    }

    return transposedAdjList;
}

int SCC(const vector<list<int>>& adjList) {

    int n = adjList.size();
    vector<bool> visited(n, false);
    stack<int> s;

    for (int i = 0; i < n; i++) if (!visited[i]) DFSUtil(adjList, i, visited, s);

    vector<list<int>> transposedAdjList = Grev(adjList);
    fill(visited.begin(), visited.end(), false);

    int ans = 0;

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        if (!visited[current]) {
            stack<int> componentStack;
            DFSUtil(transposedAdjList, current, visited, componentStack);
            ans++;
        }
    }

    return ans;
}

int SCCbfs(const vector<list<int>>& adjList)
{
    int n = adjList.size();
    vector<bool> visited(n, false);
    queue<int> q;
    int count{};
    for (int i = 0; i < n; i++) 
        if (!visited[i]) {
            BFSUtil(adjList, i, visited, q);
            count++;
        }
    return count;
}

///////////////////////ENDS HERE////////////////////////////////////////////////////////////

int main() 
{
    cout << "Enter the number of nodes: ";
    int n;
    cin >> n;
    cout << "\nThe code uses zero-based indexing\n"<< endl;

    vector<list<int>> adjList(n);

    for (long unsigned int i = 0; i < adjList.size(); i++) {
        cout << "Enter the connected nodes of " << i << endl;
        cout << "Enter -1 to stop : " << endl;
        while (1) {
            int temp;
            cin >> temp;
            if (temp != -1) {
                adjList[i].push_back(temp);
            } else
                break;
        }
    }

    int choice;
    do {
        cout << "\n\nMenu:\n";
        cout << "1. List all edges\n";
        cout << "2. Insert an edge\n";
        cout << "3. Delete an edge\n";
        cout << "4. Add a new node\n";
        cout << "5. Print adjacency list\n";
        cout << "6. Perform Breadth-First Search (BFS)\n";
        cout << "7. Perform Depth-First Search (DFS)\n";
        cout << "8. No. of SCC \n";
        cout << "9. No. of SCC using BFS\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
            {
            case 1:
                listAllEdges(adjList);
                break;
            case 2:
                int i, j;
                cout << "Enter the nodes to connect: ";
                cin >> i >> j;
                insertEdge(adjList, i, j);
                break;
            case 3:
                cout << "Enter the nodes to disconnect: ";
                cin >> i >> j;
                deleteEdge(adjList, i, j);
                break;
            case 4:
                addNode(adjList);
                break;
            case 5:
                printAdjList(adjList);
                break;
            case 6:
                int startNodeBFS;
                cout << "Enter the starting node for BFS: ";
                cin >> startNodeBFS;
                BFS(adjList, startNodeBFS);
                break;
            case 7:
                int startNodeDFS;
                cout << "Enter the starting node for DFS: ";
                cin >> startNodeDFS;
                DFS(adjList, startNodeDFS);
                break;
            case 8:
                auto tempp = SCCbfs(adjList);
                cout << "The number of strongly connected components (using KOSARAJU algorithm) is: " << tempp << endl;
                break;
            case 9:
            {
                int temp2 = SCCbfs(adjList);
                cout << "The number of strongly connected components (using BFS) is: " << temp2 << endl;
                break;
            }
    } while (choice != 10);

    return 0;
}
