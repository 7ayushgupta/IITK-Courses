#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

typedef struct node_template
{
    ll key;
    node_template* next;
}node;

typedef struct edge_template
{
    ll u;
    ll v;
}edge;

class Graph
{
    public: 
        ll V, E;
        node ** Adj;
        ll* color; //0: white, 1: gray, 2: black
        ll* discovery_time;
        ll* alternative_time;
        ll* predecessor;
        edge* bridges;
        int bridges_count;
        Graph(ll, ll);    
        void performInput();
        void DFS();
        void bridgeChecker(ll);
        void printAdjacencyList();
        void resultSaver(ll, ll);
        void printAnswer();
        void positionSwap(edge *, edge *);
};

void Graph::printAdjacencyList()
{
    for (int i = 0; i < this->V; i++) 
    { 
        node* ptr;
        ptr = this->Adj[i];
        while(ptr!=NULL)
        {
            node* pointed_node = ptr;
            cout<<pointed_node->key<<"-> ";
            ptr=ptr->next;
        }
        cout<<"NULL"<<endl;
    }
}

Graph::Graph(ll v, ll e)
{
    Adj = (node **) malloc (v*sizeof(node *));
    for(ll i = 0; i<v; i++)
    {
        Adj[i] = NULL;
    }
    V = v; E=e;
    discovery_time = (ll *)malloc(v*sizeof(ll));
    alternative_time = (ll *)malloc(v*sizeof(ll));
    predecessor = (ll *)malloc(v*sizeof(ll));
    color = (ll *)malloc(v*sizeof(ll));
    bridges = (edge *) malloc(v*sizeof(edge));
    bridges_count = 0;
}

void Graph::performInput()
{
    for(ll i = 0; i<this->E; i++)
    {
        int vert1, vert2;
        scanf("%d %d\n", &vert1, &vert2);
        node* new_node1 = (node*) malloc(sizeof(node));
        new_node1->key=vert2;
        new_node1->next=this->Adj[vert1];
        this->Adj[vert1] = new_node1;

        node* new_node2 = (node*) malloc(sizeof(node));
        new_node2->key=vert1;
        new_node2->next=this->Adj[vert2];
        this->Adj[vert2] = new_node2;
    }
}

void Graph::resultSaver(ll a, ll b)
{
    this->bridges[this->bridges_count].u = a;
    this->bridges[this->bridges_count].v = b;
    this->bridges_count++;
    // for(int i = 0; i<this->bridges_count; i++)
    //     cout<<this->bridges[i].u<<" "<<this->bridges[i].v<<endl;

}

void Graph::bridgeChecker(ll i)
{
    static ll TIME = 0; 
    TIME++;
    this->discovery_time[i] = TIME;
    this->alternative_time[i] = TIME;
    this->color[i] = 1;
    node* ptr;
    ptr = this->Adj[i];
    while(ptr!=NULL)
    {
        if(this->color[ptr->key] == 0)
        {
            this->predecessor[ptr->key]=i;
            this->bridgeChecker(ptr->key);
            this->alternative_time[i] = min(this->alternative_time[i], this->alternative_time[ptr->key]);
            if(this->alternative_time[ptr->key] > this->discovery_time[i])
                resultSaver(i, ptr->key);
        }
        else if(ptr->key != this->predecessor[i])
            this->alternative_time[i] = min(this->alternative_time[i], this->discovery_time[ptr->key]);

        ptr=ptr->next;
    }
}

void Graph::DFS()
{
    for(int i = 0; i < this->V; i++) 
    { 
        this->predecessor[i] = NULL; 
        this->color[i] = 0; 
    }   
    for (int i = 0; i < this->V; i++)
        if (this->color[i] == 0) 
            this->bridgeChecker(i); 
}

void Graph::positionSwap(edge *xp, edge *yp)  
{  
    edge temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
  
void Graph::printAnswer()
{
    if(this->bridges_count == 0)
        cout<<"No"<<endl;
    else
    {
        for (int i = 0; i < this->bridges_count-1; i++)        
        {   
            for (int j = 0; j < this->bridges_count-i-1; j++)          
            {
                if(bridges[j].u > bridges[j + 1].u)
                    positionSwap(&bridges[j], &bridges[j+1]);
                if(bridges[j].u == bridges[j + 1].u && bridges[j].v > bridges[j+1].v)
                    positionSwap(&bridges[j], &bridges[j+1]);
            }
        }
        for(int i = 0; i<this->bridges_count; i++)
            cout<<this->bridges[i].u<<" "<<this->bridges[i].v<<endl;
    }
}

int main() 
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    ll v, e;
    cin>>v>>e;
    Graph graph(v, e);
    graph.performInput();
    graph.DFS();
    graph.printAnswer();
    return 0;
}
