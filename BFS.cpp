#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> bfs(int V, vector<vector<int>>& adj) {
    queue<int> q;
    q.push(0);
    vector<int> visited(V, 0);
    visited[0] = 1;

    vector<int> ans;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        ans.push_back(node);

        for (int nbr : adj[node]) {
            if (!visited[nbr]) {
                visited[nbr] = 1;
                q.push(nbr);
            }
        }
    }
    return ans;
}

int main() {
    int V = 5;
    vector<vector<int>> adj(V);

    // Example graph edges
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(0);
    adj[1].push_back(3);
    adj[2].push_back(0);
    adj[2].push_back(4);
    adj[3].push_back(1);
    adj[4].push_back(2);

    vector<int> ans = bfs(V, adj);

    cout << "BFS Traversal: ";
    for (int node : ans) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
