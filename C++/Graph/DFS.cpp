#include <iostream>
#include <map>
#include <list>
#include <stack>

using namespace std;

typedef struct{
    int id;
    bool var;
} NODE;

void DFS(map<int, list<int>> theMAP, int nodes, int edges,  NODE arr[], int n){
    cout << n << " ";
    arr[n - 1].var = true;
    for(auto i = theMAP[n].begin(); i != theMAP[n].end(); i++){
        if(!arr[*i - 1].var){
            DFS(theMAP, nodes, edges, arr, *i);
        }
    }
}

int main() {
    int nodes, edges;
    int a, b;
    cin >> nodes >> edges;
    NODE *arr = new NODE[nodes];
    map<int, list<int>> theMAP;
    for(int i = 0; i < edges; i++){
        cin >> a >> b;
        theMAP[a].push_back(b);
        theMAP[b].push_back(a);
    }
    for(int i = 0; i < nodes; i++){
        theMAP[i + 1].sort();
        arr[i].id = i + 1;
        arr[i].var = false;
    }
    bool out = false;
    do{
        for(int i = 0; i < nodes; i++){
            if(!arr[i].var){
                DFS(theMAP, nodes, edges, arr, i + 1);
            }
            if(i == nodes - 1){
                out = true;
            }
        }
    } while(out == false);
    return 0;
}

