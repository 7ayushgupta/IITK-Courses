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

class Sets 
{  
    public: 
    int p;  
    int r;  
    ll findSet(Sets*, ll);
    void unionOfSets(Sets *, ll, ll);
};


ll Sets::findSet(Sets *sets, ll a)
{
   if (sets[a].p!=a)  
        sets[a].p=findSet(sets, sets[a].p);  
    return sets[a].p;  
}

void Sets::unionOfSets(Sets sets[], ll x, ll y)  
{  
    ll r_x = findSet(sets, x);  
    ll r_y = findSet(sets, y);  
    if (sets[r_x].r < sets[r_y].r)  
        sets[r_x].p = r_y;  
    else if (sets[r_x].r > sets[r_y].r)  
        sets[r_y].p = r_x;    
    else
    {  
        sets[r_y].p = r_x;  
        sets[r_x].r++;  
    }  
}  

class Graph : public Sets
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

ll Graph::KruskalMST()
{
    ll result = 0;
    Sets *sets = new Sets[(this->V*sizeof(Sets))];  
    for (ll i = 0; i<this->V; i++)
    {
        sets[i].p=i;
        sets[i].r=0;
    }
    for (ll i = 0, edgesAdded=0; i<this->E; i++)
    {
        if(edgesAdded==this->V-1)
            break;
        ll findSetA = findSet(sets, this->edges[i].u);
        ll findSetB = findSet(sets, this->edges[i].v);
        if(findSetA!=findSetB)
        {
            result += this->edges[i].weight;
           unionOfSets(sets, findSetA, findSetB);
        }   
    }
    free(sets);
    return result;
}

void Graph::reallocEdges(edge new_edge)
{   
    this->E++;
    edge* updated_edges = (edge *) malloc((this->E)*sizeof(edge));
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

int main() 
{
    ll v, e, q;
    scanf("%lld %lld %lld\n", &v, &e, &q);
    Graph graph(v, e);
    graph.performInput();
    // graph.sortEdges(0, e-1);
    graph.quickSort(0, e-1);
    printf("%lld\n", graph.KruskalMST());
    for(int i = 0; i<q; i++)
    {
        edge new_edge;
        scanf("%lld %lld %lld", &(new_edge).u, &(new_edge).v, &(new_edge).weight);
        graph.reallocEdges(new_edge);
        printf("%lld\n", graph.KruskalMST());
    }
    return 0;
}