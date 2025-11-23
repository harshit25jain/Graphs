#include <iostream>
#include <vector>   
#include <queue>
#include <climits>
using namespace std;


//Function to find the sum of weights of edges of the minimum spanning tree.
int spanningTree(int V, vector<vector<pair<int,int>>> &adj)  
{  

    // Min-heap to store {weight, node}
    priority_queue<
        pair<int, pair<int,int>>,
        vector<pair<int, pair<int,int>>>,
        greater<pair<int, pair<int,int>>>
    > pq;

    vector<bool> IsMST(V, 0);
    vector<int> parent(V); 
    int cost = 0;

    // Start from node 0
    pq.push({0, {0,-1}});

    while (!pq.empty()) {
        int wt = pq.top().first;
        int node = pq.top().second.first;
        int par = pq.top().second.second;
        pq.pop();

        if(!IsMST[node]) {
            IsMST[node] = 1;
            cost += wt;
            parent[node] = par;

            for (int j = 0; j < adj[node].size(); j++) {
                if (!IsMST[adj[node][j].first]) {   
                    pq.push({adj[node][j].second, {adj[node][j].first, node}});
                }
            }
        }

    } 
    return cost;
}

int main() {
    int V = 5;

    vector<vector<pair<int,int>>> adj(V);

    // Example graph represented as {node, weight}
    adj[0].push_back({1, 2});
    adj[0].push_back({3, 6});
    adj[1].push_back({0, 2});
    adj[1].push_back({2, 3});
    adj[1].push_back({3, 8});
    adj[1].push_back({4, 5});
    adj[2].push_back({1, 3});
    adj[2].push_back({4, 7});
    adj[3].push_back({0, 6});
    adj[3].push_back({1, 8});
    adj[4].push_back({1, 5});
    adj[4].push_back({2, 7});

    int totalWeight = spanningTree(V, adj);
    cout << "Total weight of MST: " << totalWeight << endl;

    return 0;
}
/*
----------------------- SHORT DRY RUN (Prim using Min-Heap) -----------------------

Graph edges (undirected, given as adjacency lists):
0 -> (1,2), (3,6)
1 -> (0,2), (2,3), (3,8), (4,5)
2 -> (1,3), (4,7)
3 -> (0,6), (1,8)
4 -> (1,5), (2,7)

Start:
pq = { (0, node=0, par=-1) }
IsMST = [0,0,0,0,0]
cost = 0

Step 1:
Pop (0,0,-1)  // pick node 0
IsMST[0]=1, cost += 0 => cost=0
Push neighbors of 0:
  push (2,1,0)
  push (6,3,0)
pq = {(2,1,0), (6,3,0)}

Step 2:
Pop (2,1,0)  // pick node 1 (smallest weight edge to outside tree)
IsMST[1]=1, cost += 2 => cost=2
Push neighbors of 1 (if not in MST):
  (0,2) ignored because IsMST[0]=1
  push (3,2,1)
  push (8,3,1)
  push (5,4,1)
pq now = {(3,2,1), (6,3,0), (8,3,1), (5,4,1)}

Step 3:
Pop (3,2,1)
IsMST[2]=1, cost += 3 => cost=5
Push neighbors of 2:
  (1,3) ignored (IsMST[1]=1)
  push (7,4,2)
pq = {(5,4,1), (6,3,0), (8,3,1), (7,4,2)}

Step 4:
Pop (5,4,1)
IsMST[4]=1, cost += 5 => cost=10
Push neighbors of 4:
  (1,5) ignored
  (2,7) ignored (IsMST[2]=1)
pq = {(6,3,0), (7,4,2), (8,3,1)}

Step 5:
Pop (6,3,0)
IsMST[3]=1, cost += 6 => cost=16
Push neighbors of 3: both neighbors already in MST

pq empty -> finish

Final MST cost = 16

Expected output:
Total weight of MST: 16

Notes:
- The pq stores edges connecting the current MST to outside vertices; we always pop the smallest such edge.
- The algorithm avoids adding a vertex more than once by checking IsMST[node].
------------------------------------------------------------------------------------
*/