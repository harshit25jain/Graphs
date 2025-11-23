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
/*
---------------------------- DRY RUN ----------------------------

Graph:
0: [1]
1: [0, 2]
2: [1, 3]
3: [2, 4]
4: [3, 1]   <-- Edge 4 → 1 creates cycle (1 → 2 → 3 → 4 → 1)

Initial:
visited = [0,0,0,0,0]

Start main loop:
i = 0 → visited[0] = false → call CycleDetect(0, -1)

CycleDetect(0, -1):
    visited[0] = 1
    neighbors: [1]
      j=0 → neighbor = 1
        parent = -1 → ok
        visited[1] = 0 → recurse CycleDetect(1, 0)

CycleDetect(1, 0):
    visited[1] = 1
    neighbors: [0, 2]
      j=0 → neighbor = 0 → parent == 0 → skip
      j=1 → neighbor = 2 → visited[2] = 0 → recurse CycleDetect(2, 1)

CycleDetect(2, 1):
    visited[2] = 1
    neighbors: [1, 3]
      j=0 → neighbor = 1 → parent == 1 → skip
      j=1 → neighbor = 3 → visited[3] = 0 → recurse CycleDetect(3, 2)

CycleDetect(3, 2):
    visited[3] = 1
    neighbors: [2, 4]
      j=0 → neighbor = 2 → parent == 2 → skip
      j=1 → neighbor = 4 → visited[4] = 0 → recurse CycleDetect(4, 3)

CycleDetect(4, 3):
    visited[4] = 1
    neighbors: [3, 1]
      j=0 → neighbor = 3 → parent == 3 → skip
      j=1 → neighbor = 1 → visited[1] = 1 AND parent != 1
               → BACK EDGE FOUND → cycle detected → return 1

This 1 returns all the way up the recursion:
CycleDetect(4,3) → CycleDetect(3,2) → CycleDetect(2,1) → CycleDetect(1,0) → CycleDetect(0,-1)

isCycle returns TRUE

Output:
Graph contains a cycle

---------------------------------------------------------------
*/
