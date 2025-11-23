#include <iostream>
#include <vector>
using namespace std;
// SPACE: O(V^2) where V is number of vertices

//Undirected & unweighted Graph using Adjacency Matrix
int main() {
    int vertex, edges;
    cin >> vertex >> edges;

    vector<vector<bool>>AdjMatrix(vertex, vector<bool>(vertex, 0));

    int u, v; //to mark edge between u and v
    for(int i = 0; i < edges; i++){
    cin>>u>>v;
    AdjMatrix[u][v] = 1;
    AdjMatrix[v][u] = 1; //for undirected graph
    }

    for(int i = 0; i < vertex; i++){
        for(int j = 0; j < vertex; j++){
            cout << AdjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

//Undirected and Weighted Graph using Adjacency Matrix
/*
int main() {
    int vertex, edges;
    cin >> vertex >> edges;

    vector<vector<int>>AdjMatrix(vertex, vector<int>(vertex, 0));

    int u, v, weight;
    for(int i = 0; i < edges; i++){
    cin>>u>>v>>weight;
    AdjMatrix[u][v] = weight;
    AdjMatrix[v][u] = weight;
    }

    for(int i = 0; i < vertex; i++){
        for(int j = 0; j < vertex; j++){
            cout << AdjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
*/

//Directed Graph using Adjacency Matrix
/*int main() {
    int vertex, edges;
    cin >> vertex >> edges;

    vector<vector<bool>>AdjMatrix(vertex, vector<bool>(vertex, 0));

    int u, v; //to mark edge between u and v
    for(int i = 0; i < edges; i++){
    cin>>u>>v;
    AdjMatrix[u][v] = 1; //Since it is directed so u -> v exists, and not v->u

    }

    for(int i = 0; i < vertex; i++){
        for(int j = 0; j < vertex; j++){
            cout << AdjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
*/