#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long int ll;

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

class Queue{
    public:
        ll capacity=1000001;
        ll front;
        ll back;
        ll arr[1000001]={0};
    
        Queue();
        void enqueue(ll c);
        ll dequeue();
        bool isEmpty();
};

Queue::Queue()
{
    this->front=-1;
    this->back=-1;
}

void Queue::enqueue(ll c)
{
    if(this->back == this->capacity - 1)
        printf("Queue is actually full\n");
    else
    {
        if(this->front == -1)
            this->front = 0;
        this->back++;
        arr[this->back] = c;   
    }
}

bool Queue::isEmpty()
{
    return (this->front==-1);
}

ll Queue::dequeue()
{
    if(this->front == -1)
    {
        printf("Queue is Empty\n");
        return -__INT_MAX__;
    }
    else{
        ll temp = this->arr[this->front];
        this->front++;
        if(this->front > this->back)
            this->front = this->back = -1;
        return temp;
    }
}  
 

class Graph : public Queue
{
    public: 
        ll V, E;
        node ** Adj;
        ll* color; //0: white, 1: gray, 2: black
        Queue queue;
        ll* bfs_time;
        ll* discovery_time;
        ll* alternative_time;
        ll* predecessor;
        edge bridge;
        ll bridges_count;
        Graph(ll, ll);    
        void performInput();
        void DFS();
        void BFS(ll);
        void bridgeChecker(ll);
        void calculateDistance();
};

Graph::Graph(ll v, ll e)
{
    Adj = (node **) malloc (v*sizeof(node *));
    for(ll i = 0; i<v; i++)
        Adj[i] = NULL;
    V = v; E=e;
    discovery_time = (ll *)malloc(v*sizeof(ll));
    alternative_time = (ll *)malloc(v*sizeof(ll));
    predecessor = (ll *)malloc(v*sizeof(ll));
    color = (ll *)malloc(v*sizeof(ll));
    bfs_time = (ll* )malloc(v*sizeof(ll));
    bridges_count = 0;
    queue = Queue();
}

void Graph::performInput()
{
    for(ll i = 0; i<this->E; i++)
    {
        ll vert1, vert2;
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
            {
                bridges_count++;
                bridge.u = i;
                bridge.v = ptr->key;
            }
        }
        else if(ptr->key != this->predecessor[i])
            this->alternative_time[i] = min(this->alternative_time[i], this->discovery_time[ptr->key]);

        ptr=ptr->next;
    }
}

void Graph::DFS()
{
    for(ll i = 0; i < this->V; i++) 
    { 
        this->predecessor[i] = NULL; 
        this->color[i] = 0; 
    }   
    for (ll i = 0; i < this->V; i++)
        if (this->color[i] == 0) 
            this->bridgeChecker(i); 
}

void Graph::calculateDistance()
{
    for(ll i = 0; i<this->V; i++)
    {
        this->color[i] = 0;
        this->bfs_time[i] = __INT_MAX__;
    }
    this->color[bridge.v] = 2;
    this->bfs_time[bridge.v]=__INT_MAX__;
    this->BFS(bridge.u);
    
    this->color[bridge.u] = 2;
    this->bfs_time[bridge.u]=__INT_MAX__;
    this->BFS(bridge.v);
    
    this->bfs_time[bridge.v]=0;
    this->bfs_time[bridge.u]=0;
}

void Graph::BFS(ll s) 
{
    this->color[s] = 1; 
    this->bfs_time[s] = 0;
    queue.enqueue(s); 
    while(!queue.isEmpty()) 
    { 
        ll u = queue.dequeue(); 
        node* ptr;
        ptr = this->Adj[u];
        while(ptr!=NULL)
        {
            if(this->color[ptr->key] == 0)
            {
                this->color[ptr->key]=1;
                this->bfs_time[ptr->key] = this->bfs_time[u]+1;
                queue.enqueue(ptr->key);
            }
            ptr=ptr->next;
        }
        this->color[u]=2;
    } 
}
  
int main() 
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    ll v, e, q;
    cin>>v>>e>>q;
    Graph graph(v, e);
    graph.performInput();
    graph.DFS();
    if(graph.bridges_count>0)
        graph.calculateDistance();
   
    for(ll i = 0; i<q; i++)
    {
        ll a, b;
        cin>>a>>b;
        ll result = graph.bfs_time[a] + graph.bfs_time[b] + 1;
        cout<<result<<endl;
    }
    return 0;
}
