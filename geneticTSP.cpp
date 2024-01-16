#include <bits/stdc++.h>
typedef long long ll;
ll nodos, vertices, MAX_GEN = 200, population_size, dist[1000][1000]; double mutation_rate = 0.28;

struct Route{
    std::vector<ll> path;
    double fitness;
    ll distTotal;
};



Route newRandomRoute(){
    Route route;
    for (int i = 0; i < nodos; i++)
        route.path.push_back(i);
    random_shuffle(route.path.begin(), route.path.end());
    route.path.push_back(route.path[0]);
    return route;
}



void calculateFitness(Route & route, ll dist[][1000]){
    double distTotal = 0.0;
    for (int i = 0; i < nodos; i++) 
        distTotal += dist[route.path[i]][route.path[i+1]];
    route.distTotal = distTotal;
    distTotal/= 100.0;
    route.fitness = distTotal;
}




std::pair<Route, int> bestRoute(std::vector<Route>& population) {
    double bestFitness = std::numeric_limits<double>::max();
    int bestIndex = -1;
    for (int i = 0; i < population.size(); i++) 
        if (population[i].fitness < bestFitness) {
            bestFitness = population[i].fitness;
            bestIndex = i;
        }
    // std::cout<<"bst = ";
    // for(int i: population[bestIndex].path) std::cout<<i<<' ';
    // std::cout<<'\n';
    return {population[bestIndex], bestIndex};
}





Route crossover(const Route& parent1, Route& parent2) {
    Route child;
    int startPos = rand() % (nodos), 
    endPos = rand() % (nodos);
    for (int i = 0; i < nodos; i++) {
        if (startPos < endPos && i > startPos && i < endPos) 
            child.path.push_back(parent1.path[i]);
        else if (startPos > endPos && !(i < startPos && i > endPos)) 
            child.path.push_back(parent1.path[i]);
        else child.path.push_back(-1);
    }
    for (int i = 0; i < nodos; i++) 
        if (find(child.path.begin(), child.path.end(), parent2.path[i]) == child.path.end()) 
            for (int j = 0; j < nodos+1; j++) 
                if (child.path[j] == -1) {
                    child.path[j] = parent2.path[i];
                    break;
                }
    child.path.push_back(child.path[0]);
    return child;
}




void mutate(Route& route) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, nodos-1);
    for (int i = 1; i < nodos; i++) 
        if ((double)rand() / RAND_MAX < mutation_rate) {
            int swap =  distrib(gen);
            std::swap(route.path[i], route.path[swap]);
        }
    // std::cout<<"mutate = ";
    // for(int i: route.path) std::cout<<i<<' ';
    // std::cout<<'\n';
}




int main(){
    std::cin>>nodos>>vertices;
    memset(dist, 100000, sizeof dist);
    population_size = nodos*nodos;
    // uso 0 para las dist o un num grande?
    while(vertices--){
        ll t1,t2,t;
        std::cin>>t1>>t2>>t;
        dist[t1-1][t2-1] = t;
        dist[t2-1][t1-1] = t;
    }

    // Generate the first population 
    std::vector<Route> population;
    for (int i = 0; i < population_size; i++) {
        population.push_back(newRandomRoute());
        calculateFitness(population[i], dist);
    }

    ll bestFitness = LONG_MAX;
    Route bb;
    // Iniciate the Genetic Algorithm
    for (int gen = 0; gen < 300; gen++) {
        std::vector<Route> newPopulation;

        for (ll i = 0; i < population_size/2; i++) {
            std::pair<Route, int> parent1 = bestRoute(population);
            // Erase the first best parent so it its not again in the generation
            population.erase(std::next(population.begin(), parent1.second));
            std::pair<Route, ll> parent2 = bestRoute(population);

            // Do the crossover between the best two parents
            Route child = crossover(parent1.first, parent2.first);
            // Calculate its fitness
            calculateFitness(child, dist);
            newPopulation.push_back(child);
            // Save to have the best child
            if(child.distTotal < bestFitness){bestFitness = child.distTotal; bb = child;}
            // Mutate it
            mutate(child);
            // Calculate its fitness
            calculateFitness(child, dist);
            newPopulation.push_back(child);
            // Save to have the best child again
            if(child.distTotal < bestFitness){bestFitness = child.distTotal;bb = child;}
        }
        //replace the old population with the new population
        population = newPopulation;
    }

    // Print the best route
    std::cout << "Genetico : ";
    for (int i ; i < bb.path.size()-1; i++) 
        std::cout << bb.path[i]+1 << ", ";
    std::cout << bb.path[nodos]+1;
    // Print the total distance of the best route
    std::cout << " Costo " << bestFitness << std::endl;


    

    return 0;
}