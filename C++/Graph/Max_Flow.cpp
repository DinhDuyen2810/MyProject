#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <climits>

using namespace std;

int nodes, edges;

typedef struct{
    int to, capacity, flow;
} Edge;
//Tìm chỉ số của to trong graph[key]
int findEdgeIndex(vector<Edge>& edges, int to) {
    for (int i = 0; i < (int)edges.size(); i++) {
        if (edges[i].to == to) {
            return i;
        }
    }
    return -1;
}

int EdmondsKarp(map<int, vector<Edge>> graph, int source, int sink){
    int max_flow = 0;
    bool find = false;
    while(true){
        //Vecto tìm cha và kiểm tra đã thăm chưa
        vector<int> parent(nodes + 1, -1);
        parent[source] = source;
        queue<int> theQUEUE;
        theQUEUE.push(source);
        find = false;
        while(!theQUEUE.empty()){
            int node = theQUEUE.front();
            theQUEUE.pop();
            //BFS
            for(int i = 0; i < (int)graph[node].size(); i++){
                Edge edge = graph[node][i];
                if(edge.capacity > edge.flow && parent[edge.to] == -1){
                    parent[edge.to] = node;
                    theQUEUE.push(edge.to);
                    if(edge.to == sink){
                        find = true;
                        int max_increase = INT_MAX;
                        int tail = sink;
                        //tìm luồng max có thể tăng
                        while(tail != source){
                            int thePrev = parent[tail];
                            Edge edge = graph[thePrev][findEdgeIndex(graph[thePrev], tail)];
                            max_increase = min(max_increase, edge.capacity - edge.flow);
                            tail = thePrev;
                        }
                        tail = sink;
                        //tăng luồng
                        while(tail != source){
                            int thePrev = parent[tail];
                            graph[thePrev][findEdgeIndex(graph[thePrev], tail)].flow += max_increase;
                            tail = thePrev;
                        }
                        max_flow += max_increase;
                        break;
                    }
                }    
            }
            if(find){
                break;
            }    
        }
        if(parent[sink] == -1){ 
            break;
        } 
    }
    return max_flow;
}

int main() {
    cin >> nodes >> edges;
    int source, sink;
    cin >> source >> sink;
    map<int, vector<Edge>> graph;
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        int k = findEdgeIndex(graph[u], v);
        if(k != -1){
            graph[u][k].capacity += w;
        }
        graph[u].push_back({v, w, 0});
    }
    cout << EdmondsKarp(graph, source, sink);
    return 0;
}

