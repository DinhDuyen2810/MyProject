#include <iostream>
#include <map>
#include <list>
#include <queue>

using namespace std;

typedef struct{
    int id;
    bool var;
} NODE;

int main() {
    int nodes, edges;
    int a, b;
    queue<int> theQUEUE;
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
                theQUEUE.push(arr[i].id);
                arr[i].var = true;
                break;
            }
            if(i == nodes - 1){
                out = true;
            }
        }
        while(!theQUEUE.empty()){
            int node = theQUEUE.front();
            theQUEUE.pop();
            cout << node << " ";
            for(auto i = theMAP[node].begin(); i != theMAP[node].end(); i++){
                if(!arr[*i - 1].var){
                    theQUEUE.push(*i);
                    arr[*i - 1].var = true;
                }
            }
        }
    } while(out == false);
    return 0;
}

