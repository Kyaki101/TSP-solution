#include <bits/stdc++.h>
const int MAX = 1000000;
int dist[10000][10000], n, e, cost = 0; std::bitset<100000> msk;

void dp(int city) {
    printf("%d, ", city + 1);
    msk[city] = 1;
    int act = MAX, min = MAX, actmin;
    for (int i = 0; i < n; i++) {
        if (((dist[city][i] != 0) && (msk[i] == 0)) && (dist[city][i] + dist[i][city] < min)){
            actmin = dist[city][i];
            min = dist[i][0] + dist[city][i];
            act = i;
        }
    }
    if (min != MAX) cost += actmin;
    int nxt = act;
    if (nxt == MAX) {
        nxt = 0;
        printf("%d", nxt + 1);
        cost += dist[city][nxt];
        return;
    }
    dp(nxt);
}
 
int main() {
    std::ios_base::sync_with_stdio(0); std::cin.tie(0);
    std::cin>>n>>e;
    memset(dist, 0, sizeof dist);

    for (int i = 0; i < e; i++){
        int t1,t2,t;
        std::cin>>t1>>t2>>t;
        dist[t1-1][t2-1] = t; dist[t2-1][t1-1] = t; 
    }
    
    printf("DP : ");
    dp(0);
    printf(" Cost %d\n", cost);
    return 0;
}
