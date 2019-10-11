#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

typedef struct node_template
{
    int key;
    node_template* next;
}node;

class Queue{
    public:
        int capacity=1000001;
        int front;
        int back;
        int size;
        int arr[1000001]={0};
    
        Queue();
        void enqueue(int c);
        int dequeue();
        bool isEmpty();
};

Queue::Queue()
{
    this->front=0;
    this->back=this->capacity-1;
    size=0;
}

void Queue::enqueue(int c)
{
    this->back = (this->back + 1) % this->capacity;  
    this->arr[this->back] = c;  
    this->size = this->size + 1;  
}

bool Queue::isEmpty()
{
    return ((this->size)==0);
}

int Queue::dequeue()
{
    if (this->isEmpty())  
    {
        cout<<"Underflow"<<endl;
        return -1;
    } 
    int item = this->arr[this->front];  
    this->front = (this->front + 1) % this->capacity;  
    this->size = this->size - 1;  
    return item;  
}  
  

class Graph : public Queue
{
    public: 
        int V, E;
        node ** Adj;
        int* color; //0: white, 1: gray, 2: black    
        int* distance;
        Queue queue;
        Graph(int, int);    
        void performInput();
        bool bipartiteBFS();
        void printAdjacencyList();
};

void Graph::printAdjacencyList()
{
    for (int i = 0; i <=this->V; i++) 
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

Graph::Graph(int v, int e)
{
    Adj = (node **) malloc ((v+1)*sizeof(node *));
    for(int i = 0; i<=v; i++)
    {
        Adj[i] = NULL;
    }
    V = v; E=e;
    distance = (int *)malloc((v+1)*sizeof(int));
    color = (int *)malloc((v+1)*sizeof(int));
    queue = Queue();
}

void Graph::performInput()
{
    for(int i = 0; i<this->E; i++)
    {
        int vert1, vert2;
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
            Adj[vert1]->next = node2;    
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
        if(Adj[vert2] == NULL)
        {
            Adj[vert2] = node3;
            Adj[vert2]->next = node4;    
        }
        else
        {
            node *temp_ptr = Adj[vert2];
            while(temp_ptr->next!=NULL)
                temp_ptr = temp_ptr->next;
            temp_ptr->next=node4;
        }
    }
}

bool Graph::bipartiteBFS()
{
    for (int i = 1; i<=this->V; i++)
    {
        this->color[i] = 0;
        this->distance[i] = __INT_MAX__;
    }
    int s = 1;
    this->color[s] = 1;
    this->distance[s] = 0;
    queue.enqueue(s);

    while(!queue.isEmpty())
    {
        int u = queue.dequeue();
        node* ptr;
        ptr = this->Adj[u]->next;
        while(ptr!=NULL)
        {
            node* v = ptr;
            if (color[v->key] == 0) 
            {
                color[v->key] = 1;
                distance[v->key] = distance[u]+1;
                queue.enqueue(v->key);
            }
            else if(distance[v->key] == distance[u])
                return false;
            ptr=ptr->next;
        }
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
        int v, e;
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