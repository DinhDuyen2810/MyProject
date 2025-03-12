#include <iostream>
#include <climits>

using namespace std;

const int n = 5; // Số thành phố
int dis[n][n] = {
    {-1, 10, 15, 20, -1},
    {10, -1, 35, 25, 30},
    {15, 35, -1, 30, 20},
    {20, 25, 30, -1, 15},
    {-1, 30, 20, 15, -1}
};
bool visited[n] = {false}; // Đánh dấu thành phố đã đi qua
int minCost = INT_MAX; // Giá trị đường đi ngắn nhất
int path[n]; // Lưu đường đi tối ưu
int curPath[n]; // Đường đi hiện tại

void Try(int k, int curCost, int curCity){
    for(int i = 1; i < n; i++){
        if(!visited[i] && dis[curCity][i] != -1){
            curPath[k] = i;
            visited[i] = true;
            curCost += dis[curCity][i];
            if(k == n - 1){
                if(dis[i][0] != -1){
                    curCost += dis[i][0];   
                    if(curCost < minCost){
                        minCost = curCost;
                        for(int j = 0; j < n; j++){
                            path[j] = curPath[j];
                        }
                    }

                }
            } else {
                Try(k + 1, curCost, i);
            }
            visited[i] = false;
            curCost -= dis[curCity][i];
        }
    }
}




int main() {
    visited[0] = true; 
    curPath[0] = 0; 
    Try(1, 0, 0);

    // In kết quả
    cout << "Duong di ngan nhat: ";
    for (int i = 0; i < n; i++) {
        cout << path[i] << " -> ";
    }
    cout << "0" << endl;
    cout << "Chi phi nho nhat: " << minCost << endl;

    return 0;
}