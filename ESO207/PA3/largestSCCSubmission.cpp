#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
ll path_length = 0;

typedef struct node_template
{
    ll key;
    node_template* next;
}node;

class Stack{
    public:
        ll top;
        ll arr[100001];
    
        Stack();
        void push(ll c);
        bool isEmpty();
        ll pop();
};

Stack::Stack()
{
    this->top=0;
}

void Stack::push(ll c)
{
    (this->top)++;
    this->arr[this->top]=c;
}

bool Stack::isEmpty()
{
    return ((this->top)==0);
}

ll Stack::pop()
{
    if(this->isEmpty())
    {
        cout<<"Underflow";
        return -1;
    }
    else
    {
        (this->top)--;
        return arr[top+1];
    }
}

class Graph : public Stack
{
    public: 
        ll V, E;
        node ** Adj;
        node ** AdjT;
        ll* color; //0: white, 1: gray, 2: black
        Stack stack;
        Graph(ll, ll);    
        void performInput();
        void DFS();
        void DFS_Visit(ll);
        void DFS_Modified();
        void DFS_Visit_Modified(ll);
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
    
    for (int i = 0; i < this->V; i++) 
    { 
        node* ptr;
        ptr = this->AdjT[i];
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
        AdjT[i] = NULL;
    }
    V = v; E=e;
    color = (ll *)malloc(v*sizeof(ll));
    stack = Stack();
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
        if(AdjT[vert2] == NULL)
        {
            AdjT[vert2] = node3;
            AdjT[vert2]->next = node4;    
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

void Graph::DFS_Visit(ll u)
{
    this->color[u] = 1;
    node* ptr;
    ptr = this->Adj[u];
    while(ptr!=NULL)
    {
        node* pointed_node = ptr;
        if(this->color[pointed_node->key] == 0)
        {
            this->DFS_Visit(pointed_node->key);
        }
        ptr=ptr->next;
    }
    this->color[u] = 2;
    this->stack.push(u);
}

void Graph::DFS()
{    
    for (int i = 0; i<this->V; i++)
    {
        this->color[i] = 0;
    }
    for (int i = 0; i<this->V; i++)
    {
        if((this->color[i]) == 0)
            DFS_Visit(i);
    }
}

void Graph::DFS_Modified()
{
    ll result = 0;
    for (int i = 0; i<this->V; i++)
    {
        this->color[i] = 0;
    }
    while(!this->stack.isEmpty())
    {
        ll v = this->stack.pop();
        if(this->color[v]==0)
        {
            path_length = 1;
            this->DFS_Visit_Modified(v);
            result = max(result, path_length);
        }
    }
    cout<<result<<endl;
}

void Graph::DFS_Visit_Modified(ll v)
{
    this->color[v]=2;
    node* ptr;
    ptr = this->AdjT[v];
    while(ptr!=NULL)
    {
        node* pointed_node = ptr;
        if (color[pointed_node->key] == 0) 
        {
            path_length++;
            DFS_Visit_Modified(pointed_node->key); 
        }
        ptr=ptr->next;
    }
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
        graph.DFS();
        graph.DFS_Modified();
    }
    return 0;
}