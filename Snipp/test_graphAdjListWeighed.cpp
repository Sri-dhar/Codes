int main() {
    int V = 4;
    vector<list<pair<int, int>>> adjList(V);
    adjList[0].push_back({1, 5});
    adjList[0].push_back({3, 10});
    adjList[1].push_back({2, 3});
    adjList[2].push_back({3, 1});

    FloydWarshall(adjList, V);
    return 0;
}