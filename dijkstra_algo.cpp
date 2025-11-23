#include <iostream>
#include <vector>
#include <climits>  
using namespace std;

//Function to find shortest distance of all vertices from source S using Dijkstra's algorithm
vector<int> dijkstra(int V, vector<vector<vector<int>>>& adj, int S){
    vector<bool> Explored(V, 0);
    vector<int> dist(V, INT_MAX);
    dist[S] = 0;

    // Select a node which is not explored yet and whose distance value is minimum
    int count = V;
    while (count--) {
        int node = -1, value = INT_MAX;

        for (int i = 0; i < V; i++) {
            if (!Explored[i] && value > dist[i]) {
                node = i;
                value = dist[i];
            }
        }

        if (node == -1) break; // no reachable unexplored node remains
        Explored[node] = 1; // Mark the node as explored

        // Relax the edges from 'node'
        for (int j = 0; j < adj[node].size(); j++) {
            int neighbour = adj[node][j][0]; // Get the adjacent vertex
            int weight = adj[node][j][1];    // Get the weight of the edge

            if (!Explored[neighbour] && dist[node] + weight < dist[neighbour]) {
                dist[neighbour] = dist[node] + weight; // Update the distance if it's shorter
            }
        }
    }

    return dist; 
}

int main() {
    int V = 5; 
    vector<vector<vector<int>>> adj(V);


    // Example graph represented as an adjacency list of {node, weight}
    adj[0].push_back({1, 10});
    adj[0].push_back({2, 3});
    adj[1].push_back({2, 1});
    adj[1].push_back({3, 2});
    adj[2].push_back({1, 4});
    adj[2].push_back({3, 8});
    adj[2].push_back({4, 2});
    adj[3].push_back({4, 7});
    adj[4].push_back({3, 9});

    int S = 0; // Source vertex

    vector<int> distances = dijkstra(V, adj, S);

    cout << "Vertex\tDistance from Source " << S << endl;
    for (int i = 0; i < V; i++)
        cout << i << "\t\t" << (distances[i] == INT_MAX ? -1 : distances[i]) << endl;

    return 0;
}

/*
----------------------- SHORT DRY RUN -----------------------

Graph edges (from adjacency):
0 -> (1,10), (2,3)
1 -> (2,1), (3,2)
2 -> (1,4), (3,8), (4,2)
3 -> (4,7)
4 -> (3,9)

Start:
dist = [0, INF, INF, INF, INF]
Explored = [0,0,0,0,0]

Iteration 1:
- pick node with min dist not explored => node = 0 (dist 0)
- relax edges from 0:
  dist[1] = min(INF, 0 + 10) = 10
  dist[2] = min(INF, 0 + 3)  = 3
dist = [0, 10, 3, INF, INF]
Explored = [1,0,0,0,0]

Iteration 2:
- pick min unexplored => node = 2 (dist 3)
- relax edges from 2:
  dist[1] = min(10, 3 + 4) = 7    (updated via 0->2->1)
  dist[3] = min(INF, 3 + 8) = 11
  dist[4] = min(INF, 3 + 2) = 5
dist = [0, 7, 3, 11, 5]
Explored = [1,0,1,0,0]

Iteration 3:
- pick min unexplored => node = 4 (dist 5)
- relax edges from 4:
  dist[3] = min(11, 5 + 9) = 11  (no change)
dist = [0,7,3,11,5]
Explored = [1,0,1,0,1]

Iteration 4:
- pick min unexplored => node = 1 (dist 7)
- relax edges from 1:
  dist[2] = min(3, 7 + 1) = 3  (no change)
  dist[3] = min(11, 7 + 2) = 9  (updated)
dist = [0,7,3,9,5]
Explored = [1,1,1,0,1]

Iteration 5:
- pick min unexplored => node = 3 (dist 9)
- relax edges from 3:
  dist[4] = min(5, 9 + 7) = 5  (no change)
dist = [0,7,3,9,5]
Explored = [1,1,1,1,1]

Final dist array:
[0, 7, 3, 9, 5]

---------------------- EXPECTED OUTPUT ---------------------
Vertex  Distance from Source 0
0        0
1        7
2        3
3        9
4        5
------------------------------------------------------------
Note: unreachable nodes would show -1 in the printed output above.
*/
