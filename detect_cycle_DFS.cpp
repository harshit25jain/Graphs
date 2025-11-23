#include <iostream>
#include <vector>
using namespace std; 

// Function to detect cycle in an undirected graph using DFS

bool CycleDetect(int node, int parent, vector<vector<int>> &adj, vector<bool> &visited) {
    visited[node] = 1;

    for (int j = 0; j < adj[node].size(); j++) {
        if (parent == adj[node][j]) continue;

        if (visited[adj[node][j]]) return 1;

        if (!visited[adj[node][j]]) {
            if (CycleDetect(adj[node][j], node, adj, visited)) return 1;
        }
    }
    return 0;
}

bool isCycle(int V, vector<vector<int>> &adj) {
    vector<bool> visited(V, 0);

    // visited all the unvisited node
    for (int i = 0; i < V; i++) {
        if (!visited[i] && CycleDetect(i, -1, adj, visited)) { 
            return 1;
        }
    }
    return 0;
}

int main() {
    int V = 5;
    vector<vector<int>> adj(V);

    // Example graph with a cycle
    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[4].push_back(3);
    adj[4].push_back(1); // This edge creates a cycle

    if (isCycle(V, adj)) {
        cout << "Graph contains a cycle" << endl;
    } else {
        cout << "Graph does not contain a cycle" << endl;
    }

    return 0;
}
