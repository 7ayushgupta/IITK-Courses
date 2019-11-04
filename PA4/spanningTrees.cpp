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
     int V, E;
     edge* edges;
     int* color;   
     int* distance;
     Graph(int, int);    
     void performInput();
     void sortEdges(ll, ll);
     void mergeEdges(ll, ll, ll);
     void reallocEdges(edge);
     ll KruskalMST(); 
     ll findSet(ll *, ll);
     void printEdges();
};

void Graph::printEdges()
{
    for (int i = 0; i < this->E; i++) 
        cout<<edges[i].weight<<", ";
    cout<<endl;
}

Graph::Graph(int v, int e)
{
    edges = (edge *) malloc(e*sizeof(edge));
    V=v; E=e;
    distance = (int *)malloc((v+1)*sizeof(int));
    color = (int *)malloc((v+1)*sizeof(int));
}

void Graph::performInput()
{
    for(int i = 0; i<this->E; i++)
        cin>>edges[i].u>>edges[i].v>>edges[i].weight;

    // for(int i = 0; i<this->E; i++)
    //     cout<<edges[i].u<<edges[i].v<<edges[i].weight;   
    // cout
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

void Graph::mergeEdges(ll p, ll q, ll r)
{
    edge leftPortion[q-p+1];
    edge rightPortion[r-q+1];
    for(int i = p, count = 0; i<=q; i++)
        leftPortion[count++] = this->edges[i];
    for(int i = q+1, count = 0; i<=r; i++)
        rightPortion[count++] = this->edges[i];

    for(int i=p, a=0, b=0; i<=q && a<q-p+1 && b<r-q+1; i++)
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
    //cout<<"Inside KRUSKAL"<<endl;
    ll result = 0;
    ll* sets = (ll *) malloc(sizeof(ll)*this->V);
    for (ll i = 0; i<this->V; i++)
        sets[i]=-__INT_MAX__;
    for (ll i = 0, edgesAdded=0; i<this->E; i++)
    {
        if(edgesAdded==this->V-1)
            break;
        ll findSetA = findSet(sets, this->edges[i].u);
        ll findSetB = findSet(sets, this->edges[i].v);
        //cout<<findSetA<<" "<<findSetB<<endl;
        if(findSetA == findSetB)
            continue;
        edgesAdded++;
        //cout<<"Edge added weight: "<<edges[i].weight<<endl;
        result+=edges[i].weight;
        ll unionSetA = findSet(sets, findSetA);
        ll unionSetB = findSet(sets, findSetB);
        if(unionSetA!=unionSetB)
            sets[unionSetA]=unionSetB;
    }
    free(sets);
    return result;
}

void Graph::reallocEdges(edge new_edge)
{
    bool alreadyPresent = false;
    ll presentPosition = -1;
    for(int i = 0; i<this->E && !alreadyPresent; i++)
    {
            if(edges[i].u==new_edge.u && edges[i].v==new_edge.v)
            {
                alreadyPresent=true;
                presentPosition=i;
            }
    }
    //cout<<"already at:"<<presentPosition<<endl;
    this->E++;
    if(alreadyPresent==false)
    {
        bool alreadyInserted=false;
        edge* updated_edges = (edge *) malloc((this->E)*sizeof(edge));
        ll entries=0;

        for(int i = 0; i<this->E-1; i++)
        {
          //  cout<<"i: "<<i<<", alreadyInserted: "<<alreadyInserted<<endl;
            if(!alreadyInserted)
            {
                if(edges[i].weight>new_edge.weight)
                {
             //       cout<<"HERE1"<<endl;
                    updated_edges[entries++]=new_edge;
                    alreadyInserted = true;
                }
                else
                {
             //       cout<<"HERE2"<<endl;
                    updated_edges[entries++]=edges[i];
                }
            }
            else
            {
                updated_edges[entries++]=edges[i];
             //   cout<<"HERE3"<<endl;
            }
            // for (int j = 0; j < entries; j++) 
            //     cout<<updated_edges[j].weight<<", ";
            // cout<<endl;
        }
        if(!alreadyInserted)
            updated_edges[this->E-1]=new_edge;
        else
            updated_edges[this->E-1]=edges[this->E-2];
        // for (int j = 0; j < entries; j++) 
        //         cout<<updated_edges[j].weight<<", ";
        //     cout<<endl;
      //  cout<<"alreadyInserted: "<<alreadyInserted<<endl;
        this->edges = updated_edges;
        // cout<<"Updated: "<<endl;
       // printEdges();
    }
    if(alreadyPresent==true)
    {
        bool alreadyInserted=false;
        edge* updated_edges = (edge *) malloc((this->E)*sizeof(edge));
        ll entries=0, h=0;
        // cout<<"NEw edge weight:"<<new_edge.weight<<endl;
        for(int i = 0; i<this->E; i++)
        {
            if(i==presentPosition)
                continue;
            if(edges[h].weight<new_edge.weight)
            {
                // cout<<"i: "<<i<<"j: "<<h<<"HERE1"<<endl;
                updated_edges[entries++]=edges[h++];
            }
            else if(!alreadyInserted)
            {   
                // cout<<"i: "<<i<<"h: "<<h<<"HERE2"<<endl;
                updated_edges[entries++]=new_edge;
                alreadyInserted=true;
                updated_edges[entries++]=edges[h++];
                i++;
            }
            else
                  updated_edges[entries++]=edges[h++];
            
            // for (int j = 0; j < entries; j++) 
            //     cout<<updated_edges[j].weight<<", ";
            // cout<<endl;
        }
        this->edges=updated_edges;
       // printEdges();
    }
}

int main() 
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    ios_base::sync_with_stdio(false);
    ll v, e, q;
    cin>>v>>e>>q;
    Graph graph(v, e);
    graph.performInput();
    // graph.printEdges();
    graph.sortEdges(0, e-1);
    // graph.printEdges();
    cout<<graph.KruskalMST()<<endl;
    for(int i = 0; i<q; i++)
    {
        edge new_edge;
        cin>>new_edge.u>>new_edge.v>>new_edge.weight;
        graph.reallocEdges(new_edge);
        // graph.printEdges();
        cout<<graph.KruskalMST()<<endl;
        // cout<<"---------------------------------------------------"<<endl;
    }
    return 0;
}