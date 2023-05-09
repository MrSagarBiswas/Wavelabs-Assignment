#include<iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> pii;

int networkDelayTime(vector<vector<int>> &times, int n, int k)
{
    vector<vector<pii>> graph(n + 1);
    vector<int> dist(n + 1, numeric_limits<int>::max());
    vector<bool> visited(n + 1, false);

    // Build the graph
    for (const auto &time : times)
    {
        int u = time[0], v = time[1], w = time[2];
        graph[u].push_back({v, w});
    }

    // Dijkstra's algorithm
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, k});
    dist[k] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (visited[u])
        {
            continue;
        }
        visited[u] = true;
        for (const auto &neighbor : graph[u])
        {
            int v = neighbor.first, w = neighbor.second;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    // Check if all nodes were reached
    int max_dist = 0;
    for (int i = 1; i <= n; i++)
    {
        if (dist[i] == numeric_limits<int>::max())
        {
            return -1;
        }
        max_dist = max(max_dist, dist[i]);
    }
    return max_dist;
}

int main()
{
    vector<vector<int>> times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n=4, k=2;
    cout<<networkDelayTime(times, n, k)<<endl;
}