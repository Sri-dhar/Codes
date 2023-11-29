#include <bits/stdc++.h>
using namespace std;

void addEdge(vector<list<pair<int, int>>> &adjList, int u, int v, int w)
{
    adjList[u].push_back(make_pair(v, w));
    adjList[v].push_back(make_pair(u, w));
}

vector<int> Dijkstra(vector<list<pair<int, int>>> &adjList, int V, int start)
{
    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push(make_pair(0, start));

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        visited[u] = true;

        for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
        {
            int v = i->first;
            int weight = i->second;

            if (!visited[v] && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

int main()
{
    cout << "Enter the number of nodes : " << endl;
    int n{};
    cin >> n;
    vector<list<pair<int, int>>> adjList(n);
    cout << "Enter the number of edges: " << endl;
    int m{};
    cin >> m;
    cout << "INPUT Format : \"Node1 Node2 Weight\"";
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(adjList, u, v, w);
    }
    cout << "Enter your location and your friend's location: " << endl;
    cout << "Using Node number (Range: 0 to n-1)" << endl;
    int yourLoc, friLoc;
    cin >> yourLoc >> friLoc;

    vector<int> YourLocVec = Dijkstra(adjList, n, yourLoc);
    vector<int> FriLocVec = Dijkstra(adjList, n, friLoc);

    vector<pair<int, int>> YourLocVecc;
    for (int i = 0; i < YourLocVec.size(); i++)
    {
        YourLocVecc.push_back(make_pair(YourLocVec[i], i));
    }

    vector<pair<int, int>> YourFriVecc;
    for (int i = 0; i < FriLocVec.size(); i++)
    {
        YourFriVecc.push_back(make_pair(FriLocVec[i], i));
    }
    sort(YourFriVecc.begin(), YourFriVecc.end());
    sort(YourLocVecc.begin(), YourLocVecc.end());

    vector<int> temp;

    for (int i = 0; i < min(YourLocVec.size(), FriLocVec.size()); i++)
    {
        if (YourLocVec[i] == FriLocVec[i])
        {
            temp.push_back(i);
        }
    }
    sort(temp.begin(), temp.end());
    if (!temp.empty())
        cout << "\n\nNODE "
             << temp[0] << " is the answer."<<endl;

    if(temp.empty()) cout<<"No P exists for which distance from both the friends is equal"<<endl;

    // cout<<"jhgas;zofhao;dj"<<endl;
    // int flag = 0;
    // int i{},j{};
    // while(i<YourLocVec.size() && j<FriLocVec.size())
    // {
    // 	if(YourLocVecc[i] == YourFriVecc[j]) {
    // 		cout<<"Desired P is "<<YourLocVecc[i].second;
    // 		flag = 1;
    //         break;
    // 	}
    // 	else if(YourLocVecc[i] > YourFriVecc[j])
    // 	{
    // 		i++;
    // 		flag = 1;
    // 	}
    // 	else{
    // 		j++;
    // 		flag = 1;
    // 	}
    // }
    // if(flag == 0)
    // {
    // 	cout<<"No such location is found where Distance from both the friends is same"<<endl;
    // }
}