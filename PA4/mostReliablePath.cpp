#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long int ll;

class Graph
{
    public:
    ll V, E;
    int Adj[2501][2501];
    int* color;   
    int* distance;
    Graph(ll, ll);   
    void performInput();
    void Djisktra(ll);
    ll closestNeighbour();
};

Graph::Graph(ll v, ll e)
{
    V = v; 
    E = e;
    distance = (int *) malloc(v*sizeof(int));
    color = (int *) malloc(v*sizeof(int));
}

void Graph::performInput()
{
    for(int i = 0; i<this->E; i++)
    {
        int vert1, vert2, weight;
        scanf("%d %d %d\n", &vert1, &vert2, &weight);
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
            if (!this->color[j] && Adj[closeNeighbour][j] && this->distance[closeNeighbour] != __INT_MAX__ && this->distance[closeNeighbour] + this->Adj[closeNeighbour][j] < this->distance[j]) 
                this->distance[j] = this->distance[closeNeighbour] + this->Adj[closeNeighbour][j];
        }
    } 
    return;
}

int main() 
{
    ll v, e, s, t;
    cin>>v>>e;
    Graph graph(v, e);
    graph.performInput();
    cin>>s>>t;
    graph.Djisktra(s);
    cout<<graph.distance[t];
    return 0;
}