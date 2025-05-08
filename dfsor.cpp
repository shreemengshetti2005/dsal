#include <bits/stdc++.h>
using namespace std;

class Graph {
    unordered_map<string, vector<pair<string, int>>> adj; // city -> list of (neighbor, weight)
    unordered_set<string> cities; // to keep track of all cities

public:
    // Add directed edge from cityA to cityB with weight
    void addEdge(string cityA, string cityB, int weight) {
        adj[cityA].push_back({cityB, weight});
        cities.insert(cityA);
        cities.insert(cityB);
    }

    // Print the adjacency list
    void printGraph() {
        for (auto &[city, neighbors] : adj) {
            cout << city << " -> ";
            for (auto &[neighbor, weight] : neighbors) {
                cout << "(" << neighbor << ", " << weight << ") ";
            }
            cout << endl;
        }
    }

    // Calculate out-degrees
    void printOutDegrees() {
        for (const auto &city : cities) {
            cout << "Out-degree of " << city << ": " << adj[city].size() << endl;
        }
    }

    // Calculate in-degrees
    void printInDegrees() {
        unordered_map<string, int> indegree;
        for (const auto &city : cities) indegree[city] = 0;

        for (const auto &[from, neighbors] : adj) {
            for (const auto &[to, _] : neighbors) {
                indegree[to]++;
            }
        }

        for (const auto &city : cities) {
            cout << "In-degree of " << city << ": " << indegree[city] << endl;
        }
    }

    // DFS utility
    void DFS(string node, unordered_set<string> &visited) {
        visited.insert(node);
        for (const auto &[neighbor, _] : adj[node]) {
            if (!visited.count(neighbor))
                DFS(neighbor, visited);
        }
    }

    // Transpose the graph
    Graph getTranspose() {
        Graph transposed;
        for (const auto &[city, neighbors] : adj) {
            for (const auto &[neighbor, weight] : neighbors) {
                transposed.addEdge(neighbor, city, weight); // reverse the edge
            }
        }
        return transposed;
    }

    // Check if graph is strongly connected
    void isConnected() {
        if (cities.empty()) {
            cout << "Graph is empty." << endl;
            return;
        }

        string start = *cities.begin();

        // DFS from start in original graph
        unordered_set<string> visited;
        DFS(start, visited);
        if (visited.size() != cities.size()) {
            cout << "Graph is NOT strongly connected (original)." << endl;
            return;
        }

        // DFS on transposed graph
        Graph transposed = getTranspose();
        visited.clear();
        transposed.DFS(start, visited);
        if (visited.size() != cities.size()) {
            cout << "Graph is NOT strongly connected (transposed)." << endl;
        } else {
            cout << "Graph is strongly connected." << endl;
        }
    }
};

int main() {
    Graph g;

    // Sample flight connections with weights (time/fuel)
    g.addEdge("CityA", "CityB", 5);
    g.addEdge("CityB", "CityC", 10);
    g.addEdge("CityC", "CityA", 15);
    g.addEdge("CityA", "CityD", 8);
    g.addEdge("CityD", "CityE", 6);
    g.addEdge("CityE", "CityA", 12);

    cout << "Adjacency List:\n";
    g.printGraph();

    cout << "\nOut-degrees:\n";
    g.printOutDegrees();

    cout << "\nIn-degrees:\n";
    g.printInDegrees();

    cout << "\nChecking connectivity:\n";
    g.isConnected();

    return 0;
}
