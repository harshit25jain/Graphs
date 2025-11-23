#include <iostream>
#include <vector>
#include <queue>
using namespace std; 

// Function to detect cycle in an undirected graph using BFS

bool BFS( vector<vector<int>> &adj, vector<bool> &visited) {
    visited[0] = 1;

    queue<pair<int, int>> q;
    visited[0] = 1;
    q.push(make_pair(0, -1));

    while(!q.empty()) {
        int node = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (int j = 0; j < adj[node].size(); j++) {
            if (parent == adj[node][j]) continue;

            if (visited[adj[node][j]]) return 1;


            visited[adj[node][j]] = 1;
            q.push(make_pair(adj[node][j], node));
            }
        }
        return 0;
}

bool isCycle(int V, vector<vector<int>> &adj) {
    vector<bool> visited(V, 0);
    return BFS( adj, visited);

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
