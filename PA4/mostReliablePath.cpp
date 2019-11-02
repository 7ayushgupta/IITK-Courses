#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long int ll;

class Graph
{
    public:
    ll V, E;
    int Adj[2505][2505];
    int* color;   
    int* distance;
    Graph(ll, ll);   
    void performInput();
    void Djisktra(ll);
    ll closestNeighbour();
};

Graph::Graph(ll v, ll e)
{
    for(int i = 0; i<v; i++)
        for(int j=0; j<v; j++)
            Adj[i][j]=-__INT_MAX__;
    V = v; 
    E = e;
    distance = (int *) malloc(v*sizeof(int));
    color = (int *) malloc(v*sizeof(int));
}

void Graph::performInput()
{
    for(ll i = 0; i<this->E; i++)
    {
        ll vert1, vert2, weight;
        scanf("%lld %lld %lld", &vert1, &vert2, &weight);
        Adj[vert1][vert2] = weight;
    }
}

ll Graph::closestNeighbour()
{ 
    ll minimum = __INT_MAX__;
    ll closest = 0; 
    for(ll i = 0; i<this->V; i++) 
    {
        if(!this->color[i] && this->distance[i] <= minimum) 
        {
            minimum = this->distance[i];
            closest = i; 
        }
    }
    return closest;
} 

void Graph::Djisktra(ll s)
{
    for(int i =0; i<this->V; i++)
    {
        this->distance[i]=__INT_MAX__;
        this->color[i]=0;
    }
    this->distance[s] = 0;
    for (int i = 0; i<this->V-1; i++) 
    { 
        int closeNeighbour = closestNeighbour(); 
        this->color[closeNeighbour]=1;
        for (int j = 0; j<this->V; j++)
        { 
            if (!this->color[j] && Adj[closeNeighbour][j]!=-__INT_MAX__ && this->distance[closeNeighbour] != __INT_MAX__ && this->distance[closeNeighbour] + this->Adj[closeNeighbour][j] < this->distance[j]) 
                this->distance[j] = this->distance[closeNeighbour] + this->Adj[closeNeighbour][j];
        }
    } 
    return;
}

int main() 
{
    ios_base::sync_with_stdio(false);
    ll v, e, s, t;
    scanf("%lld %lld\n", &v, &e);
    Graph graph(v, e);
    graph.performInput();
    scanf("%lld %lld\n", &s, &t);
    graph.Djisktra(s);
    printf("%lld", graph.distance[t]);
    return 0;
}