#include <bits/stdc++.h>

typedef std::vector<int> list;
typedef std::vector<std::vector<std::pair<int, int>>> adj;
typedef long long int ll;

adj adjaceny;

int n;
int e;

ll go = 0LL;

bool test(ll msk, ll i){
    return (msk & (1 << i));
}

int set(ll msk, ll i){
    return msk | (1 << i);
}

void fillMsk(){
    for(int i = 0; i < n; i++){
        go = set(go, i);
    }
}

int finder(int node, int goal){
    for(int i = 0; i < adjaceny[node].size(); i++){
        if(adjaceny[node][i].first == goal) return adjaceny[node][i].second;
    }
    return false;
}

std::pair<ll, list> comp(std::pair<ll, list> a, std::pair<ll, list> b, int add){
    b.first += add;
    if(a.first < b.first)return a;
    return b;
}

std::pair<ll, list> backtrack(int node, ll msk, int origin, list walk){
    msk = set(msk, node);
    walk.push_back(node);
    if(msk == go){
        int f = finder(node, origin);
        if(f){
            walk.push_back(origin);
            return std::make_pair(f, walk);
        }
        return std::make_pair((1 << 30), walk);
    }
    std::pair<ll, list> minRoute = std::make_pair((1 << 30), list(0));
    bool flag = false;
    for(int i = 0; i < adjaceny[node].size(); i++){
        if(!test(msk, adjaceny[node][i].first)){
            flag = true;
            minRoute = comp(minRoute, backtrack(adjaceny[node][i].first, msk, origin, walk), adjaceny[node][i].second);
        }
    }
    if(flag)return minRoute;
    return std::make_pair((1 << 30), walk);
}

void sol(){
    fillMsk();
    std::pair<ll, list> minRoute = std::make_pair((1 << 30), list(0));
    list walk;
    for(int i = 0; i < n; i++){
        minRoute = comp(minRoute, backtrack(i, 0LL, i, walk), 0);
    }
    std::cout << "Backtracking: ";
    for(int i = 0; i < minRoute.second.size(); i++){
        if(i != minRoute.second.size() - 1)std::cout << minRoute.second[i] + 1 << ',';
        else std::cout << minRoute.second[i] + 1 << " ";
    }
    std:: cout << "Costo: ";
    std::cout << minRoute.first << '\n';
}



int main(){
    std::cin >> n >> e;
    int a, b, w;
    adjaceny.assign(n, std::vector<std::pair<int, int>>(0));
    for(int i = 0; i < e; i++){
        std::cin >> a >> b >> w;
        adjaceny[a - 1].push_back(std::make_pair(b - 1, w));
        adjaceny[b - 1].push_back(std::make_pair(a - 1, w));
    }
    sol();


    return 0;
}