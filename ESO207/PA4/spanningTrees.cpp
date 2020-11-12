#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long int ll;

typedef struct edge_template
{
    ll u;
    ll v;
    ll weight;
}edge;

class Graph
{
     public:
     ll V, E;
     edge* edges, *spanningTree;
     ll *parents, *ranks;
     Graph(ll, ll);    
     void performInput();
     void sortEdges(ll, ll);
     void mergeEdges(ll, ll, ll);
     void reallocEdges(edge);
     ll KruskalMST(); 
     void unionSet(ll, ll, ll*, ll*);
     void link(ll, ll, ll*, ll*);
     ll findSet(ll *, ll);
     void simpleSort();
     ll makePartition(ll, ll);
     void quickSort(ll, ll);
     void printEdges();
};

void Graph::printEdges()
{
    for (int i = 0; i < this->E; i++) 
        cout<<edges[i].weight<<", ";
    cout<<endl;
}

Graph::Graph(ll v, ll e)
{
    edges = (edge *) malloc(e*sizeof(edge));
    parents = (ll*) malloc(v*sizeof(ll));
    ranks = (ll*) malloc(v*sizeof(ll));
    spanningTree = (edge *)malloc(sizeof(edge)*(this->V));
    V=v; E=e;
}

void Graph::performInput()
{
    for(int i = 0; i<this->E; i++)
        scanf("%lld %lld %lld", &(edges[i]).u, &(edges[i]).v, &(edges[i]).weight);
}

void Graph::sortEdges(ll m, ll n)
{
    if(m<n)
    {
        ll mid=(m+n)/2;
        sortEdges(m, mid);        
        sortEdges(mid+1,n);
        mergeEdges(m, mid, n);
    }
    return;
}

void Graph::simpleSort()
{
    edge updated_edges[this->E];
    edge new_edge = edges[this->E-1];
    ll position;
    for(ll i = 0; i<=this->E-2; i++)
        if(edges[i].weight>new_edge.weight)
        {    
            position=i;
            break;
        }
    for(ll i = 0; i<position; i++)
        updated_edges[i] = edges[i];
    updated_edges[position] = new_edge;
    for(ll i = position+1; i<this->E; i++)
        updated_edges[i] = edges[i-1];
    for(int i = 0; i<this->E; i++)
        edges[i]=updated_edges[i];
}

void Graph::mergeEdges(ll p, ll q, ll r)
{
    edge leftPortion[q-p+2];
    edge rightPortion[r-q+1];
    int count, i, a, b;
    for(i = p, count = 0; i<=q; i++)
        leftPortion[count++] = this->edges[i];
    leftPortion[count].weight=__INT_MAX__;
    for(i = q+1, count = 0; i<=r; i++)
        rightPortion[count++] = this->edges[i];
    rightPortion[count].weight=__INT_MAX__;
    for(i=p, a=0, b=0; i<=r; i++)
    {
        if(leftPortion[a].weight<=rightPortion[b].weight)
            this->edges[i] = leftPortion[a++];
        else
            this->edges[i] = rightPortion[b++];
    }
    return;
}

ll Graph::makePartition(ll low, ll high)  
{  
    edge pivot = edges[high];
    ll i=low-1; 
    for (ll j = low; j <= high - 1; j++)  
    {  
        if (edges[j].weight < pivot.weight)  
        {  
            i++;   
            edge temp = edges[i];
            edges[i] = edges[j];
            edges[j] = temp;
        }  
    }  
    edge temp = edges[i+1];
    edges[i+1] = edges[high];
    edges[high] = temp;
    return (i+1);  
}  

void Graph::quickSort(ll low, ll high)
{
    if (low<high)
    {
        ll pivotReturned = Graph::makePartition(low, high);
        quickSort(low, pivotReturned-1);  
        quickSort(pivotReturned+1, high); 
    }
}

void Graph::reallocEdges(edge new_edge)
{   
    edge updated_edges[this->E];
    ll position;
    for(ll i = 0; i<=this->E-2; i++)
        if(edges[i].weight>new_edge.weight)
        {    
            position=i;
            break;
        }
    for(ll i = 0; i<position; i++)
        updated_edges[i] = edges[i];
    updated_edges[position] = new_edge;
    for(ll i = position+1; i<this->E; i++)
        updated_edges[i] = edges[i-1];    
    for(int i = 0; i<this->E; i++)
        edges[i]=updated_edges[i];
}

ll Graph::findSet(ll *parents, ll x)
{
    if(x!=parents[x])
        parents[x]=findSet(parents, parents[x]);
    return parents[x];
}

void Graph::link(ll x, ll y, ll *ranks, ll *parents)
{
    if(ranks[x]>ranks[y])
        parents[y]=x;
    else
    {
        parents[x]=y;
        if(ranks[x]==ranks[y])
            ranks[y]++;
    }
    
}

void Graph::unionSet(ll x, ll y, ll* ranks, ll* parents)
{
    link(findSet(parents, x), findSet(parents, y), ranks, parents);
}

ll Graph::KruskalMST()
{
    // printEdges();
    ll result = 0;
    for(ll i = 0; i<this->V; i++)
    {
        parents[i]=i;
        ranks[i]=0;
    }
    for (ll i = 0, edgesAdded=0; i<this->E; i++)
    {
        ll findSetA = findSet(parents, this->edges[i].u);
        ll findSetB = findSet(parents, this->edges[i].v);
        if(findSetA!=findSetB)
        {
            spanningTree[edgesAdded] = edges[i];
            edgesAdded++;
            result += this->edges[i].weight;
            if(edgesAdded==this->V-1)
                break;
            unionSet(this->edges[i].u, this->edges[i].v, ranks, parents);
        }
    }
    edges=spanningTree;
    return result;
}

int main() 
{
    ll v, e, q;
    scanf("%lld %lld %lld\n", &v, &e, &q);
    Graph graph(v, e);
    graph.performInput();
    graph.sortEdges(0, e-1);
    printf("%lld\n", graph.KruskalMST());
    graph.E=graph.V;
    
    for(ll i = 0; i<q; i++)
    {
        edge new_edge;
        scanf("%lld %lld %lld", &(new_edge).u, &(new_edge).v, &(new_edge).weight);
        graph.reallocEdges(new_edge);
        printf("%lld\n", graph.KruskalMST());
    }
    return 0;
}