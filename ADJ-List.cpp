#include <iostream>
#include <vector>
using namespace std;
// SPACE: O(V + E) 
//undirected graphs(no weights) using adjacency list
 int main(){
    int vertex, edges;
    cin >> vertex >> edges;

    vector<vector<int>> AdjList(vertex);

    int u, v; //to mark edge between u and v
    for(int i = 0; i < edges; i++){
        cin>>u>>v;
        AdjList[u].push_back(v);
        AdjList[v].push_back(u); 
    }

    //printing adjacency list
    for(int i = 0; i < vertex; i++){
        cout << i << " -> ";
        for(int j = 0; j < AdjList[i].size(); j++)
            cout << AdjList[i][j] << " ";
        
        cout << endl;
    }
}

// Undirected weighted graph
/*
int main(){
    int vertex, edges;
    cin >> vertex >> edges;

    vector<vector<pair<int,int>>> AdjList(vertex);

    int u, v, weight; 
    for(int i = 0; i < edges; i++){
        cin>>u>>v>>weight;
        AdjList[u].push_back(make_pair(v, weight));
        AdjList[v].push_back(make_pair(u, weight)); 
    }

    //printing adjacency list
    for(int i = 0; i < vertex; i++){
        cout << i << " -> ";
        for(int j = 0; j < AdjList[i].size(); j++)
            cout << AdjList[i][j].first << " " << AdjList[i][j].second << " ";
        
        cout << endl;
    }
}  
*/      