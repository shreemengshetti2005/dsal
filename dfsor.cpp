#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
using namespace std;

class Graph {
    map<string, vector<pair<string, int>>> adj;
    set<string> cities;

public:
    void addEdge(string from, string to, int weight) {
        adj[from].push_back(make_pair(to, weight));
        cities.insert(from);
        cities.insert(to);
    }

    void display() {
        for (auto it = adj.begin(); it != adj.end(); ++it) {
            cout << it->first << " -> ";
            for (auto p : it->second) {
                cout << "(" << p.first << ", " << p.second << ") ";
            }
            cout << endl;
        }
    }

    void outDegrees() {
        for (auto city : cities) {
            cout << "Out-degree of " << city << ": " << adj[city].size() << endl;
        }
    }

    void inDegrees() {
        map<string, int> indeg;
        for (auto city : cities) indeg[city] = 0;

        for (auto it = adj.begin(); it != adj.end(); ++it) {
            for (auto p : it->second) {
                indeg[p.first]++;
            }
        }

        for (auto city : cities) {
            cout << "In-degree of " << city << ": " << indeg[city] << endl;
        }
    }

    void dfs(string node, map<string, bool> &visited) {
        visited[node] = true;
        for (auto p : adj[node]) {
            if (!visited[p.first])
                dfs(p.first, visited);
        }
    }

    Graph getTranspose() {
        Graph gT;
        for (auto it = adj.begin(); it != adj.end(); ++it) {
            string from = it->first;
            for (auto p : it->second) {
                gT.addEdge(p.first, from, p.second); // reverse direction
            }
        }
        return gT;
    }

    void isConnected() {
        if (cities.empty()) {
            cout << "Graph is empty.\n";
            return;
        }

        string start = *cities.begin();
        map<string, bool> visited;
        for (auto c : cities) visited[c] = false;
        dfs(start, visited);
        for (auto c : cities) {
            if (!visited[c]) {
                cout << "Graph is NOT strongly connected.\n";
                return;
            }
        }

        Graph gt = getTranspose();
        for (auto c : cities) visited[c] = false;
        gt.dfs(start, visited);
        for (auto c : cities) {
            if (!visited[c]) {
                cout << "Graph is NOT strongly connected.\n";
                return;
            }
        }

        cout << "Graph is strongly connected.\n";
    }
};

int main() {
    Graph g;
    g.addEdge("CityA", "CityB", 4);
    g.addEdge("CityB", "CityC", 5);
    g.addEdge("CityC", "CityA", 6);
    g.addEdge("CityA", "CityD", 7);
    g.addEdge("CityD", "CityE", 8);
    g.addEdge("CityE", "CityA", 9);

    cout << "\nGraph:\n";
    g.display();

    cout << "\nIn-degrees:\n";
    g.inDegrees();

    cout << "\nOut-degrees:\n";
    g.outDegrees();

    cout << "\nConnectivity check:\n";
    g.isConnected();

    return 0;
}
