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
     edge* edges;   
     Graph(ll, ll);    
     void performInput();
     void sortEdges(ll, ll);
     void mergeEdges(ll, ll, ll);
     void reallocEdges(edge);
     ll KruskalMST(); 
     ll findSet(ll *, ll);
     void simpleSort();
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
    V=v; E=e;
}

void Graph::performInput()
{
    for(int i = 0; i<this->E; i++)
        cin>>edges[i].u>>edges[i].v>>edges[i].weight;
        // scanf("%lld %lld %lld", &(edges[i]).u, &(edges[i]).v, &(edges[i]).weight);

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
    edge* updated_edges = (edge *) malloc((this->E)*sizeof(edge));
    edge new_edge = edges[this->E-1];
    ll position;
    for(ll i = 0; i<this->E-2; i++)
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
    
    edges = updated_edges;
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

ll Graph::findSet(ll *sets, ll a)
{
    if(sets[a]==-__INT_MAX__) 
        return a;
    return findSet(sets, sets[a]);
}

ll Graph::KruskalMST()
{
    ll result = 0;
    ll* sets = (ll *) malloc(sizeof(ll)*this->V);
    for (ll i = 0; i<this->V; i++)
        sets[i]=-__INT_MAX__;
    edge* spanningTree = (edge*)malloc(this->V*sizeof(edge));
    for (ll i = 0, edgesAdded=0; i<this->E; i++)
    {
        if(edgesAdded==this->V-1)
            break;
        ll findSetA = findSet(sets, this->edges[i].u);
        ll findSetB = findSet(sets, this->edges[i].v);
        if(findSetA == findSetB)
            continue;
        spanningTree[edgesAdded] = edges[i];
        edgesAdded++;
        result+=edges[i].weight;
        ll unionSetA = findSet(sets, findSetA);
        ll unionSetB = findSet(sets, findSetB);
        if(unionSetA!=unionSetB)
            sets[unionSetA]=unionSetB;
    }
    edges = spanningTree;
    this->E=this->V;
    free(sets);
    return result;
}

void Graph::reallocEdges(edge new_edge)
{   
    edge* updated_edges = (edge *) malloc((this->E)*sizeof(edge));
    // edge new_edge = edges[this->E-1];
    ll position;
    for(ll i = 0; i<this->E-2; i++)
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
    
    edges = updated_edges;
    
//     this->E++;
//     edge* updated_edges = (edge *) malloc((this->E)*sizeof(edge));
//     for(int i = 0; i<this->E-1; i++)
//         updated_edges[i] = edges[i];
//     updated_edges[this->E-1] = new_edge;
//     edge* old_edges = edges;
//     edges = updated_edges;
//     free(old_edges);
//     return;
}

int main() 
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll v, e, q;
    cin>>v>>e>>q;
    // scanf("%lld %lld %lld\n", &v, &e, &q);
    Graph graph(v, e);
    graph.performInput();
    graph.sortEdges(0, e-1);
    cout<<graph.KruskalMST()<<endl;
    // printf("%lld\n", graph.KruskalMST());
    for(int i = 0; i<q; i++)
    {
        edge new_edge;
        // scanf("%lld %lld %lld", &(new_edge).u, &(new_edge).v, &(new_edge).weight);
        cin>>new_edge.u>>new_edge.v>>new_edge.weight;
        graph.reallocEdges(new_edge);
        // graph.simpleSort();
        cout<<graph.KruskalMST()<<endl;
        // printf("%lld\n", graph.KruskalMST());
    }
    return 0;
}