#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

class Graph {

    public:
    int n;
    vector<vector<pii>> adj;

    Graph(int nodes) {
        n = nodes;
        adj.resize(n);
    }

    void addEdge(int u, int v, int cost) {
        adj[u].push_back({cost, v});
        adj[v].push_back({cost, u});
    }

    int primMST() {
        vector<bool> visited(n, false);
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        int totalCost = 0;

        pq.push({0, 0});

        while (!pq.empty()) {
            int cost = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) continue;

            visited[u] = true;
            totalCost += cost;

            for (auto edge : adj[u]) {
                int nextCost = edge.first;
                int v = edge.second;
                if (!visited[v]) {
                    pq.push({nextCost, v});
                }
            }
        }

        return totalCost;
    }
};

int main() {
    int n, m;
    cout << "Enter number of offices: ";
    cin >> n;

    cout << "Enter number of connections: ";
    cin >> m;

    Graph g(n);

    cout << "Enter each connection (u v cost):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        g.addEdge(u, v, cost);
    }

    int minCost = g.primMST();
    cout << "Minimum total cost to connect all offices: " << minCost << endl;

    return 0;
}
