#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional> 
using namespace std;

int FindParent(int u, vector<int>& parent) {
    if (u == parent[u]) {
        return u;
    }
    return parent[u] = FindParent(parent[u], parent);
}

void UnionByRank(int u, int v, vector<int>& parent, vector<int>& rank) {
    int pu = FindParent(u, parent);
    int pv = FindParent(v, parent);

    if (pu == pv) return;

    if (rank[pu] > rank[pv]) {
        parent[pv] = pu;
    } else if (rank[pu] < rank[pv]) {
        parent[pu] = pv;
    } else {
        parent[pv] = pu;
        rank[pu]++;
    }
}


int spanningTree(int V, vector<vector<pair<int,int>>> &adj)  {
    vector<int> parent(V);
    vector<int> rank(V, 0);
    for(int i=0; i<V; i++) {
        parent[i] = i;
    }

    // Min-heap to store {weight, {u, v}}
    priority_queue<
        pair<int, pair<int,int>>,
        vector<pair<int, pair<int,int>>>,
        greater<pair<int, pair<int,int>>> 
    > pq;

    // Push all edges to pq:
    for(int i = 0; i < V; i++){
        for(size_t j = 0; j < adj[i].size(); j++){
    
            pq.push({ adj[i][j].second, { i, adj[i][j].first } });
        }
    }

    int cost = 0;
    int edges = 0;
    while(!pq.empty()){
        int wt = pq.top().first;
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();

        if(FindParent(u, parent) != FindParent(v, parent)) {
            cost += wt;
            UnionByRank(u, v, parent, rank);
            edges++;
        }
        if(edges == V-1) break;
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
DRY RUN

Graph edges (unique undirected edges with weights):
(0-1, 2), (0-3, 6), (1-2, 3), (1-3, 8), (1-4, 5), (2-4, 7)

Note: Because adj stores both directions, heap contains each edge twice; DSU prevents duplicates from being counted.

Initial DSU:
parent = [0,1,2,3,4]
rank   = [0,0,0,0,0]
cost = 0, edges = 0

Edges popped from min-heap in ascending weight order (conceptually):
1) Pop (0-1, wt=2)
   - FindParent(0) = 0, FindParent(1) = 1 -> different
   - Accept edge: cost += 2 -> cost = 2
   - UnionByRank(0,1): attach 1 under 0 (rank[0] becomes 1)
   - edges = 1
   - parent ~ [0,0,2,3,4], rank ~ [1,0,0,0,0]

2) Pop (1-2, wt=3)
   - FindParent(1) -> compresses to 0, FindParent(2) = 2 -> different
   - Accept edge: cost += 3 -> cost = 5
   - UnionByRank(1,2): actually union(0,2) -> attach 2 under 0
   - edges = 2
   - parent ~ [0,0,0,3,4], rank ~ [1,0,0,0,0]

3) Pop (1-4, wt=5)
   - FindParent(1) -> 0, FindParent(4) = 4 -> different
   - Accept edge: cost += 5 -> cost = 10
   - UnionByRank(1,4): union(0,4) -> attach 4 under 0
   - edges = 3
   - parent ~ [0,0,0,3,0], rank ~ [1,0,0,0,0]

4) Pop (0-3, wt=6)
   - FindParent(0) = 0, FindParent(3) = 3 -> different
   - Accept edge: cost += 6 -> cost = 16
   - UnionByRank(0,3): attach 3 under 0
   - edges = 4
   - parent ~ [0,0,0,0,0], rank ~ [1,0,0,0,0]

Now edges == V-1 (4), so the loop breaks.

Final MST cost = 16

Verification:
Accepted edges: (0-1:2), (1-2:3), (1-4:5), (0-3:6)
Sum = 2 + 3 + 5 + 6 = 16

Complexity summary:
- Building/popping heap dominates: O(E log E)
- DSU ops: amortized near O(1) per operation
- Space: O(V + E)
*/