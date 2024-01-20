#include <bits/stdc++.h>
const int MAX = 100000;
using namespace std;

int dist[10000][10000], memo[10000][10000], n, e, cost = 0; 


// la funcion recursiva
pair<int, vector<int>> fun(int i, int mask, vector<int> path, int nodo){
    path.push_back(nodo);
    // caso base, si solo el 1er y el i bit estan prendidos
	if (mask == ((1 << i) | 3))
		return make_pair(dist[1][i],path);
	if (memo[i][mask] != 0)
		return make_pair(memo[i][mask],path);
	int res = MAX; 
    // prueba con el menor de todos
	for (int j = 1; j <= n; j++)
		if ((mask & (1 << j)) && j != i && j != 1)
			res = std::min(res, fun(j, mask & (~(1 << i)), path, j).first + dist[j][i]);
	return make_pair(memo[i][mask] = res, path);
}


int main() {
    std::ios_base::sync_with_stdio(0); std::cin.tie(0);
    std::cin>>n>>e;
    memset(dist, MAX, sizeof dist);// inicializa el dist con puros 100000
    memset(memo, 0, sizeof memo);// inicializa el memo con 0

    for (int i = 0; i < e; i++){
        int t1,t2,t;
        std::cin>>t1>>t2>>t;
        dist[t1][t2] = t; dist[t2][t1] = t; 
    }
    

    vector<int> p;
    int ans = MAX;
    // lo que hace el for es agarrar el menor de todos los ciclos iniciando
    // del nodo 1 hasta el nodo n
    for (int i = 1; i <= n; i++){
        pair<int, vector<int>> temp = fun(i, (1 << (n + 1)) - 1, p, i);
        if((temp.first + dist[i][1]) > 0 && ans > (temp.first + dist[i][1])){
            ans = temp.first + dist[i][1];
            p = temp.second;
        }
        else ans = ans;
        //std::cout<<temp + dist[i][1]<<" = fun\n";                        
        }
 
    //printf("The cost of most efficient tour = %d\n", ans);



    cout<<"DP : ";
    // esta es la funcion para imprimir el camino
    int i;
    for (i = 0; i < n; i++)
        cout<<p[i]<<", ";
    cout<<p[i+1]; // no lo hice en p[0] para ver que lo hiciera bien

    cout<<" Costo "<<ans<<'\n';
    return 0;
}