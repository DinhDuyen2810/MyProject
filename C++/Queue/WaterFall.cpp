//tim so buoc co c lit tu binh a lit va b lit

#include <iostream>
#include <queue>
#include <list>
#include <utility>
using namespace std;
int a, b, c;
//kiem ra xem da ton tai trang thai chua
bool checkVar(list<pair<int,int>> lis, pair<int, int> pai){
    for (auto it = lis.begin(); it != lis.end(); it++){
        if (it->first == pai.first && it->second == pai.second){
            return true;
        }
    }
    return false;
}
//do day binh a
pair<int,int> fullA(pair<int, int> pai){
    pair<int, int> newPai;
    newPai.first = a;
    newPai.second = pai.second;
    return newPai;
}
//do day binh b
pair<int,int> fullB(pair<int, int> pai){
    pair<int, int> newPai;
    newPai.first = pai.first;
    newPai.second = b;
    return newPai;
}
//do tu binh a qua b
pair<int,int> fullAtoB(pair<int, int> pai){
    pair<int, int> newPai;
    if(pai.first == 0){
        newPai.first = 0;
        newPai.second = pai.second;
    } else {
        int delta = b - pai.second;
        if(delta == 0){
            newPai.first = pai.first;
            newPai.second = pai.second;
        } else {
            if(delta > pai.first){
                newPai.first = 0;
                newPai.second = pai.first + pai.second;
            } else {
                newPai.first = pai.first - delta;
                newPai.second = pai.second + delta;
            }
        }
    }
    return newPai;
}
//do tu binh b qua a
pair<int,int> fullBtoA(pair<int, int> pai){
    pair<int, int> newPai;
    if(pai.second == 0){
        newPai.second = 0;
        newPai.first = pai.first;
    } else {
        int delta = a - pai.first;
        if(delta == 0){
            newPai.second = pai.second;
            newPai.first = pai.first;
        } else {
            if(delta > pai.second){
                newPai.second = 0;
                newPai.first = pai.second + pai.first;
            } else {
                newPai.second = pai.second - delta;
                newPai.first = pai.first + delta;
            }
        }
    }
    return newPai;
}
//do nuoc tu binh a di
pair<int,int> freeA(pair<int, int> pai){
    pair<int, int> newPai;
    newPai.first = 0;
    newPai.second = pai.second;
    return newPai;
}
//do nuoc tu binh b di
pair<int,int> freeB(pair<int, int> pai){
    pair<int, int> newPai;
    newPai.first = pai.first;
    newPai.second = 0;
    return newPai;
}

int main()
{
    int step;
    cin >> a >> b >> c;
    step = -1;
    queue<pair<int, int>> que;
    list<pair<int, int>> lis;
    pair<int, int> pai1, pai2;
    pai1 = make_pair(0, 0);
    que.push(pai1);
    lis.push_back(pai1);
    while(!que.empty()){
        if(pai1.first == c || pai1.second == c){
            cout << step << endl;
            break;
        }
        int queSize = que.size();
        for(int i = 0; i < queSize; i++){
            pai1 = que.front();
            que.pop();
            if(pai1.first == c || pai1.second == c){
                break;
            }
            pai2 = fullA(pai1);
            if(!checkVar(lis, pai2)){
                lis.push_back(pai2);
                que.push(pai2);
            }
            pai2 = fullB(pai1);
            if(!checkVar(lis, pai2)){
                lis.push_back(pai2);
                que.push(pai2);
            }
            pai2 = fullAtoB(pai1);
            if(!checkVar(lis, pai2)){
                lis.push_back(pai2);
                que.push(pai2);
            }
            pai2 = fullBtoA(pai1);
            if(!checkVar(lis, pai2)){
                lis.push_back(pai2);
                que.push(pai2);
            }
            pai2 = freeA(pai1);
            if(!checkVar(lis, pai2)){
                lis.push_back(pai2);
                que.push(pai2);
            }
            pai2 = freeB(pai1);
            if(!checkVar(lis, pai2)){
                lis.push_back(pai2);
                que.push(pai2);
            }
        }
        step++;
    }
}