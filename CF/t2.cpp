class Solution
{
public:
    int minimumDiameterAfterMerge(vector<vector<int>> &edges1, vector<vector<int>> &edges2)
    {
        int n1 = edges1.size() + 1;
        int n2 = edges2.size() + 1;

        vector<vector<int>> adj1(n1);
        vector<vector<int>> adj2(n2);

        for (const auto &edge : edges1)
        {
            adj1[edge[0]].push_back(edge[1]);
            adj1[edge[1]].push_back(edge[0]);
        }

        for (const auto &edge : edges2)
        {
            adj2[edge[0]].push_back(edge[1]);
            adj2[edge[1]].push_back(edge[0]);
        }

        pair<int, int> bfsFarthestNode(const vector<vector<int>> &adj, int start)
        {
            vector<int> distance(adj.size(), INT_MAX);
            queue<int> q;

            distance[start] = 0;
            q.push(start);

            int farthestNode = start;
            int maxDistance = 0;

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                for (int neighbor : adj[node])
                {
                    if (distance[neighbor] == INT_MAX)
                    {
                        distance[neighbor] = distance[node] + 1;
                        if (distance[neighbor] > maxDistance)
                        {
                            maxDistance = distance[neighbor];
                            farthestNode = neighbor;
                        }
                        q.push(neighbor);
                    }
                }
            }

            return {farthestNode, maxDistance};
        }

        int findMinAvgDistanceNode(const vector<vector<int>> &adj)
        {
            int n = adj.size();
            int minAvgDistance = INT_MAX;
            int minAvgNode = -1;

            for (int i = 0; i < n; ++i)
            {
                vector<int> distance(n, INT_MAX);
                queue<int> q;
                distance[i] = 0;
                q.push(i);

                int sumDistance = 0;
                int visited = 0;

                while (!q.empty())
                {
                    int node = q.front();
                    q.pop();
                    visited++;
                    sumDistance += distance[node];

                    for (int neighbor : adj[node])
                    {
                        if (distance[neighbor] == INT_MAX)
                        {
                            distance[neighbor] = distance[node] + 1;
                            q.push(neighbor);
                        }
                    }
                }

                int avgDistance = sumDistance / (n - 1);

                if (avgDistance < minAvgDistance)
                {
                    minAvgDistance = avgDistance;
                    minAvgNode = i;
                }
            }

            return minAvgNode;
        }

        int minimumDiameter()
        {
            int minAvgNode1 = findMinAvgDistanceNode(adj1);
            int minAvgNode2 = findMinAvgDistanceNode(adj2);

            adj1[minAvgNode1].push_back(n1 + minAvgNode2);
            adj1[n1 + minAvgNode2].push_back(minAvgNode1);

            pair<int, int> farthestFromStart = bfsFarthestNode(adj1, minAvgNode1);
            pair<int, int> farthestFromFarthest = bfsFarthestNode(adj1, farthestFromStart.first);

            return farthestFromFarthest.second;
        }
    };
