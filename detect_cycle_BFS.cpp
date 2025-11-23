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
/*
--------------------- DRY RUN (BFS) ---------------------

Graph adjacency:
0: [1]
1: [0, 2]
2: [1, 3]
3: [2, 4]
4: [3, 1]   <-- this 4->1 edge will create the cycle

Initial:
visited = [0, 0, 0, 0, 0]
queue = empty

Start BFS (the code begins from node 0):
visited[0] = 1
push (0, -1)
queue: [(0, -1)]

Iteration 1:
 pop (0, -1)
 neighbors of 0: [1]
  neighbor = 1
   parent = -1 -> not equal, continue
   visited[1] == 0 -> not visited
   mark visited[1] = 1
   push (1, 0)
 queue: [(1, 0)]
 visited: [1,1,0,0,0]

Iteration 2:
 pop (1, 0)
 neighbors of 1: [0,2]
  neighbor = 0
   parent == 0 -> skip (this is the edge back to parent)
  neighbor = 2
   parent != 2
   visited[2] == 0 -> mark visited[2] = 1
   push (2, 1)
 queue: [(2, 1)]
 visited: [1,1,1,0,0]

Iteration 3:
 pop (2, 1)
 neighbors of 2: [1,3]
  neighbor = 1
   parent == 1 -> skip
  neighbor = 3
   visited[3] == 0 -> mark visited[3] = 1
   push (3, 2)
 queue: [(3, 2)]
 visited: [1,1,1,1,0]

Iteration 4:
 pop (3, 2)
 neighbors of 3: [2,4]
  neighbor = 2
   parent == 2 -> skip
  neighbor = 4
   visited[4] == 0 -> mark visited[4] = 1
   push (4, 3)
 queue: [(4, 3)]
 visited: [1,1,1,1,1]

Iteration 5:
 pop (4, 3)
 neighbors of 4: [3,1]
  neighbor = 3
   parent == 3 -> skip
  neighbor = 1
   parent != 1
   visited[1] == 1 AND not parent -> **cycle detected**
   BFS returns true immediately

Propagation:
 isCycle receives true -> main prints "Graph contains a cycle"

Complexity reminder:
 - Time: O(V + E) since BFS touches each vertex and edge once (edges may be checked twice in undirected graph)
 - Space: O(V) for visited[] and the BFS queue

Notes:
 - This implementation starts BFS only from node 0. For disconnected graphs, you'd need to loop over all vertices and start BFS from any unvisited vertex.
 - The core cycle check is: if neighbor is visited and neighbor != parent -> cycle.
-------------------------------------------------------
*/
