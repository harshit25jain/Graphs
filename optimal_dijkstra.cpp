#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

/*
    Why Priority Queue Dijkstra?
    ----------------------------------
    - The normal Dijkstra scans all nodes linearly => O(V²)
    - Using a min-heap (priority queue) ensures:
        → We ALWAYS pick the next vertex with minimum distance
        → Done in O(log V)
    - Final time complexity becomes:  O(E log V)
    - This is the most efficient and most asked version.

    How it works:
    ----------------------------------
    - dist[] array stores shortest distances
    - Min-heap stores {distance, node}
    - Push {0, source} into heap
    - Pop the node with smallest distance
    - Relax all its edges
    - If a shorter path is found → update dist[] → push new pair in heap
*/


// ------------------ Min-Heap Dijkstra ------------------
vector<int> dijkstraPQ(int V, vector<vector<vector<int>>>& adj, int S) {

    vector<int> dist(V, INT_MAX);
    dist[S] = 0;

    // Min-heap storing {distance, node}
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    pq.push({0, S});

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int distance = top[0];
        int node = top[1];

        // Skip if it's an outdated entry
        if (distance != dist[node]) continue;

        for (auto &edge : adj[node]) {
            int neighbour = edge[0];
            int weight    = edge[1];

            if (dist[node] + weight < dist[neighbour]) {
                dist[neighbour] = dist[node] + weight;
                pq.push({dist[neighbour], neighbour});
            }
        }
    }

    return dist;
}


int main() {
    int V = 5;
    vector<vector<vector<int>>> adj(V);

    // Example graph represented as {node, weight}
    adj[0].push_back({1, 10});
    adj[0].push_back({2, 3});
    adj[1].push_back({2, 1});
    adj[1].push_back({3, 2});
    adj[2].push_back({1, 4});
    adj[2].push_back({3, 8});
    adj[2].push_back({4, 2});
    adj[3].push_back({4, 7});
    adj[4].push_back({3, 9});

    int S = 0;

    vector<int> distances = dijkstraPQ(V, adj, S);

    cout << "Vertex\tDistance from Source " << S << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "\t\t" << (distances[i] == INT_MAX ? -1 : distances[i]) << endl;
    }

    return 0;
}


/*

Graph:
0 -> (1,10), (2,3)
1 -> (2,1), (3,2)
2 -> (1,4), (3,8), (4,2)
3 -> (4,7)
4 -> (3,9)

Initial:
dist = [0, INF, INF, INF, INF]
pq   = { (0,0) }

Step 1:
Pop (0,0)
Relax edges:
  dist[1] = 10
  dist[2] = 3
pq = {(3,2),(10,1)}

Step 2:
Pop (3,2)
Relax edges:
  dist[1] = min(10, 3+4)=7
  dist[3] = 11
  dist[4] = 5
pq = {(5,4),(7,1),(11,3),(10,1 old)}

Step 3:
Pop (5,4)
Relax:
  dist[3] = min(11, 5+9)=11 (no change)
pq = {(7,1),(11,3),(10,1 old)}

Step 4:
Pop (7,1)
Relax:
  dist[2] = min(3,7+1)=3  (no change)
  dist[3] = min(11,7+2)=9  (updated)
pq = {(9,3),(11,3 old),(10,1 old)}

Step 5:
Pop (9,3)
Relax:
  dist[4] = min(5,9+7)=5 (no change)
pq now empty → stop

Final shortest distances:
0 → 0
1 → 7
2 → 3
3 → 9
4 → 5

------------------------------------------------------------
EXPECTED OUTPUT
Vertex   Distance
0        0
1        7
2        3
3        9
4        5
------------------------------------------------------------
*/
