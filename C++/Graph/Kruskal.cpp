#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) {
            return false;
        }
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

int main() {
    int nodes, edges;
    cin >> nodes >> edges;
    int u, v, w;
    vector<pair<int, pair<int, int>>> theEdges;
    for (int i = 0; i < edges; i++) {
        cin >> u >> v >> w;
        theEdges.push_back({w, {u, v}});
    }
    sort(theEdges.begin(), theEdges.end());
    UnionFind uf(nodes + 1); // Thay đổi kích thước thành nodes + 1 nếu đỉnh bắt đầu từ 1
    int weight = 0;
    int count = 0;
    for (auto &edge : theEdges) {
        w = edge.first;
        u = edge.second.first;
        v = edge.second.second;
        if (uf.unionSet(u, v)) {
            weight += w;
            count++;
            if (count == nodes - 1) {
                break;
            }
        }
    }
    cout << weight << endl;
    return 0;
}
