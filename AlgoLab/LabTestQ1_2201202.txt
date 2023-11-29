#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<climits>
#include<list>

using namespace std;

void addEdge(vector<list<pair<int, int>>> &adjList, int u, int v, int w)
{
    adjList[u].push_back(make_pair(v, w));
}

void DFSHELPER(vector<list<pair<int, int>>> &adjList, vector<bool> &visited, int u)
{
    visited[u] = true;

    for (auto i = adjList[u].begin(); i != adjList[u].end(); i++)
    {
        int v = i->first;
        if (!visited[v])
        {
            DFSHELPER(adjList, visited, v);
        }
    }
}

vector<bool> DFS(vector<list<pair<int, int>>> &adjList, int V, int start)
{
    vector<bool> visited(V, false);
    DFSHELPER(adjList, visited, start);
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