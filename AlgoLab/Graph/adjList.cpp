#include <bits/stdc++.h>
using namespace std;

bool checkEdge(const vector<pair<int, list<int>>>& adjList, int i, int j)
{
    if (i >= adjList.size()) {
        return false;
    }

    const list<int>& l = adjList[i].second;
    auto it = find(l.begin(), l.end(), j);

    if (it != l.end()) {
        return true;
    } else {
        return false;
    }
}

void addNode(vector<pair<int, list<int>>>& adjList){
    int n = adjList.size();
    adjList.push_back(make_pair(n, list<int>()));
    cout<<"Enter the connected nodes of "<<n<<endl;
    cout<<"Enter -1 to stop : "<<endl;
    while(1)
    {
        int temp ;
        cin>>temp;
        if(temp != -1){
            adjList[n].second.push_back(temp);
            adjList[temp].second.push_back(n);
        }
        else break;
    }
}

void listAllEdge(const vector<pair<int, list<int>>>& adjList){
    for(int i=0; i<adjList.size(); i++){
        cout<<"Edges connected to node "<<i<<" : ";
        for(auto j: adjList[i].second){
            cout<<i<<"-"<<j<<" ";
        }
        cout<<endl;
    }
}

void printAdjList(const vector<pair<int, list<int>>>& adjList){
    for(int i=0; i<adjList.size(); i++){
        cout<<"Node "<<i<<" : ";
        for(auto j: adjList[i].second){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}

void insertEdge(vector<pair<int, list<int>>>& adjList, int i, int j){
    adjList[i].second.push_back(j);
    adjList[j].second.push_back(i);
}

void deleteEdge(vector<pair<int, list<int>>>& adjList, int i, int j){
    adjList[i].second.remove(j);
    adjList[j].second.remove(i);
}

vector<vector<int>> convertListToMatrix(const vector<pair<int, list<int>>>& adjList){
    int n = adjList.size();
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));

    for(int i=0; i<n; i++){
        for(auto j: adjList[i].second){
            adjMatrix[i][j] = 1;
        }
    }

    return adjMatrix;
}

void BFS(const vector<pair<int, list<int>>>& adjList, int startNode) {
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

        for (int neighbor : adjList[current].second) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }

    cout << "\n" << endl;
}

void DFS(const vector<pair<int, list<int>>>& adjList, int startNode) {
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

            for (int neighbor : adjList[current].second) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }

    cout << "\n" << endl;
}

void checkIfConnected(vector<pair<int, list<int>>> &adjList)
{
    int startNode = 0;
    int n = adjList.size();
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int current = q.front();
        cout << current << " ";
        q.pop();

        for (int neighbor : adjList[current].second) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }

    cout << "\n" << endl;
    for(auto i: visited) if(i == false) {
        cout<<"The graph is not connected "<<endl;
        return;
    }
    cout<<"The graph is connected ";
}

void AdvancedDFS(const vector<pair<int, list<int>>>& adjList) {
    cout << "Enter the start node of DFS: ";
    int startNode;
    cin >> startNode;

    int time = 0;
    int n = adjList.size();
    vector<bool> visited(n, false);
    vector<int> inTime(n, 0);
    vector<int> outTime(n, 0);
    stack<int> s;

    s.push(startNode);

    while (!s.empty()) {
        int u = s.top();

        if (!visited[u]) {
            visited[u] = true;
            inTime[u] = ++time;
            cout << "Node " << u << " in  time : " << inTime[u] << endl;
        }

        bool allNeighborsVisited = true;

        for (int v : adjList[u].second) {
            if (!visited[v]) {
                s.push(v);
                allNeighborsVisited = false;
                break;
            }
        }

        if (allNeighborsVisited) {
            s.pop();
            outTime[u] = ++time;
            cout << "Node " << u << " out time : " << outTime[u] << endl;
        }
    }
}

int main() {
    cout << "Enter the number of nodes: ";
    int n;
    cin >> n;
    cout << "\nThe code uses zero-based indexing\n" << endl;

    vector<pair<int, list<int>>> adjList(n);
    for (int i = 0; i < n; i++) {
        adjList[i] = make_pair(i, list<int>());
    }

    for(int i=0; i<adjList.size(); i++)
    {
        cout<<"Enter the connected nodes of "<<i<<endl;
        cout<<"Enter -1 to stop : "<<endl;
        while(1)
        {
            int temp ;
            cin>>temp;
            if(temp != -1){
                adjList[i].second.push_back(temp);
            }
            else break;
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
        cout << "8. Perform Advanced DFS\n";
        cout << "9. Check if graph is connected or not\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listAllEdge(adjList);
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
                AdvancedDFS(adjList); 
                break;
            case 9:
                checkIfConnected(adjList);
                break;
            case 10:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 10);

    return 0;
}
