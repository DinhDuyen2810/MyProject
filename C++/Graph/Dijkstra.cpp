#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

typedef pair<int, int> pii; // Pair of (distance, node)

int main() {
    int nodes, edges;
    cin >> nodes >> edges;

    unordered_map<int, vector<pair<int, int>>> graph;
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    int source, target;
    cin >> source >> target;

    vector<int> dist(nodes + 1, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, source});
    dist[source] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto& edge : graph[u]) {
            int v = edge.first, w = edge.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[target] == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << dist[target] << endl;
    }

    return 0;
}
