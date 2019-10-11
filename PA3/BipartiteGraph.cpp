#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
ll TIME;
ll path_length = 0;

typedef struct node_template
{
    ll key;
    node_template* next;
}node;

class Queue{
    public:
        ll capacity=100001;
        ll front;
        ll back;
        ll size;
        ll arr[100001];
    
        Queue();
        void enqueue(ll c);
        ll dequeue();
        bool isEmpty();
};

Queue::Queue()
{
    this->front=0;
    this->back=this->capacity-1;
    size=0;
}

void Queue::enqueue(ll c)
{
    this->back = (this->back + 1) % this->capacity;  
    this->arr[this->back] = c;  
    this->size = this->size + 1;  
}

bool Queue::isEmpty()
{
    return ((this->size)==0);
}

ll Queue::dequeue()
{
    if (this->isEmpty())  
    {
        cout<<"Underflow"<<endl;
        return -1;
    } 
    ll item = this->arr[this->front];  
    this->front = (this->front + 1) % this->capacity;  
    this->size = this->size - 1;  
    return item;  
}  
  

class Graph : public Queue
{
    public: 
        ll V, E;
        node ** Adj;
        node ** AdjT;
        ll* color; //0: white, 1: gray, 2: black    
        ll* distance;
        ll* predecessor;
        Queue queue;
        Graph(ll, ll);    
        void performInput();
        bool bipartiteBFS();
        void printAdjacencyList();
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
    AdjT = (node **) malloc (v*sizeof(node *));
    for(ll i = 0; i<v; i++)
    {
        Adj[i] = NULL;
    }
    V = v; E=e;
    distance = (ll *)malloc(v*sizeof(ll));
    color = (ll *)malloc(v*sizeof(ll));
    queue = Queue();
}

void Graph::performInput()
{
    for(ll i = 0; i<this->E; i++)
    {
        ll vert1, vert2;
        cin>>vert1>>vert2;
        node* node1 = (node*) malloc(sizeof(node));
        node* node2 = (node*) malloc(sizeof(node));
        node1->key = vert1;
        node2->key = vert2;
        node1->next = NULL;
        node2->next = NULL;
        if(Adj[vert1] == NULL)
        {
            Adj[vert1] = node1;
            // Adj[vert1]->next = node2;    
        }
        else
        {
            node *temp_ptr = Adj[vert1];
            while(temp_ptr->next!=NULL)
                temp_ptr = temp_ptr->next;
            temp_ptr->next=node2;
        }
        
        node* node3 = (node*) malloc(sizeof(node));
        node* node4 = (node*) malloc(sizeof(node));
        node3->key = vert2;
        node4->key = vert1;
        node3->next = NULL;
        node4->next = NULL;
        if(AdjT[vert2] == NULL)
        {
            AdjT[vert2] = node3;
            // AdjT[vert2]->next = node4;    
        }
        else
        {
            node *temp_ptr = AdjT[vert2];
            while(temp_ptr->next!=NULL)
                temp_ptr = temp_ptr->next;
            temp_ptr->next=node4;
        }
    }
}

bool Graph::bipartiteBFS()
{
    for (int i = 1; i<this->V; i++)
    {
        this->color[i] = 0;
        this->distance[i] = INFINITY;
    }
    this->color[0] = 1;
    this->distance[0] = 0;
    this->predecessor[0] = -1;
    queue.enqueue(0);

    while(!queue.isEmpty())
    {
        ll u = queue.dequeue();
        node* ptr;
        ptr = this->Adj[u];
        while(ptr!=NULL)
        {
            node* pointed_node = ptr;
            if (color[pointed_node->key] == 0) 
            {
                color[pointed_node->key] = 1;
                distance[pointed_node->key] = distance[u]+1;
                queue.enqueue(pointed_node->key);
            }
            else if(distance[u] == distance[pointed_node->key])
            {
                return false;
            }
            ptr=ptr->next;
        }
        color[u]=2;
    }
    return true;
}

int main() 
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    cin>>t;
    while(t--)
    {
        ll v, e;
        cin>>v>>e;
        Graph graph(v, e);
        graph.performInput();
        if(graph.bipartiteBFS())
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }
    return 0;
}
