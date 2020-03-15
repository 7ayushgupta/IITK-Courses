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
        int capacity=10001;
        int front;
        int back;
        int arr[10001]={0};
    
        Queue();
        void enqueue(int c);
        int dequeue();
        bool isEmpty();
};

Queue::Queue()
{
    this->front=-1;
    this->back=-1;
}

void Queue::enqueue(int c)
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

int Queue::dequeue()
{
    if(this->front == -1)
    {
        printf("Queue is Empty\n");
        return -__INT_MAX__;
    }
    else{
        int temp = this->arr[this->front];
        this->front++;
        if(this->front > this->back)
            this->front = this->back = -1;
        return temp;
    }
}  
  

class Graph : public Queue
{
    public: 
        int V, E;
        node ** Adj;
        int* color;   
        int* distance;
        Queue queue;
        Graph(int, int);    
        void performInput();
        bool bipartiteBFS(int);
        bool isBipartite();
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
    V = v; 
    E=e;
    distance = (int *)malloc((v+1)*sizeof(int));
    color = (int *)malloc((v+1)*sizeof(int));
    queue = Queue();
}

void Graph::performInput()
{
    for(int i = 0; i<this->E; i++)
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

bool Graph::bipartiteBFS(int s)
{
    int current_mark = 1;
    this->color[s] = current_mark;
    this->distance[s] = 0;
    queue.enqueue(s);
    while(!queue.isEmpty())
    {
        int u = queue.dequeue();
        node* ptr;
        ptr = this->Adj[u];
        while(ptr!=NULL)
        {
            node* v = ptr;
            if(v->key == u)
                return false;
            if (color[v->key] == 0) 
            {
                current_mark=current_mark*-1;
                color[v->key] = current_mark;
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

bool Graph::isBipartite()
{
    for (int i = 0; i<=this->V; i++)
    {
        this->color[i] = 0;
        this->distance[i] = __INT_MAX__;
    }
    for (int i = 1; i <= this->V; i++) 
    {
        if (this->color[i] == 0) 
        {
            if (bipartiteBFS(i) == false) 
                return false; 
        }
     }
    return true; 
}

int main() 
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    scanf("%d\n", &t);
    while(t--)
    {
        int v, e;
        scanf("%d %d\n", &v, &e);
        if(e==0)
        {
            cout<<"Yes"<<endl;
            continue;
        }            
        Graph graph(v, e);
        graph.performInput();
        if(graph.isBipartite())
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }
    return 0;
}