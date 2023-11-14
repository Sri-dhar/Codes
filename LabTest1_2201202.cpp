
//given a dag with n vertices. Find the smallest set of vertices from which all nodes can be visited in V+E time
#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<climits>
#include<list>

using namespace std;

// int dfsCounter{};

void addEdge(vector<list<pair<int, int>>> &adjList, int u, int v, int w)
{
    adjList[u].push_back(make_pair(v, w));
}

void DFSHELPER(vector<list<pair<int, int>>> &adjList, vector<bool> &visited, int u)
{
    visited[u] = true;
    //cout << u << " ";

    for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
    {
        int v = i->first;
        if (!visited[v])
        {
            DFSHELPER(adjList, visited, v);
        }
    }
}

int DFS(vector<list<pair<int, int>>> &adjList, int V, int start)
{
    vector<bool> visited(V, false);
    DFSHELPER(adjList, visited, start);
    int yes{};
    for(int i=0; i<visited.size(); i++) if(visited[i] ==true) yes++;
    return yes;
}

vector<bool> DFSreturnsVisited(vector<list<pair<int, int>>> &adjList, int V, int start)
{
    vector<bool> visited(V, false);
    DFSHELPER(adjList, visited, start);
    int yes{};
    for(int i=0; i<visited.size(); i++) if(visited[i] ==true) yes++;
    return visited;
}

int main()
{
    cout<<"Enter the number of nodes : "<<endl;
    int n{};
    cin>>n;
    vector<list<pair<int,int>>> adjList(n);
    cout<<"Enter the number of edges: "<<endl;
    int m{};
    cin>>m;
    cout<<"INPUT Format : \"HeadNode TailNode\"";
    for(int i=0; i<m; i++)
    {
        int u,v;
        cin>>u>>v;
        addEdge(adjList,u,v,1);
    }

    cout<<endl;
    int res = 0;
    int count;

	// cout<<"The Nodes are: "<<endl;
    // for(int i=0; i<n; i++)
    // {
    // 	count = 0;
    //     int y = DFS(adjList,n,i);
    //     //cout<<"Nodes Traversed : "<<y<<"  N: "<<n<<endl;
    //     if(y == n) 
    //     {
    //     	cout<<"\n\nNode "<<i<<endl;
    //     	count++;
    //     	res = max(res,count);
    //     }
    // }

    // cout<<"\n\nCount ==> "<<res;
    // if(res == 0){
    // 	cout<<"\nWe cannot reach all nodes from one node"<<endl;
    // }
    while(1)
    {
    vector<int> indegreeArr(n,0);
    for(int i=0; i<n; i++)
    {
        for(auto j : adjList[i])
        {
            indegreeArr[j.first]++;
        }
    }
    cout<<"Indegree Array"<<endl;
    for(int i=0; i<indegreeArr.size(); i++)
    {
        cout<<i<<" "<<indegreeArr[i]<<endl;
    }

    int min = INT_MAX;
    int minNode{};
    for(int i=0; i<indegreeArr.size(); i++)
    {
    	if(indegreeArr[i]<min)
    	{
    		min = indegreeArr[i];
    		minNode = i;
    	}
    }

    cout<<"MIN Node = "<<minNode;
    cout<<"Indegree = "<<min;

    vector<bool> DFSReturned = DFS(adjList,n,minNode);
    vector<int> NOTinDFSreturned;
    for(int i=0; i<DFSReturned.size(); i++)
    {
    	if(DFSReturned[i] == false) NOTinDFSreturned.push_back(i);
    }
}

}

